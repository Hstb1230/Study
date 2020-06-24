<?php
// 修改密保问题
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['ans', 'nvp', 'nvans']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$ans = $_REQUEST['ans'];
$new_verify_problem = $_REQUEST['nvp'];
$new_verify_ans = $_REQUEST['nvans'];

$reason = '';
if(changeVerifyProblem($ans, $new_verify_problem, $new_verify_ans, $reason))
    createResponse(200, 'success');
else
    createResponse(400, $reason);
