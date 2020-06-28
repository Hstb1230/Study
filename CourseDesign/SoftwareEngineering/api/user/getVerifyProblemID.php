<?php

include_once '../util.php';
include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';
createResponse(200, 'success', getVerifyProblemID());
