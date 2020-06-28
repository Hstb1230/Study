<?php
// 修改密码
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['p', 'np']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$password = md5($_REQUEST['p']);
$new_password = $_REQUEST['np'];
$reason = '重置成功';

if(changePassword($password, $new_password, $reason, $value))
    createResponse(200, 'success');
else
    createResponse(400, $reason, $value);
