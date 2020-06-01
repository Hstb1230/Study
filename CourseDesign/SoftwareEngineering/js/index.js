var canvas1 = document.getElementById('canvas1');
var context = canvas1.getContext('2d');
var canvasBig = document.getElementsByClassName('canvas-big')[0];

// 背景图片
const bg = new Image();
bg.src = 'img/bg.jpg';

// 全民飞机大战Logo
const logoImage = new Image();
logoImage.src = 'img/logo.png';

// 加载时候的狗子和文字
let loadImage = new Image();
// 加载动画的帧序号
let loadImageSequence = 0;
// 加载次数
let loadCount = 0;
let loadrect = 1;
var loadtextblur = true,
    loadtextnum = -1,
    pointnum = 1;

//我方战斗机
var myplane = new Image();
myplane.src = 'img/myplane1.png';
var myplaneX = canvas1.width / 2,
    myplaneY = 730;

//战斗机子弹
var bullet = new Image();
bullet.src = 'img/bullet.png';
var bullettime = 0,
    bulletnum = 0,
    bulletarr = [];

// 敌机
var enemytime = 0,
    enemyarr = [];
const enemy1 = new Image();
enemy1.src = `img/enemy1.png`;
const enemy2 = new Image();
enemy2.src = `img/enemy2.png`;
const enemy3 = new Image();
enemy3.src = `img/enemy3.png`;
const enemy4 = new Image();
enemy4.src = `img/enemy4.png`;
const enemyImageList = [enemy1, enemy2, enemy3, enemy4];

//战斗机爆炸
var myplane1boom = new Image();
var myboomnum = 1,
    myboomtime = 0;

//敌机爆炸
var enemychangearr = [];

//boss警告
var warning1 = new Image();
warning1.src = 'img/warning1.png';
var warning2 = new Image();
warning2.src = 'img/warning2.png';
var warningtime = 0,
    warningchange = 0;

//boss出场背景
var bossbg = new Image();
bossbg.src = 'img/bg2.jpg';
var boss = new Image();
boss.src = 'img/planeboss.png';

//boss改变飞机速度
var bossattacktime = 0;
var bossattacknum = 1;

const startBtn = document.querySelector('.start-btn');

let game = {
    state : {
        // 在游戏首页
        start : true,
    },
    gameload : 0,
    gamerun : 0,
    gameover : 0,
    dead : 0,
    score : 0,
    life : 3,
    bgy1 : -854,
    bgy2 : 0,
    warnon : 0,
    bosstime : 0,
    bossattack : 0,
    bgon : () =>
    {
        context.drawImage(bg, 0, this.bgy1, 520, 854);
        context.drawImage(bg, 0, this.bgy2, 520, 854);
    },
    bgchange : () =>
    {
        this.bgy1++;
        this.bgy2++;
        if( this.bgy1 === 0 )
        {
            this.bgy1 = -854;
            this.bgy2 = 0;
        }
    },
    scoring : () =>
    {
        var gradient = context.createLinearGradient(0, 0, 120, 60);
        gradient.addColorStop(0, '#ff9569');
        gradient.addColorStop(1, '#e92758');
        context.font = '30px  sans-serif';
        context.fillStyle = gradient;
        context.fillText('SCORE:' + this.score, 10, 50);
    },
    lifeing : () =>
    {
        context.font = '30px  sans-serif';
        context.fillStyle = '#D28140';
        context.fillText('LIFE:' + this.life, 400, 50);
        if( game.dead === 1 && myboomnum === 9 && game.life > 0 )
        {
            game.dead = 0;
            bullettime = 0;
            bulletnum = 0;
            bulletarr = [];
            enemytime = 0;
            enemyarr = [];
            myboomnum = 1;
            myboomtime = 0;
            enemychangearr = [];
            myplane1boom.src = `img/myplane1boom${myboomnum}.png`;
        }
        else if( game.dead === 1 && game.life === 0 )
        {
            game.gameover = 1;
        }
    },
    gameovering : () =>
    {
        if( game.gameover === 1 )
        {
            game.state.start = true;
            game.gameover = 0;
            game.dead = 0;
            game.gamerun = 0;
            canvas1.style.cursor = '';
        }
    },
    starting : () =>
    {
        startBtn.classList.remove('none');
        // 修改鼠标样式
        canvas1.style.cursor = 'none';
        game.life = 3;
        game.score = 0;
        loadImageSequence = 0;
        loadCount = 0;
        loadrect = 1;
        loadtextblur = true;
        loadtextnum = -1;
        pointnum = 1;
        myplaneX = canvas1.width / 2;
        myplaneY = 730;
        bullettime = 0;
        bulletnum = 0;
        bulletarr = [];
        enemytime = 0;
        enemyarr = [];
        myboomnum = 1;
        myboomtime = 0;
        enemychangearr = [];
        warningtime = 0;
        warningchange = 0;
        bossattacktime = 0;
        bossattacknum = 1;
        game.bossbgy1 = -2420;
        game.bossbgy2 = -1640;
        game.bossbgy3 = -860;
        game.bg2boss = -262;
        game.bosstimeblur = true;
        game.bossattack = 0;
        context.drawImage(logoImage, 110, 200);
    },
    loading : () =>
    {
        loadCount = (loadCount + 1) % 5;
        if( loadCount === 0 )
        {
            // 每 50ms 切换一帧
            loadImageSequence = (loadImageSequence + 1) % 9;
            loadImage.src = `img/loadingAnimation/${loadImageSequence}.png`;
        }
        loadrect++;
        context.beginPath();
        context.fillStyle = 'white';
        context.fillRect(0, 0, 520, 800);
        var gradient = context.createLinearGradient(20, 500, 397, 30);
        gradient.addColorStop(0, '#29bdd9');
        gradient.addColorStop(1, '#276ace');
        context.fillStyle = gradient;
        context.fillRect(20, 500, loadrect, 30);
        context.closePath();
        context.drawImage(loadImage, loadrect + 20, 480, 102, 72);

    },
    loadtext : () =>
    {
        if( loadtextblur === false )
        {
            loadtextnum--;
        }
        else if( loadtextblur === true )
        {
            loadtextnum += 2;
        }
        context.beginPath();
        context.font = '40px  sans-serif';
        context.fillStyle = 'black';
        context.fillText('加载中 ', 50, 450);
        context.beginPath();
        context.font = '80px  sans-serif';
        if( pointnum === 1 )
        {
            context.fillText('. ', 200, 450 - loadtextnum);
            context.fillText('. ', 240, 450);
            context.fillText('. ', 280, 450);
            if( loadtextnum < 0 )
            {
                pointnum = 2;
                loadtextnum = 0;
                loadtextblur = true;
            }
            else if( loadtextnum > 39 )
            {
                loadtextblur = false;
            }
        }
        else if( pointnum === 2 )
        {
            context.fillText('. ', 200, 450);
            context.fillText('. ', 240, 450 - loadtextnum);
            context.fillText('. ', 280, 450);
            if( loadtextnum < 0 )
            {
                pointnum = 3;
                loadtextnum = 0;
                loadtextblur = true;
            }
            else if( loadtextnum > 39 )
            {
                loadtextblur = false;
            }
        }
        else if( pointnum === 3 )
        {
            context.fillText('. ', 200, 450);
            context.fillText('. ', 240, 450);
            context.fillText('. ', 280, 450 - loadtextnum);
            if( loadtextnum < 0 )
            {
                pointnum = 1;
                loadtextnum = 0;
                loadtextblur = true;
            }
            else if( loadtextnum > 39 )
            {
                loadtextblur = false;
            }
        }
        context.closePath();
    },
    // 移动自己飞机位置
    moveMyPlane : ( e ) =>
    {

        myplaneX = e.offsetX;
        myplaneY = e.offsetY;
        context.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
    },
    bulleton : () =>
    {
        bullettime++;
        var bulletX = myplaneX - bullet.width / 2;
        var bulletY = myplaneY - myplane.height / 2 - bullet.height;
        var num;
        if( game.bossattack === 1 )
        {
            num = 10;
        }
        else
        {
            num = 20;
        }
        if( bullettime >= num )
        {
            var changearr = [bulletX, bulletY, 0];
            bulletarr.push(changearr);
            bullettime = 0;
        }
    },
    bulletchange : () =>
    {
        var result = [];
        for(var i = 0; i < bulletarr.length; i++)
        {
            if( bulletarr[i][1] - bulletarr[i][2] >= 0 )
            {
                context.drawImage(bullet, bulletarr[i][0], bulletarr[i][1] - bulletarr[i][2]);
                bulletarr[i][2] += 4;
                result.push(bulletarr[i]);
            }
        }
        bulletarr = result;
    },

    enemy : () =>
    {
        enemytime++;
        var enemynum = parseInt(Math.random() * 4);
        if( game.bossattack === 1 )
        {
            num = 10;
        }
        else
        {
            num = 25;
        }
        if( enemytime >= num )
        {
            if( enemynum === 3 && Math.random() < 0.9 )
            {
                return;
            }
            else
            {
                var enemylife = 1;
                if( enemynum === 3 )
                {
                    enemylife = 5;
                }
                var changearr = [
                    Math.random() * 520 - enemyImageList[enemynum].width / 2, -enemyImageList[enemynum].height, 0,
                    enemynum, enemylife,
                ];
                enemyarr.push(changearr);
                enemytime = 0;
            }
        }
    },
    enemychange : () =>
    {
        var result = [];
        if( game.bossattack === 1 )
        {
            bossattacktime++;
            if( bossattacktime === 80 )
            {
                bossattacknum += 0.05;
                bossattacktime = 0;
            }
        }
        for(let i = 0; i < enemyarr.length; i++)
        {
            if( enemyarr[i][1] + enemyarr[i][2] <= canvas1.height )
            {
                context.drawImage(enemyImageList[enemyarr[i][3]], enemyarr[i][0], enemyarr[i][1] + enemyarr[i][2]);
                if( enemyImageList[enemyarr[i][3]] === enemy4 )
                {
                    enemyarr[i][2] += 1.5 * bossattacknum;
                }
                else
                {
                    enemyarr[i][2] += 2 * bossattacknum;
                }
                result.push(enemyarr[i]);
            }
        }
        enemyarr = result;
    },
    // 飞机被击毁
    planeIsBoom : () =>
    {
        game.dead = 1;
        myboomtime++;
        if( myboomtime >= 10 )
        {
            myplane1boom.src = `img/myplane1boom${myboomnum}.png`;
            myboomnum++;
            myboomtime = 0;
        }
        context.drawImage(myplane1boom, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
        if( myboomnum === 9 )
        {
            game.life -= 1;
            bulletarr = [];
            enemyarr = [];
            myplaneX = canvas1.width / 2;
            myplaneY = 750;
        }
    },
    // 判断自身是否被击毁
    judgePlaneIsBroke : () =>
    {
        for(let i = 0; i < enemyarr.length; i++)
        {
            if(
                enemyarr[i][0] < myplaneX - myplane.width / 2
                && enemyarr[i][1] + enemyarr[i][2] < myplaneY - myplane.height / 2 + myplane.height
            )
            {
                if( enemyarr[i][0] + enemyImageList[enemyarr[i][3]].width > myplaneX - myplane.width / 2
                    && enemyarr[i][1] + enemyarr[i][2] + enemyImageList[enemyarr[i][3]].height > myplaneY - myplane.height / 2 )
                {
                    game.planeIsBoom();
                }
            }
            else if(
                enemyarr[i][0] > myplaneX - myplane.width / 2
                && enemyarr[i][1] + enemyarr[i][2] < myplaneY - myplane.height / 2 + myplane.height
            )
            {
                if( enemyarr[i][0] < myplaneX - myplane.width / 2 + myplane.width
                    && enemyarr[i][1] + enemyarr[i][2] + enemyImageList[enemyarr[i][3]].height > myplaneY - myplane.height / 2 )
                {
                    game.planeIsBoom();
                }
            }
        }
    },
    enemyboom : () =>
    {
        var result = [];
        for(let i = 0; i < enemychangearr.length; i++)
        {
            enemychangearr[i][3]++;
            if( enemychangearr[i][3] >= 10 )
            {
                enemychangearr[i][5].src = `img/enemy${enemychangearr[i][2]}boom${enemychangearr[i][4]}.png`;
                enemychangearr[i][4]++;
                enemychangearr[i][3] = 0;
            }
            context.drawImage(enemychangearr[i][5], enemychangearr[i][0], enemychangearr[i][1]);
            if( enemychangearr[i][4] < 6 )
            {
                result.push(enemychangearr[i]);
            }
        }
        enemychangearr = result;
    },
    enemyisbroke : () =>
    {
        for(let i = 0; i < bulletarr.length; i++)
        {
            for(let x = 0; x < enemyarr.length; x++)
            {
                if( bulletarr[i][0] < enemyarr[x][0] && bulletarr[i][1] - bulletarr[i][2] < enemyarr[x][1] + enemyarr[x][2] + enemyImageList[enemyarr[x][3]].height && bulletarr[i][1] - bulletarr[i][2] > enemyarr[x][1] + enemyarr[x][2] )
                {
                    if( bulletarr[i][0] + bullet.width > enemyarr[x][0] )
                    {
                        enemyarr[x][4]--;
                        if( enemyarr[x][4] === 0 )
                        {
                            var enemyboom = new Image();
                            enemychangearr.push([
                                enemyarr[x][0], enemyarr[x][1] + enemyarr[x][2], enemyarr[x][3] + 1, 0, 1, enemyboom,
                            ]);
                            if( enemyarr[x][3] === 3 )
                            {
                                game.score += 10;
                            }
                            else
                            {
                                game.score += 2;
                            }
                            enemyarr.splice(x, 1);
                        }
                        bulletarr.splice(i, 1);
                    }
                }
                else if( bulletarr[i][0] > enemyarr[x][0] && bulletarr[i][1] - bulletarr[i][2] < enemyarr[x][1] + enemyarr[x][2] + enemyImageList[enemyarr[x][3]].height && bulletarr[i][1] - bulletarr[i][2] > enemyarr[x][1] + enemyarr[x][2] )
                {
                    if( bulletarr[i][0] < enemyarr[x][0] + enemyImageList[enemyarr[x][3]].width )
                    {
                        enemyarr[x][4]--;
                        if( enemyarr[x][4] === 0 )
                        {
                            var enemyboom = new Image();
                            enemychangearr.push([
                                enemyarr[x][0], enemyarr[x][1] + enemyarr[x][2], enemyarr[x][3] + 1, 0, 1, enemyboom,
                            ]);
                            if( enemyarr[x][3] === 3 )
                            {
                                game.score += 10;
                            }
                            else
                            {
                                game.score += 2;
                            }
                            enemyarr.splice(x, 1);
                        }
                        bulletarr.splice(i, 1);
                    }
                }
            }
        }
    },
    warning : () =>
    {
        warningchange++;
        warningtime++;
        if( warningtime >= 20 )
        {
            context.drawImage(warning1, 150, 200);
            context.drawImage(warning2, 190, 400);
            if( warningtime >= 80 )
            {
                warningtime = 0;
            }
        }
        if( warningchange === 500 )
        {
            game.warnon = 0;
            game.bosstime = 1;
        }

    },
    bossbgy1 : -2420,
    bossbgy2 : -1640,
    bossbgy3 : -860,
    bg2boss : -262,
    bosstimeblur : true,
    bossbgon : () =>
    {
        context.drawImage(bossbg, 0, this.bossbgy1);
        context.drawImage(bossbg, 0, this.bossbgy2);
        context.drawImage(bossbg, 0, this.bossbgy3);
        if( game.bosstime === 1 )
        {
            context.drawImage(boss, 0, this.bg2boss);
        }

    },
    bossbgchange : () =>
    {
        this.bossbgy1 += 2;
        this.bossbgy2 += 2;
        this.bossbgy3 += 2;
        this.bg2boss += 2;
        if( this.bg2boss === 800 )
        {
            this.bosstime = 0;
            this.bossattack = 1;
        }

        if( this.bossbgy3 === 800 )
        {
            this.bossbgy1 = -1540;
            this.bossbgy2 = -760;
            this.bossbgy3 = 20;
        }
    },
    // bossY : -262,
    // bossX : 0,
    // bossfirstime : 0,
    // bosssecondtime : 0,
    // beatboss : function(){
    //     context.drawImage(boss,this.bossX,this.bossY);
    //     if(obj.bossY <= 0){
    //         obj.bossfirstime ++;
    //         if( obj.bossfirstime == 4){
    //             obj.bossY++;
    //             obj.bossfirstime = 0;
    //         }
    //     }else{
    //         obj.bosssecondtime++;
    //         if(obj.bosssecondtime == 2){
    //             obj.bossX++;
    //             obj.bossfirstime = 0;
    //         }
    //     }
    // },


    gua : () =>
    {
        enemychangearr = [];
        for(let x = 0; x < enemyarr.length; x++)
        {
            var enemyboom = new Image();
            enemychangearr.push([enemyarr[x][0], enemyarr[x][1] + enemyarr[x][2], enemyarr[x][3] + 1, 0, 1, enemyboom]);
        }
        enemyarr = [];
    },
};

setInterval(() =>
{
    game.bgon();
    game.bgchange();
    if( game.state.start )
    {
        game.starting();
    }
    if( game.gameload === 1 )
    {
        if( loadrect >= 397 )
        {
            game.gameload = 0;
            game.gamerun = 1;
        }
        game.loading();
        game.loadtext();
    }
    if( game.gamerun === 1 )
    {
        if( game.score >= 300 && game.bosstimeblur === true )
        {
            game.warnon = 1;
            game.gua();
            game.bosstimeblur = false;
        }
        if( game.bosstime === 1 || game.bossattack === 1 )
        {
            game.bossbgon();
            game.bossbgchange();
        }
        if( game.dead === 0 )
        {
            context.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
            if( game.bosstime === 0 && game.warnon === 0 )
            {
                game.enemy();
                game.enemychange();
            }
            game.bulleton();
            game.bulletchange();
            if( game.warnon === 1 )
            {
                game.warning();
            }
        }
        game.judgePlaneIsBroke();
        game.enemyisbroke();
        game.enemyboom();
        game.lifeing();
        game.gameovering();
        game.scoring();
    }

}, 10);

startBtn.onclick = () =>
{
    startBtn.classList.add('none');
    game.state.start = false;
    game.gameload = 1;
};

canvas1.onmousemove = e =>
{
    if( game.gamerun === 1 && game.dead === 0 )
    {
        game.moveMyPlane(e);
    }
};

document.onkeydown = ( e ) =>
{
    console.log(e);
    if( e.key === 'Backspace' )
    {
        // 作弊器
        if( game.gamerun === 1 )
        {
            game.gua();
        }
    }
};