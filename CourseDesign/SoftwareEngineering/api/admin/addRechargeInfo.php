<?php

include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['p', 'a']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;
include_once 'fnc.php';

$pay = $_REQUEST['p'];
$amount = $_REQUEST['a'];
addRechargeInfo($pay, $amount);
createResponse(200, '添加成功');
