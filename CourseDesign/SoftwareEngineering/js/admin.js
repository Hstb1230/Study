function login()
{
    let form = $('.login form');
    let req = {
        u : form.u.value,
        p : form.p.value,
    };
    submit(req, form, loadAdminResource);
    return false;
}

function changePassword()
{
    let form = $('.float .account form');
    let req = {
        p : (form.p.value),
        np : (form.np.value),
    };

    if( form.sp.value !== form.np.value )
    {
        reportInput(form.sp, '密码不一致');
        reportInput(form.np, '密码不一致');
        return false;
    }

    if( form.p.value === form.np.value )
    {
        reportInput(form.sp, '');
        reportInput(form.np, '新旧密码一样');
        return false;
    }

    submit(req, form, () =>
    {
        setFloat('修改成功，3s后自动关闭', null, closeFloat, 2000);
    });

    return false;
}

let viewOfChangeAdminPassword = '';
let viewOfResetUserPassword = '';

function loadAdminResource()
{
    $('.admin .login').classList.add('hide');
    $('.admin .index').classList.remove('hide');
    let getChangeAdminPasswordView = () => axios.get('/view/admin/changeAdminPassword.html');
    let getResetUserPasswordView = () => axios.get('/view/admin/resetUserPassword.html');
    axios.all([
        getChangeAdminPasswordView(),
        getResetUserPasswordView(),
    ]).then(
        axios.spread(
            ( changeAdminPasswordView, resetUserPasswordView ) =>
            {
                viewOfChangeAdminPassword = changeAdminPasswordView.data;
                viewOfResetUserPassword = resetUserPasswordView.data;
            },
        ),
    );
}

function floatOfChangeAdminPassword()
{
    if( viewOfChangeAdminPassword === '' )
    {
        setFloat('获取视图数据失败，请<a onclick="location.reload()">刷新网页</a>');
        return;
    }
    setFloat(viewOfChangeAdminPassword, 'account change-password');
    return false;
}

function floatOfLogout()
{
    submit(null, '/api/admin/call/logout', () =>
    {
        setFloat('已退出登录，3s后自动关闭', null, closeFloat, 2000);
        setTimeout(() =>
        {
            $('.admin .index').classList.add('hide');
            $('.admin .login').classList.remove('hide');
        }, 1500);
    });
    return false;
}

function floatOfManageUser()
{
    let e = $make('div');
    e.innerHTML = `
        <h3>用户管理</h3>
        <ul>
            <li>
                <div class="user" style="width: 100px;">用户名</div>
                <div class="time-reg" style="width: 100px;">注册时间</div>
                <div class="time-log" style="width: 180px;">上次登录时间</div>
                <div class="sum-recharge" style="width: 80px;">累计充值</div>
                <div class="opt">操作</div>
            </li>
        </ul>
    `;
    fetch('/api/admin/call/getUserList')
        .then(res => res.json())
        .then(res => res.data)
        .then(list =>
        {
            let ul = '';
            list.forEach(u =>
            {
                ul += `
                    <li ${u['state'] ? '' : 'style="color: gray"'}>
                        <div class="user" style="width: 100px;">${u['username']}</div>
                        <div class="time-reg" style="width: 100px;">${timestampToDateOnly(u['create_time'] * 1000, false)}</div>
                        <div class="time-log" style="width: 180px;">
                            ${
                    u['last_login_time'] > 0
                        ? timestampToDate(u['last_login_time'] * 1000)
                        : '从未登录'
                }
                        </div>
                        <div class="sum-recharge" style="width: 80px;">${u['recharge_sum']}</div>
                        <div class="opt"  ${u['state'] ? '' : 'style="color: black"'}>
                            <div onclick="floatOfUserRechargeRecord(${u['id']}, '${u['username']}')">充值<br>记录</div>
                            <div onclick="floatOfUserConsumeRecord(${u['id']}, '${u['username']}')">消费<br>记录</div>
                            <div onclick="floatOfPlayRecord(${u['id']}, '${u['username']}')">游戏<br>记录</div>
                            <div onclick="${u['state'] ? 'floatOfBanUser' : 'floatOfUnBanUser'}(${u['id']}, '${u['username']}')">${u['state'] ? '封禁' : '解禁'}<br>用户</div>
                            <div onclick="floatOfResetUserPassword(${u['id']}, '${u['username']}')">重置<br>密码</div>
                        </div>
                    </li>
                `;
            });
            e.querySelector('ul').innerHTML += ul;
        });
    setFloat(e, 'table user-manage');
}

function floatOfUserRechargeRecord( id, username )
{
    let e = $make('div');
    e.innerHTML = `
        <h3>${username}的充值记录</h3>
        <ul>
            <li>
                <div class="rec-time" style="width: 150px;">充值时间</div>
                <div class="rec-way" style="width: 50px;">渠道</div>
                <div class="rec-value" style="width: 100px;">金额</div>
            </li>
        </ul>
    `;
    fetch(
        '/api/admin/call/getUserRechargeRecord',
        getFetchInit({ u : id }),
    ).then(res => res.json())
     .then(res => res.data)
     .then(list =>
     {
         let ul = '';
         list.forEach(u =>
         {
             ul += `
                    <li>
                        <div class="rec-time" style="width: 150px;">${timestampToDate(u['time'])}</div>
                        <div class="rec-way" style="width: 50px;">${u['pay_way'] === 1 ? '支付宝' : '微信'}</div>
                        <div class="rec-value" style="width: 100px;">${u['final_pay']}</div>
                    </li>
                `;
         });
         e.querySelector('ul').innerHTML += ul;
     });
    floatActionAfterClose = floatOfManageUser;
    setFloat(e, 'table user-recharge');
}

function floatOfUserConsumeRecord( id, username )
{
    let e = $make('div');
    e.innerHTML = `
        <h3>${username}的消费记录</h3>
        <ul>
            <li>
                <div class="rec-time" style="width: 150px;">消费时间</div>
                <div class="rec-com" style="width: 100px;">商品</div>
                <div class="rec-gold" style="width: 50px;">金币</div>
            </li>
        </ul>
    `;
    fetch(
        '/api/admin/call/getUserConsumeRecord',
        getFetchInit({ u : id }),
    ).then(res => res.json())
     .then(res => res.data)
     .then(list =>
     {
         let ul = '';
         list.forEach(u =>
         {
             ul += `
                    <li>
                        <div class="rec-time" style="width: 150px;">${timestampToDate(u['time'])}</div>
                        <div class="rec-com" style="width: 100px;">${u['prop_type'] === 0 ? '体力' : '复活次数'} × ${u['prop_amount']}</div>
                        <div class="rec-gold" style="width: 50px;">${u['gold_amount']}</div>
                    </li>
                `;
         });
         e.querySelector('ul').innerHTML += ul;
     });
    floatActionAfterClose = floatOfManageUser;
    setFloat(e, 'table user-consume');
}

function floatOfPlayRecord( id, username )
{
    let e = $make('div');
    e.innerHTML = `
        <h3>${username}的游戏记录</h3>
        <ul>
            <li>
                <div class="play-time" style="width: 150px;">消费时间</div>
                <div class="play-score" style="width: 50px;">分数</div>
            </li>
        </ul>
    `;
    fetch(
        '/api/admin/call/getUserPlayRecord',
        getFetchInit({ u : id }),
    ).then(res => res.json())
     .then(res => res.data)
     .then(list =>
     {
         let ul = '';
         list.forEach(u =>
         {
             ul += `
                    <li>
                        <div class="play-time" style="width: 150px;">${timestampToDate(u['time'])}</div>
                        <div class="play-score" style="width: 50px;">${u['score']}</div>
                    </li>
                `;
         });
         e.querySelector('ul').innerHTML += ul;
     });
    floatActionAfterClose = floatOfManageUser;
    setFloat(e, 'table user-play');
}

// noinspection JSUnusedGlobalSymbols
function floatOfBanUser( id, username )
{
    fetch(
        '/api/admin/call/banUser',
        getFetchInit({ u : id }),
    ).then(res => res.json())
     .then(res =>
     {
         let e;
         if( res.code === 200 )
             e = ('已封禁用户：' + username);
         else
             e = ('封禁用户失败：' + res['err_msg']);
         setFloat(e, null, floatOfManageUser, 2000);
     });
}

// noinspection JSUnusedGlobalSymbols
function floatOfUnBanUser( id, username )
{
    fetch(
        '/api/admin/call/unBanUser',
        getFetchInit({ u : id }),
    ).then(res => res.json())
     .then(res =>
     {
         let e;
         if( res.code === 200 )
             e = ('已解禁用户：' + username);
         else
             e = ('解禁用户失败：' + res['err_msg']);
         setFloat(e, null, floatOfManageUser, 2000);
     });
}

function resetPassword()
{
    let form = $('.float .account form');
    let req = {
        u : form.u.value,
        np : (form.np.value),
    };

    if( form.sp.value !== '' && form.sp.value !== form.np.value )
    {
        reportInput(form.sp, '密码不一致');
        reportInput(form.np, '密码不一致');
        return false;
    }

    submit(req, form, () =>
    {
        setFloat('重置成功，3s后自动关闭', null, floatOfManageUser, 2000);
    });

    return false;
}

function floatOfResetUserPassword( id, username )
{
    if( viewOfResetUserPassword === '' )
    {
        setFloat('获取视图数据失败，请<a onclick="location.reload()">刷新网页</a>');
        return;
    }
    let e = $make('div');
    e.innerHTML = viewOfResetUserPassword;
    e.querySelector('h3').innerText = `重置${ username }的密码`;
    e.querySelector('form').u.value = id;
    setFloat(e, 'account change-password reset-password', floatOfManageUser);
}

function floatOfRechargeRecord()
{
    let e = $make('div');
    e.innerHTML = `
        <h3>充值记录</h3>
        <ul>
            <li>
                <div class="rec-time" style="width: 150px;">充值时间</div>
                <div class="rec-user" style="width: 100px;">用户</div>
                <div class="rec-way" style="width: 50px;">渠道</div>
                <div class="rec-value" style="width: 100px;">金额</div>
            </li>
        </ul>
    `;
    fetch('/api/admin/call/getRechargeRecord')
        .then(res => res.json())
        .then(res => res.data)
        .then(list =>
        {
            let ul = '';
            list.forEach(u =>
            {
                ul += `
                    <li>
                        <div class="rec-time" style="width: 150px;">${timestampToDate(u['time'])}</div>
                        <div class="rec-user" style="width: 100px;">${u['user_name']}</div>
                        <div class="rec-way" style="width: 50px;">${u['pay_way'] === 1 ? '支付宝' : '微信'}</div>
                        <div class="rec-value" style="width: 100px;">${u['final_pay']}</div>
                    </li>
                `;
            });
            e.querySelector('ul').innerHTML += ul;
        });
    setFloat(e, 'table recharge', floatOfManageUser);
}

function setCommodity()
{
    let form = $('.float form');
    let req = {
        id : form.id.value,
        prop : form.prop.value,
        amount : form.amount.value,
        gold : form.gold.value,
    };
    submit(req, form, () =>
    {
        setFloat('操作成功，3s后自动关闭', null, floatOfManagerCommodity, 2000);
    });
    return false;
}

function floatOfEditCommodity( id, prop, amount, gold )
{
    id = id || 0;
    prop = prop || 0;
    amount = amount || 0;
    gold = gold || 0;
    let e = $make('div');
    e.innerHTML = `
        <h3>${id === 0 ? '添加' : '修改'}商品</h3>
        <form action="/api/admin/call/setCommodity" onsubmit="return setCommodity()">
            <ul>
                <li style="display: none;">
                    <p>ID</p>
                    <label for="id">
                        <input type="text" name="id" value="${id || 0}" required readonly />
                    </label>
                </li>
            
                <li>
                    <p>类型</p>
                    <label>
                        <select name="prop">
                            <option value="0" ${prop === 0 ? 'selected' : ''}>体力</option>
                            <option value="1" ${prop === 1 ? 'selected' : ''}>复活次数</option>
                        </select>
                    </label>
                </li>
                <li>
                    <p>数量</p>
                    <label for="amount">
                        <input type="number" name="amount" required value="${amount || ''}" />
                    </label>
                </li>
                <li>
                    <p>所需金币</p>
                    <label for="gold">
                        <input type="number" name="gold" required value="${gold || ''}" />
                    </label>
                </li>
            </ul>
            <label class="submit">
                <input type="submit">
                →
            </label>
        </form>
    `;
    setFloat(e, 'table account', floatOfManagerCommodity);
}

function chooseBanCommodity( id, state )
{
    let action = `/api/admin/call/${state ? 'ban' : 'unBan'}Commodity`;
    fetch(action, getFetchInit({ id : id }))
        .then(res => res.json())
        .then(res =>
        {
            let e;
            if( res.code === 200 )
                e = ('操作成功');
            else
                e = ('操作失败：' + res['err_msg']);
            setFloat(e, null, floatOfManagerCommodity, 2000);
        });
}

function floatOfManagerCommodity()
{
    let e = $make('div');
    e.innerHTML = `
        <div class="header">
            <h3>商品管理</h3>
            <p onclick="floatOfEditCommodity()">添加商品</p>
        </div>
        <ul>
            <li>
                <div class="com-state" style="width: 50px;">状态</div>
                <div class="com-type" style="width: 100px;">类型</div>
                <div class="com-amount" style="width: 50px;">数量</div>
                <div class="com-pay" style="width: 80px;">所需金币</div>
                <div class="opt">操作</div>
            </li>
        </ul>
    `;
    fetch('/api/admin/call/getCommodityList')
        .then(res => res.json())
        .then(res => res.data)
        .then(list =>
        {
            let ul = '';
            list.forEach(u =>
            {
                ul += `
                    <li ${u['state'] || ' style="color: gray;"'} >
                        <div class="com-state" style="width: 50px;">${u['state'] ? '已上线' : '下线'}</div>
                        <div class="com-type" style="width: 100px;">${u['prop'] === 0 ? '体力' : '复活次数'}</div>
                        <div class="com-amount" style="width: 50px;">${u['amount']}</div>
                        <div class="com-pay" style="width: 80px;">${u['pay']}</div>
                        <div class="opt" style="color: black;">
                            <div onclick="floatOfEditCommodity(${u['id']}, ${u['prop']}, ${u['amount']}, ${u['pay']})">修改<br>商品</div>
                            <div onclick="chooseBanCommodity(${u['id']}, ${u['state'] === 1})">${u['state'] ? '下线' : '上线'}<br>商品</div>
                        </div>
                    </li>
                `;
            });
            e.querySelector('ul').innerHTML += ul;
        });
    setFloat(e, 'table commodity-manage');
}

function setRecharge()
{
    let form = $('.float form');
    let req = {
        id : form.id.value,
        amount : form.amount.value,
        pay : form.pay.value,
    };
    submit(req, form, () =>
    {
        setFloat('操作成功，3s后自动关闭', null, floatOfManagerRecharge, 2000);
    });
    return false;
}

function floatOfEditRecharge( id, amount, pay )
{
    id = id || 0;
    amount = amount || 0;
    pay = pay || 0;
    let e = $make('div');
    e.innerHTML = `
        <h3>${id === 0 ? '添加' : '修改'}充值信息</h3>
        <form action="/api/admin/call/setRecharge" onsubmit="return setRecharge()">
            <ul>
                <li style="display: none;">
                    <p>ID</p>
                    <label for="id">
                        <input type="text" name="id" value="${id || 0}" required readonly />
                    </label>
                </li>
                <li>
                    <p>金币数量</p>
                    <label for="amount">
                        <input type="number" name="amount" required value="${amount || ''}" />
                    </label>
                </li>
                <li>
                    <p>定价</p>
                    <label for="pay">
                        <input type="number" step="0.01" name="pay" required value="${pay || ''}" />
                    </label>
                </li>
            </ul>
            <label class="submit">
                <input type="submit">
                →
            </label>
        </form>
    `;
    setFloat(e, 'table account', floatOfManagerRecharge);
}

function floatOfManagerRecharge()
{
    let e = $make('div');
    e.innerHTML = `
        <div class="header">
            <h3>充值管理</h3>
            <div class="menu">
                <p onclick="floatOfEditRecharge()">添加</p>
                <div class="filter"></div>
                <p onclick="floatOfRechargeRecord()">查看流水</p>
            </div>
        </div>
        <ul>
            <li>
                <div class="com-amount" style="width: 80px;">金币数量</div>
                <div class="com-pay" style="width: 50px;">定价</div>
                <div class="opt">操作</div>
            </li>
        </ul>
    `;
    fetch('/api/admin/call/getRechargeList')
        .then(res => res.json())
        .then(res => res.data)
        .then(list =>
        {
            let ul = '';
            list.forEach(u =>
            {
                ul += `
                    <li>
                        <div class="com-amount" style="width: 80px;">${u['amount']}</div>
                        <div class="com-pay" style="width: 50px;">${u['pay']}</div>
                        <div class="opt">
                            <div onclick="floatOfEditRecharge(${u['id']}, ${u['amount']}, ${u['pay']})">修改</div>
                        </div>
                    </li>
                `;
            });
            e.querySelector('ul').innerHTML += ul;
        });
    setFloat(e, 'table commodity-manage');
}

function setVerifyProblem()
{
    let form = $('.float form');
    let req = {
        id : form.id['value'],
        content : form.content.value
    };
    submit(req, form, () =>
    {
        setFloat('操作成功，3s后自动关闭', null, floatOfManageVerifyProblem, 2000);
    });
    return false;
}

function floatOfEditVerifyProblem(id, content)
{
    id = id || 0;
    content = content || '';
    let e = $make('div');
    e.innerHTML = `
        <h3>${id === 0 ? '添加' : '修改'}密保问题</h3>
        <form action="/api/admin/call/setVerifyProblem" onsubmit="return setVerifyProblem()">
            <ul>
                <li style="display: none;">
                    <p>ID</p>
                    <label for="id">
                        <input type="number" name="id" value="${id}" required readonly />
                    </label>
                </li>
                <li>
                    <p>内容</p>
                    <label for="content">
                        <input type="text" name="content" required value="${content || ''}" autofocus />
                    </label>
                </li>
            </ul>
            <label class="submit">
                <input type="submit">
                →
            </label>
        </form>
    `;
    setFloat(e, 'table account', floatOfManageVerifyProblem);
}

function floatOfManageVerifyProblem()
{
    let e = $make('div');
    e.innerHTML = `
        <div class="header">
            <h3>密保问题</h3>
            <p onclick="floatOfEditVerifyProblem()">添加</p>
        </div>
        <ul>
            <li>
                <div class="vfy-content">内容</div>
                <div class="opt">操作</div>
            </li>
        </ul>
    `;
    fetch('/api/admin/call/getVerifyProblem')
        .then(res => res.json())
        .then(res => res.data)
        .then(list =>
        {
            let ul = '';
            list.forEach(u =>
            {
                ul += `
                    <li>
                        <div class="vfy-content">${u['content']}</div>
                        <div class="opt">
                            <div onclick="floatOfEditVerifyProblem(${u['id']}, '${u['content']}')">修改</div>
                        </div>
                    </li>
                `;
            });
            e.querySelector('ul').innerHTML += ul;
        });
    setFloat(e, 'table verify-problem-manage');
}

{
    fetch('/api/admin/call/isLogin')
        .then(res => res.json())
        .then(res =>
        {
            if( res.data )
                loadAdminResource();
            else
                $('.admin .login').classList.remove('hide');
        });
}
