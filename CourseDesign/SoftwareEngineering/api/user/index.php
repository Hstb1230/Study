<?php
// TEST
include_once '../util.php';
// 检验数据
if(!arrIsset($_REQUEST, ['u']))
    createResponse(400, 'wrong parameter', $_REQUEST);

include_once '../db.php';
if(!defined('SQL_SERVER')) exit;
include_once 'fnc.php';

$username = $_REQUEST['u'];

createResponse(200, empty(getUserInfo($username)));