<?php

include_once '../util.php';
include_once '../db.php';
if(!defined('SQL_SERVER')) exit;

include_once 'fnc.php';

$reason = $data = null;

if(revive($data, $reason))
    createResponse(200, 'success', $data);
else
    createResponse(400, $reason, $data);
