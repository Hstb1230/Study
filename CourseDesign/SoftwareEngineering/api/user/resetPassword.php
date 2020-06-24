<?php
// 重置密码
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['u', 'vid', 'vans', 'p']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$username = $_REQUEST['u'];
$verify_problem_id = $_REQUEST['vid'];
$verify_answer = $_REQUEST['vans'];
$new_password = $_REQUEST['p'];
$factor = '重置成功';

if(resetPassword($username, $verify_problem_id, $verify_answer, $new_password, $factor))
    createResponse(200, 'success');
else
    createResponse(400, $factor);
