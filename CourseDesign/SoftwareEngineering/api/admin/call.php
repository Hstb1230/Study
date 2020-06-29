<?php

include_once '../util.php';

$fun = @$_REQUEST['to'];

include_once '../db.php';

if(!defined('SQL_SERVER')) exit;
include_once 'fnc.php';

$success = true;
$reason = null;
$data = null;

if($fun === 'portal')
{
    if(!arrIsset($_REQUEST, ['u', 'p']))
        goto fail;
    $username = $_REQUEST['u'];
    $password = $_REQUEST['p'];
    $success = portal($username, $password, $reason, $data);
}
else if($fun === 'isLogin')
{
    $data = isLogin();
}
else if(!isLogin())
{
    $success = false;
    $reason = '请先登录';
}
else if($fun === 'logout')
{
    $success = logout();
}
else if($fun === 'changePassword')
{
    if(!arrIsset($_REQUEST, ['p', 'np']))
        goto fail;
    $password = $_REQUEST['p'];
    $newPassword = $_REQUEST['np'];
    $success = changePassword($password, $newPassword, $reason, $data);
}
else if($fun === 'getUserList')
{
    $data = getUserList();
}
else if($fun === 'getUserRechargeRecord')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $data = getRechargeRecord($u);
}
else if($fun === 'getUserConsumeRecord')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $data = getUserConsumeRecord($u);
}
else if($fun === 'getUserPlayRecord')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $data = getUserPlayRecord($u);
}
else if($fun === 'banUser')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $success = banUser($u, $reason);
}
else if($fun === 'unBanUser')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $success = unBanUser($u, $reason);
}
else if($fun === 'resetUserPassword')
{
    if(!arrIsset($_REQUEST, ['u', 'np']))
        goto fail;
    $u = $_REQUEST['u'];
    $np = $_REQUEST['np'];
    $success = resetUserPassword($u, $np, $reason);
}
else if($fun === 'getRechargeRecord')
{
    $data = getRechargeRecord();
}
else if($fun === 'getCommodityList')
{
    $data = getCommodityList();
}
else if($fun === 'banCommodity')
{
    if(!arrIsset($_REQUEST, ['id']))
        goto fail;
    $id = $_REQUEST['id'];
    $success = banCommodity($id, $reason);
}
else if($fun === 'unBanCommodity')
{
    if(!arrIsset($_REQUEST, ['id']))
        goto fail;
    $id = $_REQUEST['id'];
    $success = unBanCommodity($id, $reason);
}
else if($fun === 'setCommodity')
{
    if(!arrIsset($_REQUEST, ['id', 'prop', 'amount', 'gold']))
        goto fail;
    $success = setCommodity(intval($_REQUEST['id']), $_REQUEST['prop'], $_REQUEST['amount'], $_REQUEST['gold']);
}
else if($fun === 'getRechargeList')
{
    $data = getRechargeList();
}
else if($fun === 'setRecharge') {
    if(!arrIsset($_REQUEST, ['id', 'amount', 'pay']))
        goto fail;
    $success = setRecharge(intval($_REQUEST['id']), $_REQUEST['amount'], $_REQUEST['pay']);
}
else
{
    fail:
    $success = false;
    $reason= 'wrong parameter';
    $data = $_REQUEST;
}

if($success)
    createResponse(200, $reason, $data);
else
    createResponse(400, $reason, $data);