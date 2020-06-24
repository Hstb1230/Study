<?php
// 充值
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['rid', 'fp', 'pw']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$recharge_id = $_REQUEST['rid'];
$final_pay = $_REQUEST['fp'];
$pay_way = $_REQUEST['pw'];

$resaon = '';

if(recharge($recharge_id, $final_pay, $pay_way, $reason))
    createResponse(200, 'success');
else
    createResponse(400, $reason);