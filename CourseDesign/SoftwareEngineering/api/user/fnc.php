<?php
if(!isset($conn)) exit;

function getUserInfo($username)
{
    global $conn;

    $stmt = $conn->prepare('SELECT id, password, create_time, verify_problem_id, problem_answer FROM account WHERE username = ?');
    $stmt->bind_param('s', $username);
    $stmt->execute();
    $stmt->store_result();

    $info = [];
    if($stmt->num_rows > 0)
    {
        $info['username'] = $username;
        $stmt->bind_result(
            $info['id'],
            $info['password'],
            $info['create_time'],
            $info['verify_problem_id'],
            $info['problem_answer']
        );
        $stmt->fetch();
    }
    $stmt->close();
    return $info;
}

function getUserInfoByID($id)
{
    global $conn;

    $stmt = $conn->prepare('SELECT username, password, create_time, verify_problem_id, problem_answer FROM account WHERE id = ?');
    $stmt->bind_param('s', $id);
    $stmt->execute();
    $stmt->store_result();

    $info = [];
    if($stmt->num_rows > 0)
    {
        $info['id'] = $id;
        $stmt->bind_result(
            $info['username'],
            $info['password'],
            $info['create_time'],
            $info['verify_problem_id'],
            $info['problem_answer']
        );
        $stmt->fetch();
    }
    $stmt->close();
    return $info;
}

/**
 * 是否存在用户
 * @param string $username
 * @return bool
 */
function existUser($username)
{
    return !empty(getUserInfo($username));
}

function getUserID($username)
{
    return (int)(@getUserInfo($username)['id']);
}

/**
 * 验证问题是否存在
 * @param int $problem_id 问题id
 * @return bool
 */
function existVerifyProblem($problem_id)
{
    global $conn;
    $stmt = $conn->prepare('SELECT count(*) FROM verify_problem WHERE id = ?');
    $stmt->bind_param('i', $problem_id);
    $stmt->execute();
    $stmt->store_result();

    $count = 0;
    $stmt->bind_result($count);
    $stmt->fetch();
    $stmt->close();

    return $count === 1;
}

/**
 * 注册
 * @param string $username 用户名
 * @param string $password 密码
 * @param integer $verify_problem_id 验证问题id
 * @param string $verify_answer 验证问题答案
 * @param string $factor 失败原因
 * @return bool 注册结果
 */
function register($username, $password, $verify_problem_id, $verify_answer, &$factor)
{
    if(existUser($username))
    {
        $factor = '已存在用户';
        return false;
    }
    if(!existVerifyProblem($verify_problem_id))
    {
        $factor = '问题ID非法';
        return false;
    }
    if(strlen($username) < 3)
    {
        $factor = '用户名太短';
        return false;
    }
    if(strlen($password) < 3)
    {
        $factor = '密码太短';
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
        $factor = $stmt->error;
    $stmt->close();
    return $isSuccess;
}

function logout()
{
    unset($_SESSION['role'], $_SESSION['user_id']);
}

/**
 * 重置密码
 * @param string $username 用户名
 * @param int $verify_problem_id 密保问题ID
 * @param string $verify_ans 密保问题答案
 * @param string $new_password 新密码
 * @param string $reason 失败原因
 * @return bool
 */
function resetPassword($username, $verify_problem_id, $verify_ans, $new_password, & $reason)
{
    $success = false;
    $info = getUserInfo($username);
    if(empty($info))
    {
        $reason = '不存在用户';
        goto end;
    }

    if($info['verify_problem_id'] != (int)$verify_problem_id)
    {
        $reason = '问题或答案错误';
        goto end;
    }

    if($info['problem_answer'] != $verify_ans)
    {
        $reason = '问题或答案错误';
        goto end;
    }

    $new_password = md5($new_password);
    global $conn;
    $stmt = $conn->prepare('UPDATE account SET password = ? WHERE id = ?');
    $stmt->bind_param('si', $new_password, $info['id']);
    $stmt->execute();
    if($stmt->affected_rows > 0)
        $success = true;
    else
        $reason = '没有对应用户';
    end:
    return $success;
}

/**
 * 修改密保问题
 * @param string $ans 原问题答案
 * @param int $new_verify_problem 新问题id
 * @param string $new_verify_ans 新问题答案
 * @param string $factor 失败原因
 * @return bool 操作结果
 */
function changeVerifyProblem($ans, $new_verify_problem, $new_verify_ans, & $factor)
{
    $success = true;
    if(!isset($_SESSION['user_id']))
    {
        $factor = '请先登录';
        goto fail;
    }
    $info = getUserInfoByID($_SESSION['user_id']);
    if(empty($info))
    {
        $factor = '用户不存在';
        goto fail;
    }
    else if($info['problem_answer'] != $ans)
    {
        $factor = '原问题答案错误';
    }
    else if(!existVerifyProblem($new_verify_problem))
    {
        $factor = '新问题ID非法';
    }
    else if($info['problem_answer'] == $new_verify_ans && $info['verify_problem_id'] == $new_verify_problem)
    {
        $factor = '新旧问题一样';
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
    $factor = $stmt->error;
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
    $stmt->bind_param('iis', $time, $_SESSION['user_id'], $_SERVER['HTTP_X_FORWARDED_FOR']);
    $stmt->execute();
    $stmt->close();
}

function login($username, $password, & $factor)
{
    $info = getUserInfo($username);
    if(empty($info))
    {
        $factor = '用户不存在';
    }
    else if($info['password'] != md5($password))
    {
        $factor = '密码错误';
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
    $info = getRechargeInfo($recharge_id);
    if(empty($info))
    {
        $reason = '充值商品类型非法';
        goto end;
    }
    global $conn;
    $stmt = $conn->prepare('INSERT INTO recharge_record (time, user_id, original_price, final_pay, pay_way, get_gold) VALUE (?, ?, ?, ?, ?, ?)');
    $time = time();
    $stmt->bind_param('iiddii', $time, $_SESSION['user_id'], $info['pay'], $final, $way, $info['amount']);
    $success = $stmt->execute();
    if(!$success)
        $reason = $stmt->error;

    end:
    return $success;
}

/**
 * 获取充值记录
 * @return array
 */
function getRechargeRecord()
{
    $recordList = [];
    global $conn;
    $stmt = $conn->prepare('SELECT time, original_price, final_pay, pay_way, get_gold FROM recharge_record WHERE user_id = ?');
    $stmt->bind_param('i', $_SESSION['user_id']);
    $stmt->execute();
    $stmt->bind_result($time, $ori_price, $fin_pay, $pay_way, $gold);
    while($stmt->fetch())
    {
        $recordList[] = [
            'time' => $time,
            'ori_price' => $ori_price,
            'final_pay' => $fin_pay,
            'pay_way' => $pay_way,
            'gold' => $gold
        ];
    }
    return $recordList;
}

function getCommodityInfo($id)
{
    global $conn;
    $stmt = $conn->prepare('SELECT state, prop_type, amount, pay FROM commodity WHERE id = ?');
    $stmt->bind_param('i', $id);
    $stmt->execute();
    $stmt->store_result();
    $i = [];
    if($stmt->num_rows > 0)
    {
        $stmt->bind_result($i['state'], $i['prop'], $i['amount'], $i['pay']);
        $stmt->fetch();
    }
    $stmt->close();
    return $i;
}

/**
 * 购买商品
 * @param int $id
 * @param string $reason
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
 * 获取消费记录
 * @return array
 */
function getConsumeRecord()
{
    $recordList = [];
    global $conn;
    $stmt = $conn->prepare('SELECT time, amount, commodity_id FROM consume_record WHERE user_id = ?');
    $stmt->bind_param('i', $_SESSION['user_id']);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($time, $amount, $com_id);
    while($stmt->fetch())
    {
        $cInfo = getCommodityInfo($com_id);
        $recordList[] = [
            'time' => $time,
            'pay' => $amount,
            'prop' => $cInfo['prop'],
            'amount' => $cInfo['amount']
        ];
    }
    return $recordList;
}

/**
 * 添加分数
 * @param int $score 分数
 * @param string $reason
 * @return bool
 */
function addPlayRecord($score, & $reason)
{
    $success = false;
    $wInfo = getWarehouseInfo();
    $wInfo['play_count']--;
    if($wInfo['play_count']-- <= 0)
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
        if($seq > 10 && ($i['id'] != $_SESSION['user_id']))
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

function getVerifyProblemList()
{
    global $conn;
    $stmt = $conn->prepare('SELECT id, content FROM verify_problem');
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