<?php
// 注册账户
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['u', 'p', 'vid', 'vans']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;
include_once 'fnc.php';

$username = $_REQUEST['u'];
$password = $_REQUEST['p'];
$verify_problem_id = $_REQUEST['vid'];
$verify_answer = $_REQUEST['vans'];

$factor = '';
if(!register($username, $password, $verify_problem_id, $verify_answer, $factor))
    createResponse(400, $factor);


createResponse(200, '注册成功');
