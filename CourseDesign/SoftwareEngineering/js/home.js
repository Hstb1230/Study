if(account.isLogin)
{
    $('.tab .default').style.display = 'none';
    $('.tab .home').style.display = 'black';
}

// 点击空白区域关闭悬浮窗（隐藏）
document.addEventListener('click',
    function ()
    {
        $('.float').style.display = 'none';
    }
);

$('.float .container').addEventListener('click',
    function (e)
    {
        e.stopPropagation();
        return false;
    }
);
