if(localStorage.getItem('m-bg') === null)
{
    localStorage.setItem('m-bg', true);
    localStorage.setItem('m-game', true);
}

let audioOfBG = $('#m-bg');

document.addEventListener('click', playBGM);
document.addEventListener('touchend', playBGM);

function playBGM()
{
    if(localStorage.getItem('m-bg') === 'true' && audioOfBG.paused)
    {
        audioOfBG.volume = 0;
        audioOfBG.play();
    }
}

// 背景图片
let bg = new Image();
bg.src = 'img/bg.jpg';

// 全民飞机大战Logo
let logo = new Image();
logo.src = 'img/logo.png';

function loadGameResource()
{
    myPlane.src = 'img/plane/my/plane.png';
    myPlaneBoom = new Array(9);
    for(i = 0; i < 9; i++)
    {
        myPlaneBoom[i] = new Image();
        myPlaneBoom[i].src = `img/plane/my/boom/${i}.png`;
    }

}

// 我方战斗机
let myPlane = new Image();
let myPlaneBoom;
loadGameResource();

let myPlaneX = canvas.width / 2,
    myPlaneY = 730;

//战斗机子弹
let bullet = new Image();
bullet.src = 'img/bullet.png';
let bullettime = 0,
    bulletnum = 0,
    bulletarr = [];
//敌机
let enemytime = 0,
    enemyArr = [];
let enemy1 = new Image();
enemy1.src = `img/enemy1.png`;
let enemy2 = new Image();
enemy2.src = `img/enemy2.png`;
let enemy3 = new Image();
enemy3.src = `img/enemy3.png`;
let enemy4 = new Image();
enemy4.src = `img/enemy4.png`;
let enemyall = [enemy1, enemy2, enemy3, enemy4];

//战斗机爆炸
let myplane1boom = new Image();

let myBoomSeq = 0,
    myboomtime = 0;
//敌机爆炸
let enemychangearr = [];
//boss警告
let warning1 = new Image();
warning1.src = 'img/warning1.png';
let warning2 = new Image();
warning2.src = 'img/warning2.png';
let warningTime = 0;
let warningChange = 0;
//boss出场背景
let bossbg = new Image();
bossbg.src = 'img/bg2.jpg';
let boss = new Image();
boss.src = 'img/planeboss.png';
//boss改变飞机速度
let bossattacktime = 0;
let bossattacknum = 1;

// 开始按钮
let startBtn = $('.startBtn');