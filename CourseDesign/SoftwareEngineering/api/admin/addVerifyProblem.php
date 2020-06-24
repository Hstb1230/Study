<?php

include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['c']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;
include_once 'fnc.php';

$content = $_REQUEST['c'];
addVerifyProblem($content, $reason);
createResponse(200, '添加成功');
