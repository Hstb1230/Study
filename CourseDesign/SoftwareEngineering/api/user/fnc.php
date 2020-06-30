<?php
if(!isset($conn)) exit;

/**
 * 是否已登录
 * @return bool
 */
function isLogin()
{
    return @$_SESSION['role'] === 0;
}

/**
 * 是否存在用户
 * @param string $username
 * @return bool
 */
function existUser($username)
{
    return getUserID($username) != 0;
}

/**
 * 注册
 * @param string $username 用户名
 * @param string $password 密码
 * @param integer $verify_problem_id 验证问题id
 * @param string $verify_answer 验证问题答案
 * @param string $reason 失败原因
 * @return bool 注册结果
 */
function register($username, $password, $verify_problem_id, $verify_answer, &$reason)
{
    if(existUser($username))
    {
        $reason = '已存在用户';
        return false;
    }
    if(!existVerifyProblem($verify_problem_id))
    {
        $reason = '问题ID非法';
        return false;
    }
    if(strlen($username) < 3)
    {
        $reason = '用户名太短';
        return false;
    }
    if(strlen($password) < 3)
    {
        $reason = '密码太短';
        return false;
    }
    $create_time = time();
    $password = md5($password);
    global $conn;
    $stmt = $conn->prepare('INSERT INTO account (username, create_time, password, verify_problem_id, problem_answer) VALUE (?, ?, ?, ?, ?);');
    $stmt->bind_param('sisis', $username, $create_time, $password, $verify_problem_id, $verify_answer);
    $isSuccess = ($stmt->execute());
    if($isSuccess)
    {
        $_SESSION['role'] = 0;
        $_SESSION['user_id'] = getUserID($username);
        setWarehouse(10, 5, 3);
        logout();
    }
    else
        $reason = $stmt->error;
    $stmt->close();
    return $isSuccess;
}

function logout()
{
    unset($_SESSION['role'], $_SESSION['user_id']);
}

/**
 * 修改用户密码
 * @param $password
 * @param $newPassword
 * @param $reason
 * @param $value
 * @return bool
 */
function changeUserPassword($password, $newPassword, & $reason, & $value)
{
    $success = false;
    $info = getUserInfo($_SESSION['user_id']);
    if(empty($info))
    {
        $reason = '不存在用户';
        goto end;
    }

    if($info['password'] != $password)
    {
        $reason = '原密码错误';
        $value = 'p';
        goto end;
    }

    if($password === md5($newPassword))
    {
        $reason = '新旧密码一致';
        $value = 'np';
        goto end;
    }

    $success = resetUserPassword($_SESSION['user_id'], $newPassword, $reason);

    end:
    return $success;
}

/**
 * 重置密码
 * @param string $username 用户名
 * @param int $verify_problem_id 密保问题ID
 * @param string $verify_ans 密保问题答案
 * @param string $new_password 新密码
 * @param string $reason 失败原因
 * @param string $data 错误字段
 * @return bool
 */
function resetPassword($username, $verify_problem_id, $verify_ans, $new_password, & $reason, & $data)
{
    $success = false;
    $info = getUserInfo(null, $username);
    if(empty($info))
    {
        $data = 'u';
        $reason = '用户不存在';
        goto end;
    }

    if($info['verify_problem_id'] != (int)$verify_problem_id)
    {
        $data = 'vans';
        $reason = '问题或答案错误';
        goto end;
    }

    if($info['problem_answer'] != $verify_ans)
    {
        $data = 'vans';
        $reason = '问题或答案错误';
        goto end;
    }

    if($info['password'] === md5($new_password))
    {
        $data = 'np';
        $reason = '新旧密码一样';
        goto end;
    }

    $success = resetUserPassword($info['id'], $new_password, $reason);
    end:
    return $success;
}

/**
 * 修改密保问题
 * @param string $ans 原问题答案
 * @param int $new_verify_problem 新问题id
 * @param string $new_verify_ans 新问题答案
 * @param string $reason 失败原因
 * @param string $value
 * @return bool 操作结果
 */
function changeVerifyProblem($ans, $new_verify_problem, $new_verify_ans, & $reason, & $value)
{
    $success = true;
    $info = getUserInfo($_SESSION['user_id']);
    if(empty($info))
    {
        $reason = '用户不存在';
        goto fail;
    }
    else if($info['problem_answer'] != $ans)
    {
        $value = 'vans';
        $reason = '原问题答案错误';
    }
    else if(!existVerifyProblem($new_verify_problem))
    {
        $value = 'np';
        $reason = '新问题ID非法';
    }
    else if($info['problem_answer'] == $new_verify_ans && $info['verify_problem_id'] == $new_verify_problem)
    {
        $value = 'nvans';
        $reason = '新旧问题答案一样';
    }
    else
        goto success;

    fail:
    $success = false;
    goto end;
    
    success:
    global $conn;
    $stmt = $conn->prepare('UPDATE account SET verify_problem_id = ?, problem_answer = ? WHERE id = ?');
    $stmt->bind_param('isi', $new_verify_problem, $new_verify_ans, $_SESSION['user_id']);
    $stmt->execute();
    if($stmt->affected_rows > 0)
        goto end;
    $reason = $stmt->error;
    goto fail;

    end:
    return $success;
}

/**
 * 增加登录记录
 */
function newLoginRecord()
{
    global $conn;
    $stmt = $conn->prepare('INSERT INTO login_record (time, user_id, ip) VALUE (?, ?, ?)');
    $time = time();
    $ip = $_SERVER['REMOTE_ADDR'];
    if( isset($_SERVER['HTTP_X_FORWARDED_FOR']) )
        $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
    $stmt->bind_param('iis', $time, $_SESSION['user_id'], $ip);
    $stmt->execute();
    $stmt->close();
}

/**
 * 用户登录
 * @param $username
 * @param $password
 * @param $reason
 * @param $data
 * @return bool
 */
function login($username, $password, & $reason, & $data)
{
    $info = getUserInfo(null, $username);
    if(empty($info))
    {
        $data = 'u';
        $reason = '用户不存在';
    }
    else if($info['password'] != md5($password))
    {
        $data = 'p';
        $reason = '密码错误';
    }
    else if(!$info['state'])
    {
        $reason = '账户被封禁';
    }
    else
        goto success;

    fail:
    return false;

    success:
    newLoginRecord();
    $_SESSION['role'] = 0;
    $_SESSION['user_id'] = $info['id'];
    return true;
}

/**
 * 获取仓库信息
 * @return array
 */
function getWarehouseInfo()
{
    $i = [];
    if(!isset($_SESSION['user_id']))
        return $i;
    global $conn;
    $stmt = $conn->prepare('SELECT gold, play_count, resurrection FROM warehouse WHERE user_id = ?');
    $stmt->bind_param('i', $_SESSION['user_id']);
    $stmt->execute();
    $stmt->store_result();
    if($stmt->num_rows > 0)
    {
        $stmt->bind_result($i['gold'], $i['play_count'], $i['resurrection']);
        $stmt->fetch();
    }
    $stmt->close();
    return $i;
}

/**
 * 设置仓库数据
 * @param double $gold 金币
 * @param int $play_count 玩的次数
 * @param int $resurrection 复活次数
 * @return bool
 */
function setWarehouse($gold, $play_count, $resurrection)
{
    $success = false;
    if(!isset($_SESSION['user_id']))
        goto end;
    global $conn;
    if(empty(getWarehouseInfo()))
    {
        // 新用户
        $stmt = $conn->prepare('INSERT INTO warehouse (user_id, gold, play_count, resurrection) VALUE (?, ?, ?, ?)');
        $stmt->bind_param('idii', $_SESSION['user_id'], $gold, $play_count, $resurrection);
        $stmt->execute();
        $success = ($stmt->affected_rows > 0);
        $stmt->close();
    }
    else
    {
        $stmt = $conn->prepare('UPDATE warehouse SET gold = ?, play_count = ?, resurrection = ? WHERE user_id = ?');
        $stmt->bind_param('diii', $gold, $play_count, $resurrection, $_SESSION['user_id']);
        $stmt->execute();
        $success = ($stmt->affected_rows > 0);
        $stmt->close();
    }
    end:
    return $success;
}

/**
 * 获取充值商品信息
 * @param int $id
 * @return array
 */
function getRechargeInfo($id)
{
    global $conn;
    $stmt = $conn->prepare('SELECT pay, amount FROM recharge_list WHERE id = ?');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $info = [];
    if($stmt->num_rows > 0)
    {
        $stmt->bind_result($info['pay'], $info['amount']);
        $stmt->fetch();
    }
    $stmt->close();
    return $info;
}

/**
 * 充值
 * @param int $recharge_id 充值商品ID
 * @param double $final 实际付款金额
 * @param int $way 付款渠道（0/支付宝 1/微信
 * @param string $reason 失败原因
 * @return bool
 */
function recharge($recharge_id, $final, $way, & $reason)
{
    $success = false;
    $r = getRechargeInfo($recharge_id);
    if(empty($r))
    {
        $reason = '充值商品类型非法';
        goto end;
    }
    global $conn;
    $stmt = $conn->prepare('INSERT INTO recharge_record (time, user_id, original_price, final_pay, pay_way, get_gold) VALUE (?, ?, ?, ?, ?, ?)');
    $time = time();
    $stmt->bind_param('iiddii', $time, $_SESSION['user_id'], $r['pay'], $final, $way, $r['amount']);
    $success = $stmt->execute();
    if(!$success)
        $reason = $stmt->error;
    else
    {
        $w = getWarehouseInfo();
        $w['gold'] += $r['amount'];
        setWarehouse($w['gold'], $w['play_count'], $w['resurrection']);
    }
    end:
    return $success;
}

/**
 * 购买商品
 * @param int $id
 * @param string $reason
 * @return bool
 */
function buyCommodity($id, & $reason)
{
    $info = getCommodityInfo($id);
    $account = getWarehouseInfo();
    if(empty($info))
        $reason = '商品不存在';
    else if($info['state'] === 0)
        $reason = '商品已下线';
    else if($info['pay'] > $account['gold'])
        $reason = '金币不足';
    else
        goto success;

    fail:
    $success = false;
    goto end;

    success:
    $account['gold'] -= $info['pay'];
    switch ($info['prop'])
    {
        case 0:
            // 体力
            $account['play_count'] += $info['amount'];
            break;
        case 1:
            // 复活次数
            $account['resurrection'] += $info['amount'];
            break;
    }
    // 添加消费记录
    global $conn;
    $stmt = $conn->prepare('INSERT INTO consume_record (time, user_id, amount, commodity_id) VALUE (?, ?, ?, ?)');
    $time = time();
    $stmt->bind_param('iiii', $time, $_SESSION['user_id'], $info['pay'], $id);
    $success = $stmt->execute();
    if($success)
        setWarehouse($account['gold'], $account['play_count'], $account['resurrection']);
    else
        $reason = $stmt->error;

    end:
    return $success;
}

/**
 * 添加游戏记录
 * @param int $score 分数
 * @param string $reason
 * @return bool
 */
function addPlayRecord($score, & $reason)
{
    $success = false;
    $wInfo = getWarehouseInfo();
    if(--$wInfo['play_count'] < 0)
    {
        $reason = '没有体力了';
        goto end;
    }
    $time = time();
    global $conn;
    $stmt = $conn->prepare("INSERT INTO play_record (user_id, play_time, score) VALUE (?, ?, ?)");
    $stmt->bind_param('iii', $_SESSION['user_id'], $time, $score);
    $success = $stmt->execute();
    $stmt->close();
    if($success)
        setWarehouse($wInfo['gold'], $wInfo['play_count'], $wInfo['resurrection']);
    else
        $reason = $stmt->error;
    end:
    return $success;
}

/**
 * 获取排行榜
 * @return array
 */
function getRank()
{
    $lastWeek = mktime(0, 0, 0, date('m'), date('d'), date('Y')) - 6 * 24 * 60 * 60;
    global $conn;
    $stmt = $conn->prepare('SELECT user_id, username, score from account, (SELECT user_id, MAX(score) as score FROM play_record WHERE play_time > ? GROUP BY user_id) tmp WHERE tmp.user_id = account.id ORDER BY tmp.score DESC');
    $stmt->bind_param('i', $lastWeek);
    $stmt->execute();
    $stmt->store_result();
    $i = [];
    $stmt->bind_result($i['id'], $i['name'], $i['score']);
    $seq = 0;
    $rankList = [];
    while($stmt->fetch())
    {
        $seq++;
        if($i['id'] == $_SESSION['user_id'])
            $i['name'] = '我';
        else if($seq > 10)
            continue;
        $rankList[] = [
            'seq' => $seq,
            'name' => $i['name'],
            'score' => $i['score'],
        ];
    }
    return $rankList;
}

/**
 * 获取协议内容
 * @return string
 */
function getPactContent()
{
    global $conn;
    $stmt = $conn->prepare('SELECT content FROM setting WHERE name = ?');
    $str = 'pact';
    $stmt->bind_param('s', $str);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($content);
    $stmt->fetch();
    $stmt->close();
    return $content;
}

function getVerifyProblemID()
{
    $i = getUserInfo($_SESSION['user_id']);
    return $i['verify_problem_id'];
}

/**
 * 复活
 * @param array $data 新仓库数据
 * @param $reason
 * @return bool
 */
function revive(& $data, & $reason)
{
    $w = getWarehouseInfo();
    if($w['resurrection']-- <= 0)
    {
        $reason = '复活道具不足';
        return false;
    }
    setWarehouse($w['gold'], $w['play_count'], $w['resurrection']);
    $data = $w;
    return true;
}
