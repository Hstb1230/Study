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
        if(floatActionAfterClose !== null && typeof floatActionAfterClose !== 'undefined')
        {
            setTimeout(floatActionAfterClose, 800);
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

function setFloat(e, className, actionAfterClose, delay)
{
    let style = float.getAttribute("style") || '';
    // 如果悬浮窗已经弹出，则先关闭再延迟显示
    if(style.indexOf('opacity') === -1 || float.style.opacity >= 1)
    {
        float.style.opacity = 0;
        sleep(800).then(() => {
            setFloat(e, className, actionAfterClose, delay);
        });
        return;
    }
    // 设置样式
    className = className || '';
    float.style.display = '';
    if(className !== '')
    {
        // 如果是字符串但是需要设置样式，则创建一个div再设置样式
        if(typeof e === 'string')
        {
            let div = $make('div');
            div.innerHTML = e;
            e = div;
        }
        className.split(' ').forEach( s => {
            e.classList.add(s);
        })
    }
    // 设置悬浮窗内容
    let content = float.querySelector('.content');
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
    // 延迟执行与关闭后的回调
    if(typeof delay !== 'undefined')
    {
        floatActionAfterClose = null;
        if(typeof actionAfterClose !== 'undefined')
            setTimeout(actionAfterClose, delay);
        else
            setTimeout(closeFloat, delay);
    }
    else if(typeof actionAfterClose !== 'undefined')
    {
        floatActionAfterClose = actionAfterClose;
    }
}

function showPassword( e )
{
    let label = $(`.float label[for=${e}]`);
    console.log(`.float label[for=${e}]`, label);
    let pwd = label.querySelector('input');
    let icon = label.querySelector('i');
    if( pwd.type === 'password' )
    {
        pwd.type = 'text';
        icon.setAttribute('class', 'i-see');
    }
    else
    {
        pwd.type = 'password';
        icon.setAttribute('class', 'i-hide');
    }
}