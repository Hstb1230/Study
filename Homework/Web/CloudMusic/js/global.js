const domain = 'http://localhost:3000';

function $(e) {
    return document.querySelector(e);
}

function $make(e) {
    return document.createElement(e);
}

function getParam(p) {
    // 捕获ID
    let query = location.search.slice(1).split('&');
    let value = null;
    query.forEach(element => {
        param = element.split('=');
        if(param[0] === p)
        {
            value = param[1];
            return;
        }
    });
    return value;
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
    if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60)
        fmt = '昨天';
    else if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60 * 2)
        fmt += '前天';
    else if(now.getFullYear() === t.getFullYear())
        return `${t.getFullMonth()}月${t.getFullDate()}日`;
    else if(now.getTime() / 1000 > Math.floor(timeStamp / 1000))
        return `${t.getFullYear()}年${t.getFullMonth()}月${t.getFullDate()}日`;
    fmt += `今天`;
    
    return fmt;
}

function formatTime(timeStamp) {
    let fmt = '';

    let now = new Date();
    now.setHours(0);
    now.setMinutes(0);
    now.setSeconds(0);
    now.setMilliseconds(0);

    let t = new Date(timeStamp);
    if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60)
        fmt = '昨天';
    else if(now.getTime() / 1000 - Math.floor(timeStamp / 1000) < 24 * 60 * 60 * 2)
        fmt += '前天';
    else if(now.getFullYear() === t.getFullYear())
        return `${t.getFullMonth()}月${t.getFullDate()}日`;
    else if(now.getTime() / 1000 > Math.floor(timeStamp / 1000))
        return `${t.getFullYear()}年${t.getFullMonth()}月${t.getFullDate()}日`;
    fmt += `${t.getFullHours()}:${t.getFullMinutes()}`;
    
    return fmt;
}