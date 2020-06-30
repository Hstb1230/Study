<?php

function createResponse($ret_code, $ret_msg, $ret_data = [])
{
    $message = [
        'code' => $ret_code,
        'msg' => $ret_msg,
        'data' => $ret_data
    ];
    if($ret_code != 200)
    {
        unset($message['msg']);
        $message['err_msg'] = $ret_msg;
    }
    echo json_encode($message);
    exit;
}

function arrIsset($arr, $keyList)
{
    foreach($keyList as $key)
    {
        if($key === '' || !isset($arr[$key]) || is_array($arr[$key]) || $arr[$key] === '')
            return false;
    }
    return true;
}

