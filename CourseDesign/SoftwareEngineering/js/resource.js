
let canvas = $('#game');
let view = canvas.getContext('2d');

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
        audioOfBG.play();
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

    bullet.src = 'img/bullet.png';

    enemyImg = new Array(4);
    for(i = 0; i < enemyImg.length; i++)
    {
        enemyImg[i] = new Image();
        enemyImg[i].src = `img/plane/enemy/${i}/plane.png`;
    }

    warning1.src = 'img/warning1.png';
    warning2.src = 'img/warning2.png';
    bossbg.src = 'img/bg2.jpg';
    boss.src = 'img/plane/enemy/boss/plane.png';

    enemyBoomImg = new Array(enemyImg.length);
    for(i = 0; i < enemyBoomImg.length; i++)
    {
        enemyBoomImg[i] = new Array(6);
        for(j = 0; j < enemyBoomImg[i].length; j++)
        {
            enemyBoomImg[i][j] = new Image();
            enemyBoomImg[i][j].src = `img/plane/enemy/${i}/boom/${j}.png`;
        }
    }
}

// 我方战斗机
let myPlane = new Image();
// 战斗机爆炸
let myPlaneBoom;
// 爆炸图序号
let myBoomSeq = 0,
    myboomtime = 0;

let myPlaneX = canvas.width / 2,
    myPlaneY = 730;

//战斗机子弹
let bullet = new Image();
let bullettime = 0,
    bulletnum = 0,
    bulletarr = [];

//敌机
let enemyTime = 0,
    enemyArr = [];
let enemyImg;
let enemyBoomImg;

//敌机爆炸
let enemychangearr = [];
//boss警告
let warning1 = new Image();
let warning2 = new Image();
let warningTime = 0;
let warningChange = 0;
//boss出场背景
let bossbg = new Image();
let boss = new Image();
//boss改变飞机速度
let bossattacktime = 0;
let bossattacknum = 1;

// 开始按钮
let startBtn = $('.startBtn');

loadGameResource();