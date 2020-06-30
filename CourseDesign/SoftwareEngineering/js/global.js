$ = e => document.querySelector(e);

$include = (e) => {
    let newScript = document.createElement('script');
    newScript.setAttribute('type','text/javascript');
    newScript.setAttribute('src',e);
    document.body.appendChild(newScript);
}

$make = (e) => document.createElement(e);

// https://zeit.co/blog/async-and-await
function sleep (time)
{
    return new Promise((resolve) => setTimeout(resolve, time));
}

function objectToKeyValue(obj)
{
    if(obj === null)
        return '';
    else if(typeof obj === 'string')
        return obj;
    let kv = '';
    Object.keys(obj).forEach( k => {
        kv += `&${k}=${encodeURI(obj[k])}`;
    });
    return kv.substring(1);
}

Date.prototype.getFullMonth = function()
{
    if(this.getMonth() + 1 < 10)
        return `0${this.getMonth() + 1}`;
    return this.getMonth() + 1;
}

Date.prototype.getFullDate = function()
{
    if(this.getDate() < 10)
        return `0${this.getDate()}`;
    return this.getDate();
}

Date.prototype.getFullHours = function()
{
    if(this.getHours() < 10)
        return `0${this.getHours()}`;
    return this.getHours();
}

Date.prototype.getFullMinutes = function()
{
    if(this.getMinutes() < 10)
        return `0${this.getMinutes()}`;
    return this.getMinutes();
}

function timestampToDateOnly(timeStamp)
{
    let fmt = '';

    let now = new Date();
    now.setHours(0);
    now.setMinutes(0);
    now.setSeconds(0);
    now.setMilliseconds(0);

    let t = new Date(timeStamp);
    if(now.getTime() / 1000 < Math.floor(timeStamp / 1000))
        fmt = '今天';
    else if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60)
        fmt = '昨天';
    else if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60 * 2)
        fmt = '前天';
    else if(now.getFullYear() === t.getFullYear())
        fmt = `${t.getFullMonth()}月${t.getFullDate()}日`;
    else if(now.getTime() / 1000 > Math.floor(timeStamp / 1000))
        fmt = `${t.getFullYear()}年${t.getFullMonth()}月${t.getFullDate()}日`;
    return fmt;
}

function timestampToDate(timeStamp)
{
    if(timeStamp < 1e11)
        timeStamp *= 1000;
    let fmt = timestampToDateOnly(timeStamp);

    let now = new Date();
    now.setHours(0);
    now.setMinutes(0);
    now.setSeconds(0);
    now.setMilliseconds(0);

    let t = new Date(timeStamp);
    fmt += `${t.getFullHours()}:${t.getFullMinutes()}`;
    return fmt;
}

function reportElement( e )
{
    e.classList.add('shake');
    setTimeout(function ()
    {
        e.classList.remove('shake');
    }, 1800);
}

function reportInput( e, msg )
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

function getFetchInit(req)
{
    return {
        method : 'post',
        body : objectToKeyValue( req),
        headers : { 'Content-Type' : 'application/x-www-form-urlencoded' },
    };
}

function submit( req, form, callbackOfSuccess, callbackOfFail )
{
    if( typeof form !== 'string' )
    {
        // 禁止二次点击
        form.style.opacity = 0.5;
        form.style.pointerEvents = 'none';
    }

    sleep(800).then(() =>
    {
        let action;
        if( typeof form === 'string' )
            action = form;
        else
            action = form.action;
        fetch(action, {
            method : 'post',
            headers : { 'Content-Type' : 'application/x-www-form-urlencoded' },
            body : objectToKeyValue(req),
        })
            .then(res => res.json())
            .then(data =>
                {
                    if( typeof form !== 'string' )
                    {
                        form.style.opacity = 1;
                        form.style.pointerEvents = '';
                    }
                    // console.log(data);
                    // 状态码为200时表示调用成功
                    if( data.code === 200 )
                    {
                        // 进行成功回调
                        if( typeof callbackOfSuccess !== 'undefined' && callbackOfSuccess !== null )
                            callbackOfSuccess();
                    }
                    else if( typeof callbackOfFail !== 'undefined' && callbackOfFail !== null )
                    {
                        callbackOfFail(data);
                    }
                    else if( typeof form !== 'string' && typeof data['data'] === 'string' && data['data'] !== '')
                    {
                        reportInput(form[data['data']], data['err_msg']);
                    }
                    else
                    {
                        setFloat(data['err_msg']);
                    }
                },
            );
    });
}

