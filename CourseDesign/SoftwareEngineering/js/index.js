function $(e)
{
    return document.querySelector(e);
}

let canvas = $('#canvas');
let view = canvas.getContext('2d');

// 背景图片
let bg = new Image();
bg.src = 'img/bg.jpg';

// 全民飞机大战Logo
let logo = new Image();
logo.src = 'img/logo.png';

//加载时候的狗子和文字
// let load = new Image();
let load = new Array(9);
for(let i = 0; i < 9; i++)
{
    load[i] = new Image();
    load[i].src = `./img/loading/${i}.png`;
}
// 加载图片的序号
let loadSeq = 0;
// 加载进度
let loadRect = 1;
// 符号 · 的移动方向
let loadTextToUp = true;
// 符号 · 的Y轴偏移量
let loadPointY = -1;
// 正被加载的符号 · 序号
let pointSeq = 0;

//我方战斗机
let myplane = new Image();
myplane.src = 'img/myplane1.png';
let myplaneX = canvas.width / 2,
    myplaneY = 730;
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
let myboomnum = 1,
    myboomtime = 0;
//敌机爆炸
let enemychangearr = [];
//boss警告
let warning1 = new Image();
warning1.src = 'img/warning1.png';
let warning2 = new Image();
warning2.src = 'img/warning2.png';
let warningtime = 0,
    warningchange = 0;
//boss出场背景
let bossbg = new Image();
bossbg.src = 'img/bg2.jpg';
let boss = new Image();
boss.src = 'img/planeboss.png';
//boss改变飞机速度
let bossattacktime = 0;
let bossattacknum = 1;

let game = {
    // 游戏状态
    state: 'running',

    gamestart : 1,
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
    bgon : function ()
    {
        view.drawImage(bg, 0, this.bgy1, 520, 854);
        view.drawImage(bg, 0, this.bgy2, 520, 854);
    },
    bgchange : function ()
    {
        this.bgy1++;
        this.bgy2++;
        if( this.bgy1 == 0 )
        {
            this.bgy1 = -854;
            this.bgy2 = 0;
        }
    },
    scoring : function ()
    {
        let gradient = view.createLinearGradient(0, 0, 120, 60);
        gradient.addColorStop(0, '#ff9569');
        gradient.addColorStop(1, '#e92758');
        view.font = '30px  sans-serif';
        view.fillStyle = gradient;
        view.fillText('SCORE:' + this.score, 10, 50);
    },
    lifeing : function ()
    {
        view.font = '30px  sans-serif';
        view.fillStyle = '#D28140';
        view.fillText('LIFE:' + this.life, 400, 50);
        if( game.dead == 1 && myboomnum == 9 && game.life > 0 )
        {
            game.dead = 0;
            bullettime = 0;
            bulletnum = 0;
            bulletarr = [];
            enemytime = 0;
            enemyArr = [];
            myboomnum = 1;
            myboomtime = 0;
            enemychangearr = [];
            myplane1boom.src = `img/myplane1boom${myboomnum}.png`;
        }
        else if( game.dead == 1 && game.life == 0 )
        {
            game.gameover = 1;
        }
    },
    gameovering : function ()
    {
        if( game.gameover == 1 )
        {
            game.gamestart = 1;
            game.gameover = 0;
            game.dead = 0;
            game.gamerun = 0;
        }
    },
    starting : function ()
    {
        startBtn.classList.remove('none');
        game.life = 3;
        game.score = 0;

        loadSeq = 0;
        loadRect = 1;
        loadTextToUp = true;
        loadPointY = -1;
        pointSeq = 0;

        myplaneX = canvas.width / 2;
        myplaneY = 730;
        bullettime = 0;
        bulletnum = 0;
        bulletarr = [];
        enemytime = 0;
        enemyArr = [];
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
        view.drawImage(logo, 110, 200);
    },
    // 加载动画
    loading : function ()
    {
        loadRect++;
        if( loadRect % 5 === 0)
        {
            loadSeq = (loadSeq + 1) % 9;
        }
        view.beginPath();
        view.fillStyle = 'white';
        view.fillRect(0, 0, 520, 800);
        let gradient = view.createLinearGradient(20, 500, 397, 30);
        gradient.addColorStop(0, '#29bdd9');
        gradient.addColorStop(1, '#276ace');
        view.fillStyle = gradient;
        view.fillRect(20, 500, loadRect, 30);
        view.closePath();
        view.drawImage(load[loadSeq], loadRect + 20, 480, 102, 72);
    },
    // 加载页的文本变化
    loadText : function ()
    {
        if( loadTextToUp === false )
        {
            loadPointY--;
        }
        else if( loadTextToUp === true )
        {
            loadPointY += 2;
        }

        view.beginPath();
        view.font = '40px  sans-serif';
        view.fillStyle = 'black';
        view.fillText('加载中 ', 50, 450);

        view.beginPath();
        view.font = '80px  sans-serif';

        let moveToY = [450, 450, 450];
        moveToY[pointSeq] -= loadPointY;

        view.fillText('. ', 200, moveToY[0]);
        view.fillText('. ', 240, moveToY[1]);
        view.fillText('. ', 280, moveToY[2]);

        if( loadPointY < 0 )
        {
            loadPointY = 0;
            loadTextToUp = true;
            pointSeq = (pointSeq + 1) % 3;
        }
        else if( loadPointY > 39 )
        {
            loadTextToUp = false;
        }

        view.closePath();
    },

    myplane : function ( e )
    {

        myplaneX = e.offsetX;
        myplaneY = e.offsetY;
        view.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
    },
    bulleton : function ()
    {
        bullettime++;
        let bulletX = myplaneX - bullet.width / 2;
        let bulletY = myplaneY - myplane.height / 2 - bullet.height;
        let num;
        if( game.bossattack == 1 )
        {
            num = 10;
        }
        else
        {
            num = 20;
        }
        if( bullettime >= num )
        {
            let changearr = [bulletX, bulletY, 0];
            bulletarr.push(changearr);
            bullettime = 0;
        }
    },
    bulletchange : function ()
    {
        let result = [];
        for(let i = 0; i < bulletarr.length; i++)
        {
            if( bulletarr[i][1] - bulletarr[i][2] >= 0 )
            {
                view.drawImage(bullet, bulletarr[i][0], bulletarr[i][1] - bulletarr[i][2]);
                bulletarr[i][2] += 4;
                result.push(bulletarr[i]);
            }
        }
        bulletarr = result;
    },

    enemy : function ()
    {
        enemytime++;
        let enemynum = parseInt(Math.random() * 4);
        if( game.bossattack == 1 )
        {
            num = 10;
        }
        else
        {
            num = 25;
        }
        if( enemytime >= num )
        {
            if( enemynum == 3 && Math.random() < 0.9 )
            {
                return;
            }
            else
            {
                let enemylife = 1;
                if( enemynum == 3 )
                {
                    enemylife = 5;
                }
                let changearr = [
                    Math.random() * 520 - enemyall[enemynum].width / 2, -enemyall[enemynum].height, 0, enemynum,
                    enemylife,
                ];
                enemyArr.push(changearr);
                enemytime = 0;
            }
        }
    },
    enemychange : function ()
    {
        let result = [];
        if( game.bossattack == 1 )
        {
            bossattacktime++;
            if( bossattacktime == 80 )
            {
                bossattacknum += 0.05;
                bossattacktime = 0;
            }
        }
        for(let i = 0; i < enemyArr.length; i++)
        {
            if( enemyArr[i][1] + enemyArr[i][2] <= canvas.height )
            {
                view.drawImage(enemyall[enemyArr[i][3]], enemyArr[i][0], enemyArr[i][1] + enemyArr[i][2]);
                if( enemyall[enemyArr[i][3]] == enemy4 )
                {
                    enemyArr[i][2] += 1.5 * bossattacknum;
                }
                else
                {
                    enemyArr[i][2] += 2 * bossattacknum;
                }
                result.push(enemyArr[i]);
            }
        }
        enemyArr = result;
    },
    myplaneboom : function ()
    {
        game.dead = 1;
        myboomtime++;
        if( myboomtime >= 10 )
        {
            myplane1boom.src = `img/myplane1boom${myboomnum}.png`;
            myboomnum++;
            myboomtime = 0;
        }
        view.drawImage(myplane1boom, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
        if( myboomnum == 9 )
        {
            game.life -= 1;
            bulletarr = [];
            enemyArr = [];
            myplaneX = canvas.width / 2;
            myplaneY = 750;
        }
    },
    myplaneisbroke : function ()
    {
        for(let i = 0; i < enemyArr.length; i++)
        {
            if(
                enemyArr[i][0] < myplaneX - myplane.width / 2
                && enemyArr[i][1] + enemyArr[i][2] < myplaneY - myplane.height / 2 + myplane.height
            )
            {
                if(
                    enemyArr[i][0] + enemyall[enemyArr[i][3]].width > myplaneX - myplane.width / 2
                    && enemyArr[i][1] + enemyArr[i][2] + enemyall[enemyArr[i][3]].height > myplaneY - myplane.height / 2
                )
                {
                    game.myplaneboom();
                }
            }
            else if(
                enemyArr[i][0] > myplaneX - myplane.width / 2
                && enemyArr[i][1] + enemyArr[i][2] < myplaneY - myplane.height / 2 + myplane.height
            )
            {
                if( enemyArr[i][0] < myplaneX - myplane.width / 2 + myplane.width && enemyArr[i][1] + enemyArr[i][2] + enemyall[enemyArr[i][3]].height > myplaneY - myplane.height / 2 )
                {
                    game.myplaneboom();
                }
            }
        }
    },
    enemyboom : function ()
    {
        let result = [];
        for(let i = 0; i < enemychangearr.length; i++)
        {
            enemychangearr[i][3]++;
            if( enemychangearr[i][3] >= 10 )
            {
                enemychangearr[i][5].src = `img/enemy${enemychangearr[i][2]}boom${enemychangearr[i][4]}.png`;
                enemychangearr[i][4]++;
                enemychangearr[i][3] = 0;
            }
            view.drawImage(enemychangearr[i][5], enemychangearr[i][0], enemychangearr[i][1]);
            if( enemychangearr[i][4] < 6 )
            {
                result.push(enemychangearr[i]);
            }
        }
        ;
        enemychangearr = result;
    },
    enemyisbroke : function ()
    {
        for(let i = 0; i < bulletarr.length; i++)
        {
            for(let x = 0; x < enemyArr.length; x++)
            {
                if(
                    bulletarr[i][0] < enemyArr[x][0]
                    && bulletarr[i][1] - bulletarr[i][2] < enemyArr[x][1] + enemyArr[x][2] + enemyall[enemyArr[x][3]].height
                    && bulletarr[i][1] - bulletarr[i][2] > enemyArr[x][1] + enemyArr[x][2]
                )
                {
                    if( bulletarr[i][0] + bullet.width > enemyArr[x][0] )
                    {
                        enemyArr[x][4]--;
                        if( enemyArr[x][4] == 0 )
                        {
                            let enemyboom = new Image();
                            enemychangearr.push([
                                enemyArr[x][0], enemyArr[x][1] + enemyArr[x][2], enemyArr[x][3] + 1, 0, 1, enemyboom,
                            ]);
                            if( enemyArr[x][3] == 3 )
                            {
                                game.score += 10;
                            }
                            else
                            {
                                game.score += 2;
                            }
                            enemyArr.splice(x, 1);
                        }
                        bulletarr.splice(i, 1);
                    }
                }
                else if(
                    bulletarr[i][0] > enemyArr[x][0]
                    && bulletarr[i][1] - bulletarr[i][2] < enemyArr[x][1] + enemyArr[x][2] + enemyall[enemyArr[x][3]].height
                    && bulletarr[i][1] - bulletarr[i][2] > enemyArr[x][1] + enemyArr[x][2]
                )
                {
                    if( bulletarr[i][0] < enemyArr[x][0] + enemyall[enemyArr[x][3]].width )
                    {
                        enemyArr[x][4]--;
                        if( enemyArr[x][4] == 0 )
                        {
                            let enemyboom = new Image();
                            enemychangearr.push([
                                enemyArr[x][0], enemyArr[x][1] + enemyArr[x][2], enemyArr[x][3] + 1, 0, 1, enemyboom,
                            ]);
                            if( enemyArr[x][3] == 3 )
                            {
                                game.score += 10;
                            }
                            else
                            {
                                game.score += 2;
                            }
                            enemyArr.splice(x, 1);
                        }
                        bulletarr.splice(i, 1);
                    }
                }
            }
        }
    },
    warning : function ()
    {
        warningchange++;
        warningtime++;
        if( warningtime >= 20 )
        {
            view.drawImage(warning1, 150, 200);
            view.drawImage(warning2, 190, 400);
            if( warningtime >= 80 )
            {
                warningtime = 0;
            }
        }
        if( warningchange == 500 )
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
    bossbgon : function ()
    {
        view.drawImage(bossbg, 0, this.bossbgy1);
        view.drawImage(bossbg, 0, this.bossbgy2);
        view.drawImage(bossbg, 0, this.bossbgy3);
        if( game.bosstime == 1 )
        {
            view.drawImage(boss, 0, this.bg2boss);
        }

    },
    bossbgchange : function ()
    {
        this.bossbgy1 += 2;
        this.bossbgy2 += 2;
        this.bossbgy3 += 2;
        this.bg2boss += 2;
        if( this.bg2boss == 800 )
        {
            this.bosstime = 0;
            this.bossattack = 1;
        }
        if( this.bossbgy3 == 800 )
        {
            this.bossbgy1 = -1540;
            this.bossbgy2 = -760;
            this.bossbgy3 = 20;
        }
    },

    gua : function ()
    {
        enemychangearr = [];
        for(let x = 0; x < enemyArr.length; x++)
        {
            let enemyboom = new Image();
            enemychangearr.push([enemyArr[x][0], enemyArr[x][1] + enemyArr[x][2], enemyArr[x][3] + 1, 0, 1, enemyboom]);
        }
        enemyArr = [];
    },
};

setInterval(function ()
{
    // 暂停游戏
    if(game.state === 'pause')
    {
        return;
    }
    game.bgon();
    game.bgchange();
    if( game.gamestart == 1 )
    {
        game.starting();
    }
    if( game.gameload == 1 )
    {
        if( loadRect >= 380 )
        {
            game.gameload = 0;
            game.gamerun = 1;
        }
        game.loading();
        game.loadText();
    }
    if( game.gamerun == 1 )
    {
        if( game.score >= 300 && game.bosstimeblur == true )
        {
            game.warnon = 1;
            game.gua();
            game.bosstimeblur = false;
        }
        if( game.bosstime == 1 || game.bossattack == 1 )
        {
            game.bossbgon();
            game.bossbgchange();
        }
        if( game.dead == 0 )
        {
            view.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
            if( game.bosstime == 0 && game.warnon == 0 )
            {
                game.enemy();
                game.enemychange();
            }
            game.bulleton();
            game.bulletchange();
            if( game.warnon == 1 )
            {
                game.warning();
            }
        }
        game.myplaneisbroke();
        game.enemyisbroke();
        game.enemyboom();
        game.lifeing();
        game.gameovering();
        game.scoring();
    }

}, 10);

// 开始按钮
let startBtn = $('.startBtn');
startBtn.onclick = function ()
{
    startBtn.classList.add('none');
    game.gamestart = 0;
    game.gameload = 1;
};

canvas.onmousemove = function ( e )
{
    if(game.state === 'running' && game.gamerun == 1 && game.dead == 0 )
    {
        game.myplane(e);
        this.style.cursor = 'none';
    }
    else
    {
        canvas.removeAttribute('style');
        // this.style.cursor = '';
    }
};

document.onkeydown = function ( e )
{
    if(e.key === 'Escape')
    {
        if(game.state === 'running')
        {
            // 暂停游戏
            game.state = 'pause';
        }
        else if(game.state === 'pause')
        {
            game.state = 'running';
        }
    }
    else if( e.key === 'Backspace' )
    {
        if(game.state === 'running')
        {
            // 清除敌机（调试）
            game.gua();
        }
    }
};
