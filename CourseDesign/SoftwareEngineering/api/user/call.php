<?php
include_once '../inc.php';
include_once 'fnc.php';

$fun = @$_REQUEST['to'];

$success = true;
$reason = 'success';
$data = null;

if($fun === 'isLogin')
{
    $success = isLogin();
    $data = $_SESSION;
}
else if($fun === 'getPactContent')
{
    $data = getPactContent();
}
else if($fun === 'getVerifyProblemList')
{
    $data = getVerifyProblemList();
}
else if($fun === 'register')
{
    if(!arrIsset($_REQUEST, ['u', 'p', 'vid', 'vans']))
        goto fail;
    else if(isLogin())
        goto fail;
    $username = $_REQUEST['u'];
    $password = $_REQUEST['p'];
    $verify_problem_id = $_REQUEST['vid'];
    $verify_answer = $_REQUEST['vans'];
    $success = register($username, $password, $verify_problem_id, $verify_answer, $reason);
}
else if($fun === 'userExist')
{
    if(!arrIsset($_REQUEST, ['u']))
        goto fail;
    $data = existUser($_REQUEST['u']);
}
else if($fun === 'login')
{
    if(!arrIsset($_REQUEST, ['u', 'p']))
        goto fail;
    $username = $_REQUEST['u'];
    $password = $_REQUEST['p'];

    $success = login($username, $password, $reason, $data);
}
else if($fun === 'resetPassword')
{
    if(!arrIsset($_REQUEST, ['u', 'vid', 'vans', 'np']))
        goto fail;
    $username = $_REQUEST['u'];
    $verify_problem_id = $_REQUEST['vid'];
    $verify_answer = $_REQUEST['vans'];
    $new_password = $_REQUEST['np'];
    $success = resetPassword($username, $verify_problem_id, $verify_answer, $new_password, $reason, $data);
}
else if(!isLogin())
{
    $success = false;
    $reason = '请先登录';
}
else if($fun === 'logout')
{
    logout();
}
else if($fun === 'changePassword')
{
    if(!arrIsset($_REQUEST, ['p', 'np']))
        goto fail;
    $password = md5($_REQUEST['p']);
    $new_password = $_REQUEST['np'];
    $success = changeUserPassword($password, $new_password, $reason, $data);
}
else if($fun === 'changeVerifyProblem')
{
    if(!arrIsset($_REQUEST, ['vans', 'nvp', 'nvans']))
        goto fail;
    $ans = $_REQUEST['vans'];
    $new_verify_problem = $_REQUEST['nvp'];
    $new_verify_ans = $_REQUEST['nvans'];

    $success = changeVerifyProblem($ans, $new_verify_problem, $new_verify_ans, $reason, $data);
}
else if($fun === 'getVerifyProblemID')
{
    $data = getUserVerifyProblemID();
}
else if($fun === 'getWarehouseInfo')
{
    $data = getWarehouseInfo();
}
else if($fun === 'rank')
{
    $data = getRank();
}
else if($fun === 'getCommodityList')
{
    $data = getCommodityList();
}
else if($fun === 'buyCommodity')
{
    if(!arrIsset($_REQUEST, ['cid']))
        goto fail;
    $id = $_REQUEST['cid'];
    $success = buyCommodity($id, $reason);
}
else if($fun === 'getConsumeRecord')
{
    $data = getUserConsumeRecord($_SESSION['user_id']);
}
else if($fun === 'getRechargeList')
{
    $data = getRechargeList();
}
else if($fun === 'getRechargeRecord')
{
    $data = getUserRechargeRecord($_SESSION['user_id']);
}
else if($fun === 'recharge')
{
    if(!arrIsset($_REQUEST, ['rid', 'fp', 'pw']))
        goto fail;
    $recharge_id = $_REQUEST['rid'];
    $final_pay = $_REQUEST['fp'];
    $pay_way = $_REQUEST['pw'];
    $success = recharge($recharge_id, $final_pay, $pay_way, $reason);
}
//    复活
else if($fun === 'revive')
{
    $success = revive($data, $reason);
}
else if($fun === 'addPlayRecord')
{
    if(!arrIsset($_REQUEST, ['score']))
        goto fail;
    $success = addPlayRecord($_REQUEST['score'], $reason);
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
