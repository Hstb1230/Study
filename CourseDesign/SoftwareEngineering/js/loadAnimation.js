// 加载动画
let load = {
    img : [],
    // 狗子X轴位置偏移
    rect: 1,
    textSeq : 0,
    textToUp: true,
    textY: -1,
    // 初始化资源
    init : () => {},
    // 加载动画
    playing : () => {},
    // 加载页的文本变化
    flushText : () => {},
};

load.init = () =>
{
    // 重置状态
    load.rect = 1;
    load.textSeq = 0;
    load.textToUp = true;
    load.textY = -1;
    if(load.img.length > 0)
        return;
    load.img = new Array(9);
    // new Image[9];
    for(let i = 0; i < 9; i++)
    {
        load.img[i] = new Image();
        load.img[i].src = `./img/loading/${i}.png`;
    }
}

load.playing = () =>
{
    load.rect++;
    let seq = Math.floor(load.rect / 5 % 9);
    view.beginPath();
    view.fillStyle = 'white';
    view.fillRect(0, 0, 520, 800);
    let gradient = view.createLinearGradient(20, 500, 397, 30);
    gradient.addColorStop(0, '#29bdd9');
    gradient.addColorStop(1, '#276ace');
    view.fillStyle = gradient;
    view.fillRect(20, 500, load.rect, 30);
    view.closePath();
    // console.log(this.seq, this.rect);
    view.drawImage(load.img[seq], load.rect + 20, 480, 102, 72);
    load.flushText();
}

load.flushText = () =>
{
    load.textY += load.textToUp ? 2 : -1;

    view.beginPath();
    view.font = '40px sans-serif';
    view.fillStyle = 'black';
    view.fillText('加载中 ', 50, 450);

    view.beginPath();
    view.font = '80px sans-serif';

    let moveToY = [450, 450, 450];
    moveToY[load.textSeq] -= load.textY;

    view.fillText('. ', 200, moveToY[0]);
    view.fillText('. ', 240, moveToY[1]);
    view.fillText('. ', 280, moveToY[2]);

    if( load.textY < 0 )
    {
        load.textToUp = true;
        load.textSeq = (load.textSeq + 1) % 3;
    }
    else if( load.textY > 39 )
    {
        load.textToUp = false;
    }

    view.closePath();
}

load.init();
