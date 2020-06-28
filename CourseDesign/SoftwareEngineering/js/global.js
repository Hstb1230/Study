$ = e => document.querySelector(e);

$include = (e) => {
    let newScript = document.createElement('script');
    newScript.setAttribute('type','text/javascript');
    newScript.setAttribute('src',e);
    document.body.appendChild(newScript);
}

$make = (e) => document.createElement(e);

// https://zeit.co/blog/async-and-await
function sleep (time) {
    return new Promise((resolve) => setTimeout(resolve, time));
}

function objectToKeyValue(obj)
{
    let kv = '';
    Object.keys(obj).forEach( k => {
        kv += `&${k}=${escape(obj[k])}`;
    });
    return kv.substring(1);
}

Date.prototype.getFullMonth = function() {
    if(this.getMonth() + 1 < 10)
        return `0${this.getMonth() + 1}`;
    return this.getMonth() + 1;
}

Date.prototype.getFullDate = function() {
    if(this.getDate() < 10)
        return `0${this.getDate()}`;
    return this.getDate();
}

Date.prototype.getFullHours = function() {
    if(this.getHours() < 10)
        return `0${this.getHours()}`;
    return this.getHours();
}

Date.prototype.getFullMinutes = function() {
    if(this.getMinutes() < 10)
        return `0${this.getMinutes()}`;
    return this.getMinutes();
}

function timestampToDate(timeStamp) {
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

let canvas = $('#game');
let view = canvas.getContext('2d');
