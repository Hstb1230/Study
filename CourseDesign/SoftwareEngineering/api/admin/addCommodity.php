<?php
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['prop', 'amount', 'pay']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$prop = $_REQUEST['prop'];
$amount = $_REQUEST['amount'];
$pay = $_REQUEST['pay'];

$reason = '';
if(addCommodity($prop, $amount, $pay, $reason))
    createResponse(200, 'success');
else
    createResponse(400, $reason);