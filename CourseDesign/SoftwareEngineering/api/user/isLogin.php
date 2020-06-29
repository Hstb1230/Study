<?php
include_once '../util.php';
include_once '../db.php';
createResponse(200, @$_SESSION['role'] === 0, $_SESSION);