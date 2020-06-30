<?php

/**
 * 获取充值信息列表
 * @param int $id 指定充值信息的id，若指定则只查询该充值信息内容
 * @return array
 */
function getRechargeList($id = 0)
{
    $uInfo = null;
    $query = 'select id, pay, amount from recharge_list';
    if($id > 0)
        $query .= 'where id = ?';
    global $conn;
    $stmt = $conn->prepare($query);
    if($id > 0)
        $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $i = [
        'id' => 0,
        'pay' => 0,
        'amount' => 0,
    ];
    $stmt->bind_result($i['id'], $i['pay'], $i['amount']);
    $list = [];
    while($stmt->fetch())
    {
        $list[] = [
            'id' => $i['id'],
            'pay' => $i['pay'],
            'amount' => $i['amount']
        ];
    }
    $stmt->close();
    return $list;
}

/**
 * 获取商品列表
 * @param $id
 * @return array
 * @noinspection DuplicatedCode
 */
function getCommodityList($id = 0)
{
    $query = 'SELECT id, state, prop_type, amount, pay FROM commodity ';
    if($id !== 0)
        $query .= 'WHERE id = ?';
    global $conn;
    $stmt = $conn->prepare($query);
    if($id !== 0)
        $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $list = $i = [];
    $stmt->bind_result($i['id'], $i['state'], $i['prop'], $i['amount'], $i['pay']);
    while($stmt->fetch())
    {
        $list[] = [
            'id' => $i['id'],
            'state' => $i['state'],
            'prop' => $i['prop'],
            'amount' => $i['amount'],
            'pay' => $i['pay']
        ];
    }
    $stmt->close();
    return $list;
}

/**
 * 获取指定用户充值记录
 * @param int $user_id 用户ID，为0则查询所有
 * @return array
 */
function getUserRechargeRecord($user_id = 0)
{
    $uInfo = null;
    $query = 'select id, user_id, time, original_price, final_pay, pay_way, get_gold from recharge_record order by time desc';
    if($user_id > 0)
        $query = substr_replace($query, ' where user_id = ? ', strpos($query, 'order by'), 0);
    else
        $uInfo = getUserInfo($user_id);
    global $conn;
    $stmt = $conn->prepare($query);
    if($user_id > 0)
        $stmt->bind_param('i', $user_id);
    $stmt->execute();
    $stmt->store_result();
    $i = [
        'id' => 0,
        'user_id' => 0,
        'user_name' => '',
        'time' => 0,
        'original_price' => 0,
        'final_pay' => 0,
        'pay_way' => 0,
        'get_gold' => 0,
    ];
    $stmt->bind_result($i['id'], $i['user_id'], $i['time'], $i['original_price'], $i['final_pay'], $i['pay_way'], $i['get_gold']);
    $list = [];
    while($stmt->fetch())
    {
        if($user_id === 0)
            $uInfo = getUserInfo($i['user_id']);
        $list[] = [
            'id' => $i['id'],
            'user_id' => $i['user_id'],
            'user_name' => $uInfo['username'],
            'time' => $i['time'],
            'original_price' => $i['original_price'],
            'final_pay' => $i['final_pay'],
            'pay_way' => $i['pay_way'],
            'get_gold' => $i['get_gold'],
        ];
    }
    $stmt->close();
    return $list;
}

/**
 * 获取验证问题列表
 * @param int $id
 * @return array
 */
function getVerifyProblemList($id = 0)
{
    $query = 'SELECT id, content FROM verify_problem ';
    if($id > 0)
        $query .= 'WHERE id = ?';
    global $conn;
    $stmt = $conn->prepare($query);
    if($id > 0)
        $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $i = [];
    $list = [];
    $stmt->bind_result($i['id'], $i['content']);
    while($stmt->fetch())
        $list[] = [
            'id' => $i['id'],
            'content' => $i['content'],
        ];
    $stmt->close();
    return $list;
}

/**
 * 验证问题是否存在
 * @param int $problem_id 问题id
 * @return bool
 */
function existVerifyProblem($problem_id)
{
    return count(getVerifyProblemList($problem_id)) === 1;
}

/**
 * 获取用户ID
 * @param $username
 * @return int
 */
function getUserID($username)
{
    $id = 0;
    global $conn;
    $stmt = $conn->prepare('SELECT id FROM account WHERE username = ?');
    $stmt->bind_param('s', $username);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($id);
    if($stmt->num_rows)
        $stmt->fetch();
    $stmt->close();
    return $id;
}

/**
 * 重置指定用户密码
 * @param $id
 * @param string $newPassword 新密码（原文）
 * @param $reason
 * @return bool
 */
function resetUserPassword($id, $newPassword, & $reason)
{
    $newPassword = md5($newPassword);
    global $conn;
    $stmt = $conn->prepare('UPDATE account SET password = ? WHERE id = ?');
    $stmt->bind_param('si', $newPassword, $id);
    $stmt->execute();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '用户不存在 或 未设置新密码';
    $stmt->close();
    return $success;
}

/**
 * 获取商品信息
 * @param $id
 * @return array
 */
function getCommodityInfo($id)
{
    return getCommodityList($id)[0];
}

/**
 * 获取指定用户的消费记录
 * @param $id
 * @return array
 */
function getUserConsumeRecord($id)
{
    global $conn;
    $stmt = $conn->prepare('select id, time, user_id, amount, commodity_id from consume_record where user_id = ? order by time desc ');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $i = [
        'id' => 0,
        'time' => 0,
        'user_id' => $id,
        'gold_amount' => 0,
        'commodity_id' => 0,
        'prop_type' => 0,
        'prop_amount' => 0,
    ];
    $stmt->bind_result($i['id'], $i['time'], $i['user_id'], $i['gold_amount'], $i['commodity_id']);
    $list = [];
    while($stmt->fetch())
    {
        $cInfo = getCommodityInfo($i['commodity_id']);
        $list[] = [
            'id' => $i['id'],
            'time' => $i['time'],
            'user_id' => $i['user_id'],
            'gold_amount' => $i['gold_amount'],
            'commodity_id' => $i['commodity_id'],
            'prop_type' => $cInfo['prop'],
            'prop_amount' => $cInfo['amount'],
        ];
    }
    $stmt->close();
    return $list;
}

/**
 * 获取用户信息
 * @param $id
 * @param null $username
 * @return array
 */
function getUserInfo($id = null, $username = null)
{
    $i = [
        'id' => $id,
        'username' => $username,
        'state' => true,
        'create_time' => 0,
        'password' => '',
        'verify_problem_id' => 0,
        'problem_answer' => '',
        'last_login_time' => 0,
        'recharge_sum' => 0
    ];
    $query = 'select id, username, state, create_time, password, verify_problem_id, problem_answer from account ';
    if($id !== null)
        $query .= 'where id = ?';
    else if($username !== null)
        $query .= 'where username = ?';
    else
        return [];
    global $conn;
    // 查询基本信息
    $stmt = $conn->prepare($query);
    if($id !== null)
        $stmt->bind_param('i', $id);
    else if($username !== null)
        $stmt->bind_param('s', $username);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result(
        $i['id'],
        $i['username'],
        $i['state'],
        $i['create_time'],
        $i['password'],
        $i['verify_problem_id'],
        $i['problem_answer']
    );
    if($stmt->num_rows === 0)
    {
        $i = [];
        goto end;
    }
    $stmt->fetch();
    $i['state'] = ($i['state'] !== 0);
    $stmt->close();
    // 查询登录时间
    $stmt = $conn->prepare('select time from login_record where user_id = ? order by time desc ');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    if($stmt->num_rows > 0)
    {
        $stmt->bind_result($i['last_login_time']);
        $stmt->fetch();
    }
    $stmt->close();
    // 统计充值金额
    $stmt = $conn->prepare('SELECT SUM(final_pay) FROM `recharge_record` WHERE user_id = ?');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    if($stmt->num_rows > 0)
    {
        $stmt->bind_result($i['recharge_sum']);
        $stmt->fetch();
        if($i['recharge_sum'] === null)
            $i['recharge_sum'] = 0;
    }
    end:
    $stmt->close();
    return $i;
}
