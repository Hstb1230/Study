<?php /** @noinspection SpellCheckingInspection */

define('SQL_SERVER', 'localhost');
define('SQL_USER', 'game');
define('SQL_PWD', 'emag');
define('SQL_DB', 'game');

$conn = new mysqli(SQL_SERVER, SQL_USER, SQL_PWD, SQL_DB);
if ($conn->connect_error)
    createResponse(500, $conn->connect_error);
$conn->query("set names 'utf8'");

session_start();
