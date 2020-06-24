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