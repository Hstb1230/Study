let float = $('.float');
let floatActionAfterClose = null;

float.addEventListener('transitionstart',
    function ()
    {
        // 阻止点击
        float.style.pointerEvents = 'none';
    }
)

float.addEventListener('transitionend',
    function ()
    {
        // 移除视图以便操作底层视图
        if(this.style.opacity <= 0)
            this.style.display = 'none';
        // 恢复点击
        float.style.pointerEvents = 'inherit';
    }
)

float.querySelector('.close').addEventListener('click',
    function ()
    {
        closeFloat();
        if(floatActionAfterClose !== null)
        {
            floatActionAfterClose();
            floatActionAfterClose = null;
        }
    }
)

function closeFloat()
{
    float.style.opacity = 0;
}

/*
// 关闭与开启悬浮窗（使用JS）
// 关闭悬浮窗（逐渐消失并禁止点击）
function closeFloat()
{
    if(float.style.opacity <= 0)
        float.style.opacity = 1;
    if(float.style.opacity >= 1)
        float.style.pointerEvents = 'none';
    let time = float.style.opacity * 100;
    time -= Math.ceil(time / 10) * 1.5;
    float.style.opacity = Math.max(0, time) / 100;
    if(float.style.opacity <= 0)
        float.style.display = 'none';
    else
        setTimeout(closeFloat, float.style.opacity * 100);
}

// 点击空白区域关闭悬浮窗（隐藏）
document.addEventListener('click',
    function ()
    {
        closeFloat();
        // $('.float').style.opacity = 0;
    },
);

$('.float .content').addEventListener('click',
    function ( e )
    {
        // 阻止触发默认操作
        e.stopPropagation();
        return false;
    },
);

function showFloat()
{
    if(float.style.opacity <= 0)
    {
        float.style.display = '';
        float.style.pointerEvents = '';
        float.style.opacity = 0.01;
    }
    let time = float.style.opacity * 100;
    time += Math.ceil(time / 10) * 1.8;
    float.style.opacity = Math.min(100, time) / 100;
    console.log(float.style.opacity);
    if(float.style.opacity < 1)
        setTimeout(showFloat, float.style.opacity * 100);
}
*/

function setFloat(e, className)
{
    let style = float.getAttribute("style") || '';
    if(style.indexOf('opacity') === -1 || float.style.opacity >= 1)
    {
        float.style.opacity = 0;
        // 用法
        sleep(800).then(() => {
            setFloat(e, className);
        });
        return;
    }
    className = className || '';
    float.style.display = '';
    let content = float.querySelector('.content');
    if(className !== '')
    {
        className.split(' ').forEach( s => {
            e.classList.add(s);
        })
    }
    content.innerHTML = '';
    if(typeof e === 'string')
        content.innerHTML = e;
    else
        content.append(e);
    // showFloat();
    // 延迟设置透明度，否则会因为display为none而缺少过渡动画
    setTimeout(() => {
        float.style.opacity = 1;
    }, 100);
}
