let account = {
    isLogin : false,
};

// 登录页面视图
let viewOfAccLog = '';
// 注册页面视图
let viewOfAccReg = '';
// 重置密码页面视图
let viewOfResetPassword = '';
// 协议内容
let contentOfPact = '';
// 验证问题
let verifyProblem = [];

// 获取登录状态
let waitAccount = fetch('/api/user/call/isLogin')
    .then(data => data.json())
    .then(data =>
        {
            account.isLogin = (data.code === 200);
            return account.isLogin;
        },
    );

waitAccount.then(state =>
{
    if( state )
    {
        $('.main .home').classList.remove('hide');
        loadHomeResource();
    }
    else
    {
        $('.main .default').classList.remove('hide');
        initDefaultResource();

        pactSelect.addEventListener('click',
            function ()
            {
                localStorage.setItem('agree-pact', this.checked);
                if( this.checked )
                    acc.classList.remove('gray');
                else
                    acc.classList.add('gray');
                console.log('pact select', this.checked);
            },
        );

        // 从本地读取同意状态，避免每次打开网页都要勾选
        if( localStorage.getItem('agree-pact') === 'true' )
        {
            pactSelect.checked = true;
            acc.classList.remove('gray');
        }
    }
});

function initDefaultResource()
{
    let getLoginView = () => axios.get('/view/login.html');
    let getPactContent = () => axios.get('/api/user/call/getPactContent');
    let getRegisterView = () => axios.get('/view/register.html');
    let getResetPasswordView = () => axios.get('/view/resetPassword.html');
    let getVerifyProblemList = () => axios.get('/api/user/call/getVerifyProblemList');
    axios.all(
        [
            getPactContent(),
            getLoginView(),
            getRegisterView(),
            getResetPasswordView(),
            getVerifyProblemList(),
        ],
    )
         .then(
             axios.spread(
                 (
                     pactContent,
                     loginView,
                     registerView,
                     resetPasswordView,
                     verifyProblemList,
                 ) =>
                 {
                     // console.log(loginView, registerView);
                     contentOfPact = pactContent.data.data.replace(/\n/g, '<br>');
                     viewOfAccLog = loginView.data;
                     viewOfAccReg = registerView.data;
                     viewOfResetPassword = resetPasswordView.data;
                     verifyProblem = verifyProblemList.data.data;
                 }),
         );
}

function register()
{
    let form = $('.float .register form');
    if( form.p.value !== form.sp.value )
    {
        form.sp.value = '';
        form.sp.focus();
        form.sp.placeholder = '密码不一致';
        return false;
    }
    let req = {
        u : (form.u.value),
        p : (form.p.value),
        vid : (form.vid.value),
        vans : (form.vans.value),
    };
    submit(
        req, form,
        () => {
            setFloat('注册成功，<a onclick="return floatOfLogin()">现在登录</a>');
        },
        data => {
            setFloat(
                `
                    <h3>注册失败</h3>
                    <p>${data['err_msg']}，<a onclick="return floatOfRegister()">重新注册</a></p>
                `,
                'error'
            );
        }
    )
    return false;
}

function userExist( e )
{
    fetch(`/api/user/call/userExist`, getFetchInit({ u : e.value }))
        .then(res => res.json())
        .then(data =>
        {
            if( data.data )
                reportInput(e, '用户已存在');
        });
}

function login()
{
    let form = $('.float .login form');
    let req = {
        u : (form.u.value),
        p : (form.p.value),
    };
    submit(
        req, form,
        () => {
            setFloat(
                '登录成功，3s后自动关闭',
                null,
                () => {
                    $('.main .default').classList.add('hide');
                    $('.main .home').classList.remove('hide');
                    closeFloat();
                    loadHomeResource();
                },
                3000
            );
        }
    );
    return false;
}

function resetPassword()
{
    let form = $('.float .reset-password form');
    let req = {
        u : (form.u.value),
        vid : (form.vid.value),
        vans : (form.vans.value),
        np : (form.np.value),
    };
    submit(
        req, form,
        () => { setFloat('重置成功，<a onclick="return floatOfLogin()">现在登录</a>'); }
    );
    return false;
}

let pact = $('.main .default .pact');
let pactSelect = pact.querySelector('input');

let acc = $('.main .default .account');

function floatOfRegister()
{
    if( !pactSelect.checked )
    {
        floatOfPactRequest();
        return;
    }
    if( viewOfAccReg === '' )
    {
        setFloat('获取数据失败，请<a onclick="location.reload()">刷新网页</a>');
        return;
    }
    let div = $make('div');
    div.innerHTML = viewOfAccReg;

    let select = div.querySelector('form select');
    while( select.options.length > 0 )
        select.options.remove(0);
    verifyProblem.forEach(i =>
    {
        select.options.add(new Option(
            i.content,
            i.id,
        ));
    });

    setFloat(div, 'account register');
    div.querySelector('label[for=u] input')
       .addEventListener('blur',
           function ()
           {
               if( this.value !== '' )
                   userExist(this);
           },
       );
    div.querySelector('label[for=sp] input')
       .addEventListener('blur',
           function ()
           {
               if( this.value !== '' && this.value !== div.querySelector('form').p.value )
               {
                   reportInput(this, '密码不一致');
                   reportInput(div.querySelector('form').p, '');
               }
           },
       );
}

function floatOfLogin()
{
    if( !pactSelect.checked )
    {
        floatOfPactRequest();
        return;
    }
    if( viewOfAccLog === '' )
    {
        setFloat('获取数据失败，请<a onclick="location.reload()">刷新网页</a>');
        return;
    }
    let div = $make('div');
    div.innerHTML = viewOfAccLog;
    setFloat(div, 'account login');
}

function floatOfResetPassword()
{
    if( viewOfResetPassword === '' )
    {
        setFloat('获取数据失败，请<a onclick="location.reload()">刷新网页</a>');
        return;
    }
    let div = $make('div');
    div.innerHTML = viewOfResetPassword;
    setFloat(div, 'account reset-password', floatOfLogin);

    let select = div.querySelector('form select');
    while( select.options.length > 0 )
        select.options.remove(0);
    verifyProblem.forEach(i =>
    {
        select.options.add(new Option(
            i.content,
            i.id,
        ));
    });

    return false;
}

// 显示阅读协议请求
function floatOfPactRequest()
{
    let div = $make('div');
    div.innerHTML = `
        <p>
            请先阅读并同意
            <a onclick="floatOfPactContent()">《用户与隐私协议》</a>
        </p>
    `;
    setFloat(div, 'pact-request');
}

// 显示协议内容
function floatOfPactContent()
{
    let div = $make('div');
    div.innerHTML = `
        <h3>用户与隐私协议</h3>
        <p>获取中 · · ·</p>
        <div class="btn-agree" style="display:none;">我已理解并同意 √</div>
    `;
    setFloat(div, 'pact-content');
    let content = div.querySelector('p');
    if( contentOfPact.length > 0 )
        content.innerHTML = contentOfPact;
    else
        content.innerHTML = '获取失败';
    let agree = div.querySelector('.btn-agree');
    if( !pactSelect.checked )
        agree.style.display = '';
    agree.addEventListener('click',
        function ()
        {
            // 将同意状态保存至本地
            localStorage.setItem('agree-pact', true);
            pactSelect.checked = true;
            // 需要手动触发动画
            setTimeout(() =>
            {
                acc.classList.remove('gray');
            }, 500);
            closeFloat();
        },
    );
    return false;
}
