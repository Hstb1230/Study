<?php

include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['cid']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$com_id = $_REQUEST['cid'];
$reason = '';
if(buyCommodity($com_id, $reason))
    createResponse(200, 'success');
else
    createResponse(400, $reason);