$ = e => document.querySelector(e);

$include = (e) => {
    let newScript = document.createElement('script');
    newScript.setAttribute('type','text/javascript');
    newScript.setAttribute('src',e);
    let head = document.querySelector('head');
    head.appendChild(newScript);
}

let canvas = $('#game');
let view = canvas.getContext('2d');
