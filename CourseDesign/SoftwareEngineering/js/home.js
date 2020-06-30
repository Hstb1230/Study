let home = $('.main .home');
let warehouse;
let viewOfSetting = '';
let viewOfChangePassword = '';
let viewOfChangeVerifyProblem = '';
let listOfVerifyProblem = [];
let verifyProblemID = 1;
let listOfRecharge;

function flushWarehouse()
{
    axios.get('/api/user/call/getWarehouseInfo')
        .then( res => res.data )
        .then( res => {
            warehouse = res.data;
            let prop = home.querySelector('.prop');
            prop.querySelector('.gold p').innerHTML = warehouse['gold'];
            prop.querySelector('.power p').innerHTML = warehouse['play_count'];
        })
}

function loadHomeResource()
{
    let getWarehouseInfo = () => axios.get('/api/user/call/getWarehouseInfo');
    let getSettingView = () => axios.get('/view/setting.html');
    axios.all(
        [
            getWarehouseInfo(),
            getSettingView()
        ]
    ).then(
        axios.spread(
            (
                warehouseInfo,
                settingView
            ) =>
            {
                warehouse = warehouseInfo.data.data;
                let prop = home.querySelector('.prop');
                prop.querySelector('.gold p').innerHTML = warehouse['gold'];
                prop.querySelector('.power p').innerHTML = warehouse['play_count'];
                viewOfSetting = settingView.data;
            }
        )
    )
}

function loadSettingResource()
{
    let getChangePasswordView = () => axios.get('/view/changePassword.html');
    let getChangeVerifyProblemView = () => axios.get('/view/changeVerifyProblem.html');
    let getVerifyProblemList = () => axios.get('/api/user/call/getVerifyProblemList');
    let getVerifyProblemID = () => axios.get('/api/user/call/getVerifyProblemID');
    axios.all(
        [
            getChangePasswordView(),
            getChangeVerifyProblemView(),
            getVerifyProblemList(),
            getVerifyProblemID()
        ]
    ).then(
        axios.spread(
            (
                changePasswordView,
                changeVerifyProblemView,
                verifyProblemList,
                verifyProblemIDData
            ) =>
            {
                viewOfChangePassword = changePasswordView.data;
                viewOfChangeVerifyProblem = changeVerifyProblemView.data;
                listOfVerifyProblem = verifyProblemList.data.data;
                verifyProblemID = verifyProblemIDData.data.data;
            }
        )
    )
}

function floatOfSetting()
{
    loadSettingResource();
    let div = $make('div');
    div.innerHTML = viewOfSetting;
    div.querySelector('.s-music input[name=m-bg]').checked = (localStorage.getItem('m-bg') === 'true');
    div.querySelector('.s-music input[name=m-game]').checked = (localStorage.getItem('m-game') === 'true');
    div.querySelector('.s-music input[name=m-bg]').addEventListener('click',
        function ()
        {
            localStorage.setItem('m-bg', this.checked);
            if(this.checked)
                audioOfBG.play();
            else
                audioOfBG.pause();
        }
    )
    div.querySelector('.s-music input[name=m-game]').addEventListener('click',
        function ()
        {
            localStorage.setItem('m-game', this.checked);
        }
    )
    setFloat(div, 'setting');
    return false;
}

function logout()
{
    fetch('/api/user/call/logout')
        .then(() => {
            initDefaultResource();
            $('.main .home').classList.add('hide');
            $('.main .default').classList.remove('hide');
            setFloat('已退出登录，3s后自动关闭', null, closeFloat, 3000);
        })
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
        reportInput(form.np, '');
        return false;
    }

    if( form.p.value === form.np.value )
    {
        reportInput(form.sp, '');
        reportInput(form.np, '新旧密码一样');
        return false;
    }

    submit(req, form, () => { setFloat('修改成功，3s后自动关闭', null, floatOfSetting, 3000); })

    return false;
}

function floatOfChangePassword()
{
    let e = $make('div');
    e.innerHTML = viewOfChangePassword;
    setFloat(e, 'account change-password', floatOfSetting);
    return false;
}

function changeVerifyProblem()
{
    let form = $('.float .account form');
    // noinspection SpellCheckingInspection
    let req = {
        vans : (form.vans.value),
        nvp : (form.nvp.value),
        nvans : (form.nvans.value),
    };
    submit(req, form, () => { setFloat('修改成功，3s后自动关闭', null, floatOfSetting, 3000); })
    return false;
}

function floatOfChangeVerifyProblem()
{
    let div = $make('div');
    div.innerHTML = viewOfChangeVerifyProblem;
    let form = div.querySelector('form');
    form.vp.value = listOfVerifyProblem[verifyProblemID - 1].content;
    let select = form.querySelector('select');
    while( select.options.length > 0 )
        select.options.remove(0);
    listOfVerifyProblem.forEach(i =>
    {
        select.options.add(new Option(
            i.content,
            i.id,
        ));
    });
    setFloat(div, 'account change-verify-problem', floatOfSetting);
    return false;
}

function floatOfRank()
{
    let e = $make('div');
    e.innerHTML = `
        <h3>排行榜</h3>
        <ul>
            <li>
                <div class="more">获取中</div>
            </li>
        </ul>
    `;
    setFloat(e, 'rank');
    fetch('/api/user/call/rank')
        .then( res => res.json() )
        .then( res => res.data )
        .then( arr => {
            let ul = '';
            arr.forEach( (a, i) => {
                let seq = a['seq'];
                if(seq === 1)
                    seq = '<div class="i-first-win"></div>';
                else if(seq === 2)
                    seq = '<div class="i-second-win"></div>';
                else if(seq === 3)
                    seq = '<div class="i-third-win"></div>';
                if(a.seq !== i + 1)
                    ul += `
                        <li>
                            <div class="more">······</div>
                        </li>
                    `;
                else
                    ul += `
                        <li>
                            <div class="seq">${seq}</div>
                            <div class="name">${a.name}</div>
                            <div class="score">${a.score}</div>
                        </li>
                    `;
            })
            e.querySelector('ul').innerHTML = ul;
        })
    return false;
}

function buyProp(id)
{
    submit(
        { cid : id },
        '/api/user/call/buyCommodity',
        () => {
            flushWarehouse();
            setFloat('购买成功', null, floatOfStore, 3000);
        },
        (res) => {
            setFloat(
                `
                    <h3>购买失败</h3>
                    <p>${res['err_msg']}</p>
                `,
                'message',
                floatOfStore, 3000
            );
        }
    )
}

function floatOfStore()
{
    let e = $make('div');
    e.innerHTML = `
        <div class="header">
            <h3>商店</h3>
            <h5 onclick="floatOfConsumeRecord()"><div class="i-bill"></div>消费记录</h5>
        </div>
        <ul>
            <li>获取中 · · ·</li>
        </ul>
    `;
    setFloat(e, 'store');
    let ul = '';
    fetch('/api/user/call/getCommodityList')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            list.forEach( i => {
                ul += `
                    <li onclick="buyProp(${ i['id'] })">
                        <div class="info">
                            <div class="${ i['prop'] === 0 ? 'i-power' : 'i-heart' }"></div>
                            <div style="font-size: 12px; margin-right: 3px;">x</div>
                            <div class="count">${ i['amount'] }</div>
                        </div>
                        <div class="detail">
                            <div class="i-stock">
                                <div class="count">${ i['prop'] === 0 ? warehouse['play_count'] : warehouse['resurrection'] }</div>
                            </div>
                            <div class="i-gold">
                                <div class="need">${ i['pay'] }</div>    
                            </div>
                        </div>
                    </li>
                `;
            } )
            e.querySelector('ul').innerHTML = ul;
        } )
    return false;
}

function floatOfConsumeRecord()
{
    let e = $make('div');
    e.innerHTML = `
        <h3>消费记录</h3>
        <ul>
        </ul>
    `;
    setFloat(e, 'record', floatOfStore);
    let ul = '';
    fetch('/api/user/call/getConsumeRecord')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            list.forEach( i => {
                ul += `
                    <li>
                        <div class="time" style="width: 120px; text-align: center;">${ timestampToDate(i.time * 1000) }</div>
                        花费
                        <div class="i-gold">
                            <div class="need">${ i['gold_amount'] }</div>
                        </div>
                        购买
                        <div class="${ i['prop_type'] === 0 ? 'i-power' : 'i-heart' }">
                            <div class="count">${ i['prop_amount'] }</div>
                        </div>
                    </li>
                `;
            } )
            e.querySelector('ul').innerHTML = ul;
        } )
    return false;
}

function floatOfRechargeRecord()
{
    let e = $make('div');
    e.innerHTML = `
        <h3>充值记录</h3>
        <ul>
        </ul>
    `;
    setFloat(e, 'record', floatOfRecharge);
    let ul = '';
    fetch('/api/user/call/getRechargeRecord')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            list.forEach( i => {
                ul += `
                    <li>
                        <div class="time" style="width: 120px; text-align: center">${ timestampToDate(i.time * 1000) }</div>
                        通过
                        <div class="i-${ i['pay_way'] === 1 ? 'alipay' : 'wechat' }"></div>
                        充值
                        <div class="i-CNY">
                            <div class="need">${ i['final_pay'] }</div>
                        </div>
                        获得
                        <div class="i-gold">
                            <div class="count">${ i['get_gold'] }</div>
                        </div>
                    </li>
                `;
            } )
            e.querySelector('ul').innerHTML = ul;
        } )
    return false;
}

function recharge(way)
{
    let radio = $('input[name=pay]:checked');
    if(radio === null)
    {
        reportElement($('.float .recharge ul'));
        return false;
    }
    let req = {
        rid: listOfRecharge[radio.value]['id'],
        fp: listOfRecharge[radio.value]['pay'],
        pw : way
    };
    submit(
        req, '/api/user/call/recharge',
        () =>
        {
            flushWarehouse();
            setFloat('充值成功', null, floatOfRecharge, 3000);
        },
        res => {
            setFloat(
                `
                    <h3>充值失败</h3>
                    <p>${ res['err_msg'] }</p>
                `,
                'message', floatOfRecharge, 3000
            );
        }
    )
}

function floatOfRecharge()
{
    let e = $make('div');
    e.innerHTML = `
        <div class="header">
            <h3>充值</h3>
            <h5 onclick="floatOfRechargeRecord()"><div class="i-bill"></div>充值记录</h5>
        </div>
        <ul>
            <li>获取中 · · ·</li>
        </ul>
        <div class="pay">
            <h3>付款方式</h3>
        </div>
        <ul>
            <li onclick="recharge(1)">
                <div class="i-alipay"></div>
            </li>
            <li onclick="recharge(2)">
                <div class="i-wechat"></div>
            </li>
        </ul>
    `;
    setFloat(e, 'recharge');
    let ul = '';
    fetch('/api/user/call/getRechargeList')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            listOfRecharge = list;
            list.forEach( (i, seq) => {
                ul += `
                    <label>
                        <input type="radio" name="pay" style="display: none;" value="${ seq }">
                        <li>
                            <div class="info">
                                <div class="i-gold">
                                    <div class="count">${ i['amount'] }</div>    
                                </div>
                            </div>
                            <div class="detail">
                                <div class="i-CNY"></div>
                                <div class="need">${ i['pay'] }</div>
                            </div>
                        </li>
                    </label>
                `;
            } )
            e.querySelector('ul').innerHTML = ul;
        } )
    return false;
}
