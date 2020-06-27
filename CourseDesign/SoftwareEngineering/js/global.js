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

let canvas = $('#game');
let view = canvas.getContext('2d');
