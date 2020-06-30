<?php

include_once '../inc.php';
include_once 'fnc.php';

$fun = @$_REQUEST['to'];

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
    $data = isPortal();
}
else if(!isPortal())
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
    $success = changeAdminPassword($password, $newPassword, $reason, $data);
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
    $data = getUserRechargeRecord($u);
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
    $success = setUserState($u, false, $reason);
}
else if($fun === 'unBanUser')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $u = $_REQUEST['u'];
    $success = setUserState($u, true, $reason);
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
    $data = getUserRechargeRecord();
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
    $success = setCommodityState($id, false, $reason);
}
else if($fun === 'unBanCommodity')
{
    if(!arrIsset($_REQUEST, ['id']))
        goto fail;
    $id = $_REQUEST['id'];
    $success = setCommodityState($id, true, $reason);
}
else if($fun === 'setCommodity')
{
    if(!arrIsset($_REQUEST, ['id', 'prop', 'amount', 'gold']))
        goto fail;
    $success = setCommodityInfo(intval($_REQUEST['id']), $_REQUEST['prop'], $_REQUEST['amount'], $_REQUEST['gold'], $reason);
}
else if($fun === 'getRechargeList')
{
    $data = getRechargeList();
}
else if($fun === 'setRecharge') {
    if(!arrIsset($_REQUEST, ['id', 'amount', 'pay']))
        goto fail;
    $success = setRechargeInfo(intval($_REQUEST['id']), $_REQUEST['amount'], $_REQUEST['pay'], $reason);
}
else if($fun === 'setVerifyProblem')
{
    if(!arrIsset($_REQUEST, ['id', 'content']))
        goto fail;
    $success = setVerifyProblem(intval($_REQUEST['id']), $_REQUEST['content'], $reason);
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