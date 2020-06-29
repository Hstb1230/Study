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

/**
 * 增加充值定价信息
 * @param double $pay 所需金额
 * @param int $amount 金币数量
 * @return bool
 */
function addRechargeInfo($pay, $amount)
{
    global $conn;
    $stmt = $conn->prepare('INSERT INTO recharge_list (pay, amount) VALUE (?, ?)');
    $stmt->bind_param('di', $pay, $amount);
    $stmt->execute();
    $stmt->close();
    return true;
}

/**
 * 增加商品
 * @param int $prop 商品类型：0/体力，1/金币
 * @param int $amount 数量
 * @param int $pay 所需金币
 * @param $reason
 * @return bool
 */
function addCommodity($prop, $amount, $pay, & $reason)
{
    global $conn;
    $stmt = $conn->prepare('INSERT INTO commodity (publish_time, prop_type, amount, pay) VALUE (?, ?, ?, ?)');
    $time = time();
    $stmt->bind_param('iiii', $time, $prop, $amount, $pay);
    $success = $stmt->execute();
    if(!$success)
        $reason = $stmt->error;
    return $success;
}

/**
 * 登录验证
 * @param string $username
 * @param string $password
 * @param string $reason
 * @return bool
 */
function portal($username, $password, & $reason)
{
    global $conn;
    $stmt = $conn->prepare('SELECT content FROM `setting` WHERE name = ? UNION SELECT content FROM `setting` WHERE name = ?');
    $var1 = 'username';
    $var2 = 'password';
    $stmt->bind_param('ss', $var1, $var2);
    $stmt->execute();
    $stmt->store_result();
    if($stmt->num_rows === 2)
    {
        $content = '';
        $stmt->bind_result($content);
        $stmt->fetch();
        if($username !== $content)
        {
            $reason = '用户名错误';
            goto end;
        }
        $stmt->fetch();
        if($password !== $content)
        {
            $reason = '密码错误';
            goto end;
        }
        $_SESSION['role'] = 1;
        return true;
    }
    $reason = '记录不存在';
    end:
    return false;
}

function isLogin()
{
    return @$_SESSION['role'] === 1;
}
