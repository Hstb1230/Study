<?php

include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['score']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$score = $_REQUEST['score'];
$reason = '';
if(addPlayRecord($score, $reason))
    createResponse(200, 'success');
else
    createResponse(400, $reason);