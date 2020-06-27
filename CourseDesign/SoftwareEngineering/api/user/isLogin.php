<?php
include_once '../util.php';
include_once '../db.php';
createResponse(200, !empty($_SESSION), $_SESSION);