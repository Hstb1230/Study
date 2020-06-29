<?php

if(!isset($conn)) exit;

/**
 * 增加验证问题
 * @param $content
 * @param $reason
 * @return bool
 */
function addVerifyProblem($content, & $reason)
{
    global $conn;
    $stmt = $conn->prepare('INSERT INTO verify_problem (content) VALUE (?)');
    $stmt->bind_param('s', $content);
    $success = $stmt->execute();
    if(!$success)
        $reason = $stmt->error;
    $stmt->close();
    return $success;
}

function getManagerAccount()
{
    $acc = [];
    global $conn;
    $stmt = $conn->prepare('SELECT content FROM `setting` WHERE name = ? UNION SELECT content FROM `setting` WHERE name = ?');
    $var1 = 'username';
    $var2 = 'password';
    $stmt->bind_param('ss', $var1, $var2);
    $stmt->execute();
    $stmt->store_result();
    $content = '';
    $stmt->bind_result($content);
    $stmt->fetch();
    $acc['username'] = $content;
    $stmt->fetch();
    $acc['password'] = $content;
    $stmt->close();
    return $acc;
}

/**
 * 登录验证
 * @param string $username
 * @param string $password
 * @param string $reason
 * @param string $report
 * @return bool
 */
function portal($username, $password, & $reason, & $report)
{
    $acc = getManagerAccount();
    if($username !== $acc['username'])
    {
        $reason = '用户名错误';
        $report = 'u';
        goto end;
    }
    if($password !== $acc['password'])
    {
        $reason = '密码错误';
        $report = 'p';
        goto end;
    }
    $_SESSION['role'] = 1;
    return true;
    end:
    return false;
}

function isLogin()
{
    return @$_SESSION['role'] === 1;
}

function changePassword($password, $newPassword, & $reason, & $report)
{
    if(!isLogin())
    {
        $reason = '未授权';
        return false;
    }
    $acc = getManagerAccount();
    if($password !== $acc['password'])
    {
        $report = 'p';
        $reason = '原密码错误';
        return false;
    }
    global $conn;
    $stmt = $conn->prepare('UPDATE setting SET content = ? WHERE name = ?');
    $var2 = 'password';
    $stmt->bind_param('ss', $newPassword, $var2);
    $stmt->execute();
    $stmt->close();
    return true;
}

/**
 * 退出登录
 * @return bool
 */
function logout()
{
    unset($_SESSION['role']);
    return true;
}

/**
 * 获取用户信息
 * @param $id
 * @return array
 */
function getUserInfo($id)
{
    $i = [
        'id' => $id,
        'username' => '',
        'state' => true,
        'create_time' => 0,
        'last_login_time' => 0,
        'recharge_sum' => 0
    ];
    global $conn;
    // 查询基本信息
    $stmt = $conn->prepare('select username, state, create_time from account where id = ?');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($i['username'], $i['state'], $i['create_time']);
    $stmt->fetch();
    $i['state'] = ($i['state'] !== 0);
    $stmt->close();
    // 查询登录时间
    $stmt = $conn->prepare('select time from login_record where user_id = ?');
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
    $stmt->close();
    return $i;
}

/**
 * 获取用户列表
 * @return array
 */
function getUserList()
{
    global $conn;
    $stmt = $conn->prepare('select id from account');
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($id);
    $list = [];
    while($stmt->fetch())
        $list[] = getUserInfo($id);
    $stmt->close();
    return $list;
}

function getCommodityInfo($id)
{
    return getCommodityList($id)[0];
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
 * 获取指定用户的充值记录
 * @param $id
 * @return array
 */
function getUserPlayRecord($id)
{
    global $conn;
    $stmt = $conn->prepare('select play_time, score from play_record where user_id = ? order by play_time desc ');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $i = [
        'user_id' => $id,
        'time' => 0,
        'score' => 0,
    ];
    $stmt->bind_result($i['time'], $i['score']);
    $list = [];
    while($stmt->fetch())
        $list[] = [
            'user_id' => $i['user_id'],
            'time' => $i['time'],
            'score' => $i['score'],
        ];
    $stmt->close();
    return $list;
}

function chooseBanUser($id, $state, & $reason)
{
    global $conn;
    $stmt = $conn->prepare('UPDATE account SET state = ? WHERE id = ?');
    $state = ($state ? 1 : 0);
    $stmt->bind_param('ii', $state, $id);
    $stmt->execute();
//    $stmt->store_result();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '用户不存在';
    $stmt->close();
    return $success;
}

function banUser($id, & $reason)
{
    return chooseBanUser($id, 0, $reason);
}

function unBanUser($id, & $reason)
{
    return chooseBanUser($id, 1, $reason);
}

/**
 * 重置指定用户密码
 * @param $id
 * @param $newPassword
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
//    $stmt->store_result();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '用户不存在';
    $stmt->close();
    return $success;
}

/**
 * @param int $user_id
 * @return array
 */
function getRechargeRecord($user_id = 0)
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

function chooseBanCommodity($id, $state, & $reason)
{
    $state = ($state ? 1 : 0);
    global $conn;
    $stmt = $conn->prepare('UPDATE commodity SET state = ? WHERE id = ?');
    $stmt->bind_param('ii', $state, $id);
    $stmt->execute();
//    $stmt->store_result();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '商品不存在或重复操作';
    $stmt->close();
    return $success;
}

function banCommodity($id, & $reason)
{
    return chooseBanCommodity($id, false, $reason);
}

function unBanCommodity($id, & $reason)
{
    return chooseBanCommodity($id, true, $reason);
}

/**
 * @param int $id 如果为0，则代表新增
 * @param int $prop 商品类型：0/体力，1/金币
 * @param int $amount 数量
 * @param int $gold 所需金币
 * @return bool
 */
function setCommodity($id, $prop, $amount, $gold)
{
    global $conn;
    $query = null;
    if($id === 0)
        $query = 'INSERT INTO commodity (publish_time, prop_type, amount, pay) VALUE (?, ?, ?, ?)';
    else
        $query = 'UPDATE commodity SET prop_type = ?, amount = ?, pay = ? WHERE id = ?';
    $stmt = $conn->prepare($query);
    if($id === 0)
    {
        $time = time();
        $stmt->bind_param('iiii', $time, $prop, $amount, $gold);
    }
    else
    {
        $stmt->bind_param('iiii', $prop, $amount, $gold, $id);
    }
    $success = $stmt->execute() || $stmt->affected_rows > 0;
    $stmt->close();
    return $success;
}

/** @noinspection DuplicatedCode */
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

function setRecharge($id, $amount, $pay)
{
    global $conn;
    $query = null;
    if($id === 0)
        $query = 'INSERT INTO recharge_list (amount, pay) VALUE (?, ?)';
    else
        $query = 'UPDATE recharge_list SET amount = ?, pay = ? WHERE id = ?';
    $stmt = $conn->prepare($query);
    if($id === 0)
    {
        $stmt->bind_param('id', $amount, $pay);
    }
    else
    {
        $stmt->bind_param('idi', $amount, $pay, $id);
    }
    $success = $stmt->execute() || $stmt->affected_rows > 0;
    $stmt->close();
    return $success;
}
