let tabBtn = document.querySelectorAll('.tab > label');
let screenView = document.querySelectorAll('.inner > .screen')

for (let i = 0; i < tabBtn.length; i++) {
    const element = tabBtn[i];
    element.onclick = () => {
        changeHeight(screenView[i], screenView[i].parentNode.parentNode);
    }
}

function changeHeight(obj, target)
{
    target.style.height = obj.scrollHeight + 'px';
}
