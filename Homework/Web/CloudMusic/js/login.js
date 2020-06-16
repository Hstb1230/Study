const ref = unescape(getParam('ref') || '.');

function jump() 
{
    window.location.href= ref;
}

fetch(`${domain}/login/status`, {
    method: 'get',
    mode: 'cors'
})
.then( data => data.json() )
.then( data => {
    console.log(data);
    if(data.code === 200)
        jump();
} )

$('.login').onsubmit = () => {
    let phone = escape($('#login-phone').value);
    let pwd = escape($('#login-pwd').value);
    // console.log(phone, pwd);
    fetch(`${domain}/login/cellphone?phone=${phone}&password=${pwd}`, {
        method: 'get',
        mode: 'cors',
        credentials: 'include'
    })
    .then( data => data.json() )
    .then( data => {
        console.log(data);
        if(data.code === 200)
        {
            localStorage.setItem('userID', data.profile.userId);
            jump();
        }
        else
            alert(`登录失败：${data.message}`);
    } )

    return false;
}