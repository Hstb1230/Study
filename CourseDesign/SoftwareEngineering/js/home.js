let home = $('.main .home');
let viewOfSetting = '';
let viewOfChangePassword = '';
let viewOfChangeVerifyProblem = '';
let listOfVerifyProblem = [];
let verifyProblemID = 1;

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
                let prop = home.querySelector('.prop');
                prop.querySelector('.gold p').innerHTML = warehouseInfo.data.data['gold'];
                prop.querySelector('.power p').innerHTML = warehouseInfo.data.data['play_count'];
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