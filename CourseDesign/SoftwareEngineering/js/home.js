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
    axios.get('/api/user/getWarehouseInfo.php')
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
    let getWarehouseInfo = () => axios.get('/api/user/getWarehouseInfo.php');
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
    let getVerifyProblemList = () => axios.get('/api/user/getVerifyProblemList.php');
    let getVerifyProblemID = () => axios.get('/api/user/getVerifyProblemID.php');
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
    fetch('/api/user/logout.php')
        .then(() => {
            initDefaultResource();
            $('.main .home').classList.add('hide');
            $('.main .default').classList.remove('hide');
            setFloat('已退出登录，3s后自动关闭');
            setTimeout(() => {
                closeFloat();
            }, 3000);
        })
}

function changePassword()
{
    let form = $('.float .account form');
    let req = {
        p : escape(form.p.value),
        np : escape(form.np.value),
    };

    if( form.sp.value !== '' && form.sp.value !== form.np.value )
    {
        reportInput(form.sp, '密码不一致');
        reportInput(form.np, '');
        return false;
    }

    submit(req, form)

    return false;
}

function floatOfChangePassword()
{
    let e = $make('div');
    e.innerHTML = viewOfChangePassword;
    setFloat(e, 'account change-password');
    return false;
}

function submit(req, form)
{
    // 禁止二次点击
    form.style.opacity = 0.5;
    form.style.userSelect = 'none';

    sleep(800).then(() =>
    {
        fetch(form.action, {
            method : 'post',
            headers : { 'Content-Type' : 'application/x-www-form-urlencoded' },
            body : objectToKeyValue(req),
        })
            .then(res => res.json())
            .then(data =>
                {
                    form.style.opacity = 1;
                    form.style.userSelect = '';
                    // console.log(data);
                    if( data.code === 200 )
                    {
                        setFloat('修改成功，3s后自动关闭');
                        setTimeout(() => {
                            floatOfSetting();
                        }, 3000);
                    }
                    else
                    {
                        reportInput(form[data['data']], data['err_msg']);
                    }
                },
            );
    });
}

function changeVerifyProblem()
{
    let form = $('.float .account form');
    let req = {
        vans : escape(form.vans.value),
        nvp : escape(form.nvp.value),
        nvans : escape(form.nvans.value),
    };
    submit(req, form);
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
    setFloat(div, 'account change-verify-problem');
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
    fetch('/api/user/rank.php')
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
    fetch(
        '/api/user/buyCommodity.php',
        {
            method : 'post',
            headers : { 'Content-Type' : 'application/x-www-form-urlencoded' },
            body : objectToKeyValue({ cid : id }),
        }
    ).then( res => res.json() )
     .then( res => {
         let e;
         if( res.code === 200 )
         {
             e = '购买成功，<a onclick="floatOfStore()">继续购买</a>';
             flushWarehouse();
             setFloat(e);
         }
         else
         {
             e = $make('div');
             e.innerHTML = `
                <h3>购买失败</h3>
                <p>${res['err_msg']}，<a onclick="floatOfStore()">继续购买</a></p>
             `;
             setFloat(e, 'message');
         }
     })
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
    fetch('/api/user/getCommodityList.php')
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
                                <div class="count">${ i['prop'] === 0 ? warehouse['play_count'] : warehouse['gold'] }</div>
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
    setFloat(e, 'record');
    let ul = '';
    fetch('/api/user/getConsumeRecord.php')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            list.forEach( i => {
                ul += `
                    <li>
                        <div class="time">${ timestampToDate(i.time * 1000) }</div>
                        花费
                        <div class="i-gold">
                            <div class="need">${ i['pay'] }</div>
                        </div>
                        购买
                        <div class="${ i['prop'] === 0 ? 'i-power' : 'i-heart' }">
                            <div class="count">${ i['amount'] }</div>
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
    setFloat(e, 'record');
    let ul = '';
    fetch('/api/user/getRechargeRecord.php')
        .then( res => res.json() )
        .then( res => res.data )
        .then( list => {
            list.forEach( i => {
                ul += `
                    <li>
                        <div class="time">${ timestampToDate(i.time * 1000) }</div>
                        通过
                        <div class="i-${ i['pay_way'] === 1 ? 'alipay' : 'wechat' }"></div>
                        充值
                        <div class="i-CNY">
                            <div class="need">${ i['final_pay'] }</div>
                        </div>
                        获得
                        <div class="i-gold">
                            <div class="count">${ i['gold'] }</div>
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
    fetch(
        '/api/user/recharge.php',
        {
            method: 'post',
            headers : { 'Content-Type' : 'application/x-www-form-urlencoded' },
            body : objectToKeyValue(req),
        }
    )   .then( res => res.json() )
        .then( res => {
            if(res.code === 200)
            {
                flushWarehouse();
                setFloat('充值成功，<a onclick="floatOfRecharge()">继续充值</a>');
            }
            else
            {
                let e = $make('div');
                e.innerHTML = `
                    <h3>充值失败</h3>
                    <p>
                        ${ res['err_msg'] }
                        ，<a onclick="floatOfRecharge()">继续充值</a>
                    </p>
                `;
                setFloat(e, 'message');
            }
        })
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
    fetch('/api/user/getRechargeList.php')
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
