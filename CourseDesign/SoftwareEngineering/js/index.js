function $(e)
{
    return document.querySelector(e);
}

let view = $('#view');
let context = view.getContext('2d');

// 背景图片
let bg = new Image();
bg.src = 'img/bg.jpg';

// 全民飞机大战Logo
let logo = new Image();
logo.src = 'img/logo.png';

//加载时候的狗子和文字
let load = new Image();
let loadnum = 1;
let loadtime = 0;
// 加载进度
let loadRect = 1;
let loadtextblur = true,
    loadtextnum = -1,
    pointnum = 1;

//我方战斗机
let myplane = new Image();
myplane.src = 'img/myplane1.png';
let myplaneX = view.width / 2,
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
        context.drawImage(bg, 0, this.bgy1, 520, 854);
        context.drawImage(bg, 0, this.bgy2, 520, 854);
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
        let gradient = context.createLinearGradient(0, 0, 120, 60);
        gradient.addColorStop(0, '#ff9569');
        gradient.addColorStop(1, '#e92758');
        context.font = '30px  sans-serif';
        context.fillStyle = gradient;
        context.fillText('SCORE:' + this.score, 10, 50);
    },
    lifeing : function ()
    {
        context.font = '30px  sans-serif';
        context.fillStyle = '#D28140';
        context.fillText('LIFE:' + this.life, 400, 50);
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
        loadnum = 1;
        loadtime = 0;
        loadRect = 1;
        loadtextblur = true;
        loadtextnum = -1;
        pointnum = 1;
        myplaneX = view.width / 2;
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
        context.drawImage(logo, 110, 200);
    },
    loading : function ()
    {
        loadtime++;
        loadRect++;
        if( loadtime == 5 )
        {
            loadtime = 0;
            loadnum++;
            if( loadnum == 10 )
            {
                loadnum = 1;
            }
            load.src = `img/load${loadnum}.png`;
        }
        context.beginPath();
        context.fillStyle = 'white';
        context.fillRect(0, 0, 520, 800);
        let gradient = context.createLinearGradient(20, 500, 397, 30);
        gradient.addColorStop(0, '#29bdd9');
        gradient.addColorStop(1, '#276ace');
        context.fillStyle = gradient;
        context.fillRect(20, 500, loadRect, 30);
        context.closePath();
        context.drawImage(load, loadRect + 20, 480, 102, 72);

    },
    loadtext : function ()
    {
        if( loadtextblur == false )
        {
            loadtextnum--;
        }
        else if( loadtextblur == true )
        {
            loadtextnum += 2;
        }
        context.beginPath();
        context.font = '40px  sans-serif';
        context.fillStyle = 'black';
        context.fillText('加载中 ', 50, 450);
        context.beginPath();
        context.font = '80px  sans-serif';
        if( pointnum == 1 )
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
        else if( pointnum == 2 )
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
        else if( pointnum == 3 )
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
    myplane : function ( e )
    {

        myplaneX = e.offsetX;
        myplaneY = e.offsetY;
        context.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
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
                context.drawImage(bullet, bulletarr[i][0], bulletarr[i][1] - bulletarr[i][2]);
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
            if( enemyArr[i][1] + enemyArr[i][2] <= view.height )
            {
                context.drawImage(enemyall[enemyArr[i][3]], enemyArr[i][0], enemyArr[i][1] + enemyArr[i][2]);
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
        context.drawImage(myplane1boom, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
        if( myboomnum == 9 )
        {
            game.life -= 1;
            bulletarr = [];
            enemyArr = [];
            myplaneX = view.width / 2;
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
            context.drawImage(enemychangearr[i][5], enemychangearr[i][0], enemychangearr[i][1]);
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
            context.drawImage(warning1, 150, 200);
            context.drawImage(warning2, 190, 400);
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
        context.drawImage(bossbg, 0, this.bossbgy1);
        context.drawImage(bossbg, 0, this.bossbgy2);
        context.drawImage(bossbg, 0, this.bossbgy3);
        if( game.bosstime == 1 )
        {
            context.drawImage(boss, 0, this.bg2boss);
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
        game.loadtext();
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
            context.drawImage(myplane, myplaneX - myplane.width / 2, myplaneY - myplane.height / 2);
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

let startBtn = $('.startBtn');
startBtn.onclick = function ()
{
    startBtn.classList.add('none');
    game.gamestart = 0;
    game.gameload = 1;
};

view.onmousemove = function ( e )
{
    if( game.gamerun == 1 && game.dead == 0 )
    {
        game.myplane(e);
        this.style.cursor = 'none';
    }
    else
    {
        this.style.cursor = '';
    }
};

document.onkeydown = function ( event )
{
    if( event.keyCode == 8 && game.gamerun == 1 )
    {
        game.gua();
    }

};
