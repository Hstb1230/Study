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

let canvas = $('#game');
let view = canvas.getContext('2d');
