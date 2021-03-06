let game = {
    // 游戏状态
    state : 'home',

    start : () =>
    {
    },
    pause : () =>
    {
    },

    // 使背景滚动
    bgY : -854,
    bgChange : () =>
    {
    },

    gameOver : false,
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
        // view.fillText('SCORE:' + game.score, 10, 50);
    },
    lifeing : function ()
    {
        view.font = '30px  sans-serif';
        view.fillStyle = '#D28140';
        // view.fillText('LIFE:' + game.life, 400, 50);
        if( game.dead == 1 && myBoomSeq === myPlaneBoom.length - 1 && game.life > 0 )
        {
            game.dead = 0;
            bullettime = 0;
            bulletnum = 0;
            bulletarr = [];
            enemyTime = 0;
            enemyArr = [];
            myBoomSeq = 0;
            myboomtime = 0;
            enemychangearr = [];
        }
        else if( game.dead == 1 && game.life == 0 )
        {
            // game.gameOver = true;
            game.state = 'over';
        }
    },
    gameIsOver : () => {},

    // 开始新一轮游戏，重置游戏状态
    reset : function ()
    {
        game.state = 'home';
        // 显示鼠标，开始游戏按钮
        canvas.removeAttribute('style');
        if( account.isLogin )
        {
            $('.main .game').classList.add('hide');
            $('.main .home').classList.remove('hide');
        }

        game.life = 3;
        game.score = 0;

        myPlaneX = canvas.width / 2;
        myPlaneY = 730;
        bullettime = 0;
        bulletnum = 0;
        bulletarr = [];
        enemyTime = 0;
        enemyArr = [];
        myBoomSeq = 0;
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


        game.gameOver = false;
        game.dead = 0;
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
        enemyTime++;
        let enemyType = parseInt(Math.random() * 4);
        // 生成飞机频率
        let enemyFrequency = (game.bossAttack ? 10 : 25);
        if( enemyTime < enemyFrequency )
            return;
        // 决定要不要生成大飞机
        if( enemyType === 3 && Math.random() < 0.9 )
            return;
        let enemyLife = 1;
        if( enemyType === 3 )
            enemyLife = 5;
        let enemyInfo = [
            Math.random() * 520 - enemyImg[enemyType].width / 2,
            -enemyImg[enemyType].height,
            0,
            enemyType,
            enemyLife,
        ];
        enemyArr.push(enemyInfo);
        enemyTime = 0;
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
                view.drawImage(enemyImg[enemyArr[i][3]], enemyArr[i][0], enemyArr[i][1] + enemyArr[i][2]);
                // if( enemyImg[enemyArr[i][3]] == enemy4 )
                if( enemyArr[i][3] === 3 )
                {
                    // 是大飞机，伤害减弱
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
            myBoomSeq = (myBoomSeq + 1) % myPlaneBoom.length;
            myboomtime = 0;
        }

        view.drawImage(myPlaneBoom[myBoomSeq], myPlaneX - myPlane.width / 2, myPlaneY - myPlane.height / 2);
        if( myBoomSeq === myPlaneBoom.length - 1 )
        {
            game.life -= 1;
            $('.main .game .heart .value').innerText = game.life;
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
                    enemyArr[i][0] + enemyImg[enemyArr[i][3]].width > myPlaneX - myPlane.width / 2
                    && enemyArr[i][1] + enemyArr[i][2] + enemyImg[enemyArr[i][3]].height > myPlaneY - myPlane.height / 2
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
                if( enemyArr[i][0] < myPlaneX - myPlane.width / 2 + myPlane.width && enemyArr[i][1] + enemyArr[i][2] + enemyImg[enemyArr[i][3]].height > myPlaneY - myPlane.height / 2 )
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
                enemychangearr[i][5] = enemyBoomImg[(enemychangearr[i][2] - 1)][(enemychangearr[i][4] - 1)];
                // enemychangearr[i][5].src = `img/enemy${enemychangearr[i][2]}boom${enemychangearr[i][4]}.png`;
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
                if( bulletarr.length <= i)
                    break;
                if(
                    bulletarr[i][0] < enemyArr[x][0]
                    && bulletarr[i][1] - bulletarr[i][2] < enemyArr[x][1] + enemyArr[x][2] + enemyImg[enemyArr[x][3]].height
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
                    && bulletarr[i][1] - bulletarr[i][2] < enemyArr[x][1] + enemyArr[x][2] + enemyImg[enemyArr[x][3]].height
                    && bulletarr[i][1] - bulletarr[i][2] > enemyArr[x][1] + enemyArr[x][2]
                )
                {
                    if( bulletarr[i][0] < enemyArr[x][0] + enemyImg[enemyArr[x][3]].width )
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

// 开始游戏
game.start = () =>
{
    // 隐藏鼠标
    canvas.style.cursor = 'none';
    if( game.state === 'home' )
    {
        load.init();
        game.state = 'loading';
        $('.main .home').classList.add('hide');
    }
    else if( game.state === 'pause' )
        game.state = 'playing';
};

// 继续游戏
game.continue = (time) =>
{
    if(game.life === 0)
    {
        // 没有生命，使用道具
        if(warehouse['resurrection'] <= 0)
        {
            let e = $make('div');
            e.innerHTML = `复活道具不足，<a onclick="floatOfStore()">立即购买</a>`;
            setFloat(e, 'message');
            // floatActionAfterClose = game.gameIsOver;
            floatActionAfterClose = () => {
                game.gameIsOver(true);
            }
            return;
        }
        game.life++;
        fetch('/api/user/call/revive')
            .then( res => res.json() )
            .then( res => {
                warehouse = res.data;
            })
    }
    time = time || 768
    closeFloat();
    game.state = 'pause';
    setTimeout(game.start, time);
}

// 退出游戏
game.exit = (report) => {
    closeFloat();
    setTimeout(game.reset, 512);
    report = report || false;
    // 上报分数
    if(report)
        submit({ score : game.score }, '/api/user/call/addPlayRecord')
}

// 暂停游戏
game.pause = () =>
{
    if( game.state !== 'playing' )
        return;
    game.state = 'pause';
    // 显示鼠标
    canvas.removeAttribute('style');

    let e = $make('div');
    e.innerHTML = `
        <h3>已暂停游戏</h3>
        <ul>
            <li>
                <div class="score">
                    <div class="i-score"></div>
                    ${ game.score }
                </div>
                <div class="heart">
                    <div class="i-heart"></div>
                    ${ game.life }
                </div>
            </li>
            <li>
                <div class="continue" onclick="game.continue()">
                    继续游戏
                </div>
            </li>
            <li>
                <div class="exit" onclick="game.exit()">
                    退出游戏
                </div>
            </li>
        </ul>
    `;
    setFloat(e, 'game-pause');
    floatActionAfterClose = game.continue;
};

game.gameIsOver = function (force)
{
    force = force || false;
    if( game.state === 'over' && (float.style.display === 'none' || force) )
    {
        // game.reset();
        let e = $make('div');
        e.innerHTML = `
            <ul>
                <li>
                    <div class="score">
                        <div class="i-score"></div>
                        ${ game.score }
                    </div>
                </li>
                <!--
                <li>
                    <div class="rank">
                        <div class="i-rank"></div>
                        排名
                    </div>
                </li>
                -->
                <li>
                    <div class="continue" onclick="game.continue()">
                        复活
                        <div class="i-heart">
                            <div class="count">
                                ${ warehouse['resurrection'] }
                            </div>
                        </div>
                    </div>
                </li>
                <li>
                    <div class="exit" onclick="game.exit(true)">
                        结束游戏
                    </div>
                </li>
            </ul>
        `;
        setFloat(e, 'game-over', 'game.exit(true)');
        floatActionAfterClose = game.reset;
    }
}

// 改变背景
game.bgChange = () =>
{
    // 判断当前场景是否生效
    if( game.state === 'loading' || game.bossAttack )
        return;
    // 渲染两次背景，进行拼接
    view.drawImage(bg, 0, game.bgY, 520, 854);
    view.drawImage(bg, 0, game.bgY + 854, 520, 854);
    game.bgY++;
    if( game.bgY === 0 )
        game.bgY = -854;
};

setInterval(() => {
    $('.main .game .heart .value').innerText = game.life;
    $('.main .game .score .value').innerText = game.score;
/*
    if(game.state === 'over' && float.style.display === 'none')
    {
        game.gameIsOver();
    }
*/
}, 1000)

setInterval(function ()
{
    // 暂停游戏
    if( game.state === 'pause' )
        return;
    game.bgChange();
    if( game.state === 'home' )
        // 只在首页显示LOGO
        view.drawImage(logo, 110, 200);
    else if( game.state === 'loading' )
    {
        if( load.isFinish() )
        {
            game.state = 'playing';
            $('.main .game').classList.remove('hide');
        }
        else
            load.playing();
    }
    else if( game.state === 'playing' )
    {
        // 设置Boss模式触发点
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
        game.gameIsOver();
        game.scoring();
    }

}, 10);

startBtn.onclick = () =>
{
    if(warehouse['play_count'] > 0)
        game.start();
    else
        setFloat('体力不足，请先<a onclick="floatOfStore()">购买</a>');
}

canvas.onmousemove = function ( e )
{
    // console.log(game.state, game.dead);
    // 更新飞机位置（轨迹）
    if( game.state === 'playing' && game.dead == 0 )
        game.myplane(e);
};

canvas.onmouseenter = ( e ) => canvas.isFocus = true;

document.onkeydown = ( e ) =>
{
    if( !canvas.isFocus )
        return;
    if( e.key === 'Escape' )
    {
        if( game.state === 'playing' )
            game.pause();
        else if( game.state === 'pause' )
            game.continue(512);
    }
    else if( e.key === 'Backspace' )
    {
        if( game.state === 'playing' )
            // 清除敌机（调试）
            game.gua();
    }
};

let allowLeft = (document.body.parentElement.offsetWidth / 2 - 260) - 50;
let allowRight = (document.body.parentElement.offsetWidth / 2 + 260) - 50;

// 因为不触发resize事件，只能定时获取
setInterval(() =>
{
    allowLeft = (document.body.parentElement.offsetWidth / 2 - 260) - 50;
    allowRight = (document.body.parentElement.offsetWidth / 2 + 260) + 50;
}, 2000);

// 当鼠标移出游戏界面时暂停游戏
document.onmouseout = document.onmousemove = ( e ) =>
{
    canvas.isFocus = (allowLeft <= e.clientX && e.clientX <= allowRight);
    if( !canvas.isFocus )
        game.pause();
};

game.reset();
