let home = $('.main .home');

function loadHomeResource()
{
    fetch('/api/user/getWarehouseInfo.php')
        .then( res => res.json() )
        .then( res => res.data )
        .then( info => {
            let prop = home.querySelector('.prop');
            prop.querySelector('.gold p').innerHTML = info['gold'];
            prop.querySelector('.power p').innerHTML = info['play_count'];
        })
}

function floatOfSetting()
{
    let div = $make('div');
    div.innerHTML = `
        <h3>声音设置</h3>
        <div class="music">
            <label>
                <input type="checkbox" name="musicOfBackground" checked>
                背景音乐
            </label>
            <label>
                <input type="checkbox" name="musicOfGame" checked>
                游戏音效
            </label>
        </div>
        <h3>账号设置</h3>
        <div class="s-acc">
            <div class="change-password">修改密码</div>
            <div class="change-verify-problem">修改密保问题</div>
            <div class="exit">退出登录</div>
        </div>
    `;
    setFloat(div, 'setting');
    return false;
}

function floatOfRank()
{
    setFloat('排行榜');
    return false;
}

function floatOfStore()
{
    setFloat('商店');
    return false;
}

function floatOfRecharge()
{
    setFloat('充值');
    return false;
}