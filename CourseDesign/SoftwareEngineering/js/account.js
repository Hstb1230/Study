let account = {
    isLogin : false,
};

// 获取登录状态
fetch('/api/')
    .then(data => data.json())
    .then(data =>
    {
        account.isLogin = (data.code === 200 && toString(data.data) !== '{}');
    });

if( account.isLogin )
{
    $('.tab .default').style.display = 'none';
    $('.tab .home').style.display = 'black';
}

function showPassword( e )
{
    let label = $(`.float label[for=${e}]`);
    let pwd = label.querySelector('input');
    let icon = label.querySelector('i');
    if( pwd.type === 'password' )
    {
        pwd.type = 'text';
        icon.setAttribute('class', 'i-see');
    }
    else
    {
        pwd.type = 'password';
        icon.setAttribute('class', 'i-hide');
    }
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
        u : escape(form.u.value),
        p : escape(form.p.value),
        vid : escape(form.vid.value),
        vans : escape(form.vans.value),
    };
    console.log(objectToKeyValue(req));
    fetch('/api/user/register.php', {
        method : 'post',
        body : objectToKeyValue(req),
    })
        .then(res => res.json())
        .then(data =>
        {
            console.log(data);
        });
    // console.log(form);
    return false;
}

function userExist( e )
{
    fetch(`/api/user/userExist.php?u=${escape(e.value)}`)
        .then(res => res.json())
        .then(data =>
        {
            if( data.data )
                reportInput(e, '用户已存在');
        });
}

function reportInput(e, msg)
{
    e.value = '';
    e.validationMessage = e.placeholder = msg;
    e.reportValidity();
    e.focus();
    e.classList.add('shake');
    e.classList.add('ph-hide');
    setTimeout(function ()
    {
        e.placeholder = '';
        e.validationMessage = '请填写该字段';
        e.classList.remove('shake');
        e.classList.remove('ph-hide');
    }, 1800);
}

function login( username, password )
{

}

let pact = $('.main .default .pact');
let pactLink = pact.querySelector('a');
let pactSelect = pact.querySelector('input');
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

let acc = $('.main .default .account');
let accReg = acc.querySelector('.register');
let accLog = acc.querySelector('.login');
accReg.addEventListener('click',
    function ()
    {
        if( !pactSelect.checked )
        {
            console.log('accReg');
            floatOfPactRequest();
            return;
        }
        let div = $make('div');
        div.innerHTML = `
            <div class="register">
                <h3>注册</h3>
                <form action="/api/user/register.php" onsubmit="return register()">
                    <ul>
                        <li>
                            <p>用户名</p>
                            <label for="u">
                                <input type="text" minlength="3" name="u" required />
                            </label>
                        </li>
                        <li>
                            <p>密码</p>
                            <label for="p">
                                <input type="password" minlength="3" name="p" required />
                                <i class="i-hide" onclick="showPassword('p')"> </i>
                            </label>
                        </li>
                        <li>
                            <p>再次输入密码</p>
                            <label for="sp">
                                <input type="password" minlength="3" name="sp" required />
                                <i class="i-hide" onclick="showPassword('sp')"> </i>
                            </label>
                        </li>
                        <li>
                            <p>密保问题</p>
                            <label>
                                <select name="vid">
                                    <option value="0">获取中 · · ·</option>
                                </select>
                            </label>
                        </li>
                        <li>
                            <p>答案</p>
                            <label>
                                <input type="text" name="vans" required />
                            </label>
                        </li>
                    </ul>
                    <label class="submit">
                        <input type="submit">
                        →
                    </label>
                </form>
            </div>
        `;
        axios.get('/api/user/getVerifyProblemList.php')
             .then(res => res.data)
             .then(res => res.data)
             .then(data =>
             {
                 // console.log(data)
                 let select = div.querySelector('form select');
                 while( select.options.length > 0 )
                     select.options.remove(0);
                 data.forEach(i =>
                 {
                     select.options.add(new Option(
                         i.content,
                         i.id,
                     ));
                 });
             });
        setFloat(div, 'register');
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
                   if( this.value !== div.querySelector('form').p.value )
                       reportInput(this, '密码不一致');
               },
           );
    },
);
accLog.addEventListener('click',
    function ()
    {
        if( !pactSelect.checked )
        {
            console.log('accLog');
            floatOfPactRequest();
            return;
        }
        console.log('log');
    },
);

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
    fetch('/api/user/getPactContent.php')
        .then(data => data.json())
        .then(data =>
        {
            let content = div.querySelector('p');
            // 替换协议中的换行为HTML版换行
            content.innerHTML = data.data.replace(/\n/g, '<br>');
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
        });
    return false;
}

// 从本地读取同意状态，避免每次打开网页都要勾选
if( localStorage.getItem('agree-pact') === 'true' )
{
    pactSelect.checked = true;
    acc.classList.remove('gray');
}
