// 引用文件

$include('./js/loadAnimation.js');

// 背景图片
let bg = new Image();
bg.src = 'img/bg.jpg';

// 全民飞机大战Logo
let logo = new Image();
logo.src = 'img/logo.png';

// 我方战斗机
let myPlane = new Image();
myPlane.src = 'img/plane/my/plane.png';

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
let myboomnum = 1,
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

let game = {
    // 游戏状态
    state: 'playing',

    start : () => {},
    pause : () => {},

    // 使背景滚动
    bgY : -854,
    bgChange : () => {},

    gamestart : 1,
    gameload : 0,
    gamerun : 0,
    gameover : 0,
    dead : 0,
    score : 0,
    life : 3,
    // 显示警告
    warnOn : false,

    bossTime : false,
    bossAttack : false,


    scoring : function ()
    {
        let gradient = view.createLinearGradient(0, 0, 120, 60);
        gradient.addColorStop(0, '#ff9569');
        gradient.addColorStop(1, '#e92758');
        view.font = '30px  sans-serif';
        view.fillStyle = gradient;
        view.fillText('SCORE:' + game.score, 10, 50);
    },
    lifeing : function ()
    {
        view.font = '30px  sans-serif';
        view.fillStyle = '#D28140';
        view.fillText('LIFE:' + game.life, 400, 50);
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
    gameOvering : function ()
    {
        if( game.gameover == 1 )
        {
            game.gamestart = 1;
            game.gameover = 0;
            game.dead = 0;
            game.gamerun = 0;
        }
    },

    // 开始新一轮游戏，重置游戏状态
    starting : function ()
    {
        startBtn.classList.remove('none');
        game.life = 3;
        game.score = 0;

        myPlaneX = canvas.width / 2;
        myPlaneY = 730;
        bullettime = 0;
        bulletnum = 0;
        bulletarr = [];
        enemytime = 0;
        enemyArr = [];
        myboomnum = 1;
        myboomtime = 0;
        enemychangearr = [];

        warningTime = 0;
        warningChange = 0;

        bossattacktime = 0;
        bossattacknum = 1;
        game.bossbgy1 = -2420;
        game.bossbgy2 = -1640;
        game.bossbgy3 = -860;
        game.bg2boss = -262;

        game.bossTimeBlur = true;
        game.bossAttack = false;

        view.drawImage(logo, 110, 200);
    },

    myplane : function ( e )
    {

        myPlaneX = e.offsetX;
        myPlaneY = e.offsetY;
        view.drawImage(myPlane, myPlaneX - myPlane.width / 2, myPlaneY - myPlane.height / 2);
    },
    bulleton : function ()
    {
        bullettime++;
        let bulletX = myPlaneX - bullet.width / 2;
        let bulletY = myPlaneY - myPlane.height / 2 - bullet.height;
        let num;
        if( game.bossAttack )
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
        if( game.bossAttack )
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
        if( game.bossAttack )
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
        view.drawImage(myplane1boom, myPlaneX - myPlane.width / 2, myPlaneY - myPlane.height / 2);
        if( myboomnum == 9 )
        {
            game.life -= 1;
            bulletarr = [];
            enemyArr = [];
            myPlaneX = canvas.width / 2;
            myPlaneY = 750;
        }
    },
    myplaneisbroke : function ()
    {
        for(let i = 0; i < enemyArr.length; i++)
        {
            if(
                enemyArr[i][0] < myPlaneX - myPlane.width / 2
                && enemyArr[i][1] + enemyArr[i][2] < myPlaneY - myPlane.height / 2 + myPlane.height
            )
            {
                if(
                    enemyArr[i][0] + enemyall[enemyArr[i][3]].width > myPlaneX - myPlane.width / 2
                    && enemyArr[i][1] + enemyArr[i][2] + enemyall[enemyArr[i][3]].height > myPlaneY - myPlane.height / 2
                )
                {
                    game.myplaneboom();
                }
            }
            else if(
                enemyArr[i][0] > myPlaneX - myPlane.width / 2
                && enemyArr[i][1] + enemyArr[i][2] < myPlaneY - myPlane.height / 2 + myPlane.height
            )
            {
                if( enemyArr[i][0] < myPlaneX - myPlane.width / 2 + myPlane.width && enemyArr[i][1] + enemyArr[i][2] + enemyall[enemyArr[i][3]].height > myPlaneY - myPlane.height / 2 )
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
        warningChange++;
        warningTime++;
        if( warningTime >= 20 )
        {
            view.drawImage(warning1, 150, 200);
            view.drawImage(warning2, 190, 400);
            if( warningTime >= 80 )
            {
                warningTime = 0;
            }
        }
        if( warningChange == 500 )
        {
            // console.log('boss time');
            game.warnOn = false;
            game.bossTime = true;
        }

    },
    bossbgy1 : -2420,
    bossbgy2 : -1640,
    bossbgy3 : -860,
    bg2boss : -262,
    bossTimeBlur : true,
    bossBgShow : function ()
    {
        // console.log('bossBgShow');
        view.drawImage(bossbg, 0, game.bossbgy1);
        view.drawImage(bossbg, 0, game.bossbgy2);
        view.drawImage(bossbg, 0, game.bossbgy3);
        if( game.bossTime )
        {
            view.drawImage(boss, 0, game.bg2boss);
        }

    },
    bossBgChange : function ()
    {
        game.bossbgy1 += 2;
        game.bossbgy2 += 2;
        game.bossbgy3 += 2;
        game.bg2boss += 2;
        if( game.bg2boss == 800 )
        {
            game.bossTime = false;
            game.bossAttack = true;
        }
        if( game.bossbgy3 == 800 )
        {
            game.bossbgy1 = -1540;
            game.bossbgy2 = -760;
            game.bossbgy3 = 20;
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

// 暂停游戏
game.pause = () => {
    if(game.state !== 'playing')
        return;
    game.state = 'pause';
    canvas.isFocus = false;
}

// 改变背景
game.bgChange = () => {
    // 判断当前场景是否生效
    if(game.state === 'loading' || game.bossAttack)
        return;
    // 渲染两次背景，进行拼接
    view.drawImage(bg, 0, game.bgY, 520, 854);
    view.drawImage(bg, 0, game.bgY + 854, 520, 854);
    game.bgY++;
    if( game.bgY === 0 )
        game.bgY = -854;
}

setInterval(function ()
{
    // 暂停游戏
    if(game.state === 'pause')
    {
        return;
    }
    game.bgChange();
    if( game.gamestart == 1 )
    {
        game.starting();
    }
    if( game.gameload == 1 )
    {
        if( load.rect >= 380 )
        {
            game.gameload = 0;
            game.gamerun = 1;
        }
        load.playing();
    }
    if( game.gamerun == 1 )
    {
        if( game.score >= 300 && game.bossTimeBlur )
        {
            game.warnOn = true;
            game.gua();
            game.bossTimeBlur = false;
        }
        if( game.bossTime || game.bossAttack )
        {
            game.bossBgShow();
            game.bossBgChange();
        }
        if( game.dead == 0 )
        {
            view.drawImage(myPlane, myPlaneX - myPlane.width / 2, myPlaneY - myPlane.height / 2);
            if( !game.bossTime && !game.warnOn )
            {
                game.enemy();
                game.enemychange();
            }
            game.bulleton();
            game.bulletchange();
            if( game.warnOn )
            {
                game.warning();
            }
        }
        game.myplaneisbroke();
        game.enemyisbroke();
        game.enemyboom();
        game.lifeing();
        game.gameOvering();
        game.scoring();
    }

}, 10);

// 开始按钮
let startBtn = $('.startBtn');
startBtn.onclick = function ()
{
    load.init();

    startBtn.classList.add('none');
    game.gamestart = 0;
    game.gameload = 1;
};

canvas.onmousemove = function ( e )
{
    if(game.state === 'playing' && game.gamerun == 1 && game.dead == 0 )
    {
        game.myplane(e);
        canvas.style.cursor = 'none';
    }
    else
    {
        canvas.removeAttribute('style');
    }
};

canvas.onmouseenter = (e) => canvas.isFocus = true;

document.onkeydown = (e) =>
{
    if(!canvas.isFocus)
        return;
    if(e.key === 'Escape')
    {
        if(game.state === 'playing')
        {
            // 暂停游戏
            game.state = 'pause';
        }
        else if(game.state === 'pause')
        {
            game.state = 'playing';
        }
    }
    else if( e.key === 'Backspace' )
    {
        if(game.state === 'playing')
        {
            // 清除敌机（调试）
            game.gua();
        }
    }
};

// 当鼠标移出游戏界面时暂停游戏
document.onmouseout = document.onmousemove = (e) =>
{
    const left = canvas.parentElement.offsetLeft - 30;
    const right = canvas.parentElement.offsetLeft + canvas.parentElement.offsetWidth + 30;
    if((left <= e.clientX && e.clientX <= right))
        return;
    game.pause();
}
