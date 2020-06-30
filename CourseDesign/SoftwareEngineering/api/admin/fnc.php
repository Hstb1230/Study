<?php

if(!isset($conn)) exit;

/**
 * 获取管理账户信息
 * @return array
 */
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

function isPortal()
{
    return @$_SESSION['role'] === 1;
}

function changeAdminPassword($password, $newPassword, & $reason, & $report)
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

/**
 * 获取指定用户的游戏记录
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

/**
 * 设置用户状态
 * @param int $id 用户id
 * @param bool $state true/解禁 false/封禁
 * @param string $reason 失败原因
 * @return bool
 */
function setUserState($id, $state, & $reason)
{
    global $conn;
    $stmt = $conn->prepare('UPDATE account SET state = ? WHERE id = ?');
    $state = ($state ? 1 : 0);
    $stmt->bind_param('ii', $state, $id);
    $stmt->execute();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '用户不存在';
    $stmt->close();
    return $success;
}

/**
 * 设置商品状态
 * @param int $id
 * @param bool $state 状态，true/上线 false/下线
 * @param string $reason 失败原因
 * @return bool
 */
function setCommodityState($id, $state, & $reason)
{
    $state = ($state ? 1 : 0);
    global $conn;
    $stmt = $conn->prepare('UPDATE commodity SET state = ? WHERE id = ?');
    $stmt->bind_param('ii', $state, $id);
    $stmt->execute();
    $success = ($stmt->affected_rows > 0);
    if(!$success)
        $reason = '商品不存在或重复操作';
    $stmt->close();
    return $success;
}

/**
 * 设置商品信息
 * @param int $id 如果为0，则代表新增
 * @param int $prop 商品类型：0/体力，1/金币
 * @param int $amount 数量
 * @param int $gold 所需金币
 * @param string $reason
 * @return bool
 */
function setCommodityInfo($id, $prop, $amount, $gold, & $reason)
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
    $success = $stmt->execute();
    if(!$success)
        $reason = '操作数据库失败：' . $stmt->error;
    $stmt->close();
    return $success;
}

/**
 * 设置充值信息
 * @param int $id 充值信息ID，为0时新增
 * @param int $amount 对应的金币数量
 * @param double $pay 对应的RMB数量
 * @param $reason
 * @return bool
 */
function setRechargeInfo($id, $amount, $pay, & $reason)
{
    global $conn;
    $query = null;
    if($id === 0)
        $query = 'INSERT INTO recharge_list (amount, pay) VALUE (?, ?)';
    else
        $query = 'UPDATE recharge_list SET amount = ?, pay = ? WHERE id = ?';
    $stmt = $conn->prepare($query);
    if($id === 0)
        $stmt->bind_param('id', $amount, $pay);
    else
        $stmt->bind_param('idi', $amount, $pay, $id);
    $success = $stmt->execute();
    if(!$success)
        $reason = '操作数据库失败：' . $stmt->error;
    $stmt->close();
    return $success;
}

/**
 * 设置验证问题
 * @param int $id 问题ID，0为增加
 * @param string $content 问题内容
 * @param string $reason 失败原因
 * @return bool
 */
function setVerifyProblem($id, $content, & $reason)
{
    $query = null;
    if($id === 0)
        $query = 'INSERT INTO verify_problem (content) VALUE (?)';
    else
        $query = 'UPDATE verify_problem SET content = ? WHERE id = ?';
    global $conn;
    $stmt = $conn->prepare($query);
    if($id === 0)
        $stmt->bind_param('s', $content);
    else
        $stmt->bind_param('si', $content, $id);
    $success = $stmt->execute();
    if(!$success)
        $reason = '操作数据库失败：' . $stmt->error;
    $stmt->close();
    return $success;
}


