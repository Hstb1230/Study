let account = {
    isLogin : false
};

// 获取登录状态
fetch('/api/')
.then( data => data.json())
.then( data => {
    account.isLogin = (data.code === 200 && toString(data.data) !== '{}');
} )

if(account.isLogin)
{
    $('.tab .default').style.display = 'none';
    $('.tab .home').style.display = 'black';
}

function register(username, password, verify_problem_id, verify_answer)
{

}

function login(username, password)
{

}

let pact = $('.main .default .pact');
let pactLink = pact.querySelector('a');
let pactSelect = pact.querySelector('input');
pactSelect.addEventListener('click',
    function ()
    {
        localStorage.setItem('agree-pact', this.checked);
        if(this.checked)
            acc.classList.remove('gray');
        else
            acc.classList.add('gray');
        console.log('pact select', this.checked);
    }
);

let acc = $('.main .default .account');
let accReg = acc.querySelector('.register');
let accLog = acc.querySelector('.login');
accReg.addEventListener('click',
    function ()
    {
        if(!pactSelect.checked)
        {
            console.log('accReg');
            floatOfPactRequest();
            return;
        }
        console.log('reg');
    }
)
accLog.addEventListener('click',
    function ()
    {
        if(!pactSelect.checked)
        {
            console.log('accLog');
            floatOfPactRequest();
            return;
        }
        console.log('log');
    }
)

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
        .then( data => data.json() )
        .then( data => {
            let content = div.querySelector('p');
            content.innerHTML = data.data.replace(/\n/g, '<br>');
            let agree = div.querySelector('.btn-agree');
            if(!pactSelect.checked)
                agree.style.display = '';
            agree.addEventListener('click',
                function ()
                {
                    localStorage.setItem('agree-pact', true);
                    pactSelect.checked = true;
                    setTimeout(() => {
                        acc.classList.remove('gray');
                    }, 500);
                    closeFloat();
                }
            );
        })
    return false;
}

if(localStorage.getItem('agree-pact') === 'true')
{
    pactSelect.checked = true;
    acc.classList.remove('gray');
}
