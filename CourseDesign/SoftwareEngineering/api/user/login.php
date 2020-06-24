<?php

include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['u', 'p']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
include_once 'fnc.php';

$username = $_REQUEST['u'];
$password = $_REQUEST['p'];

if(login($username, $password, $factor))
    createResponse(200, 'success');
else
    createResponse(400, $factor);
