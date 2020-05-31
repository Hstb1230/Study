const game = new Phaser.Game(320, 505, Phaser.AUTO, 'game');

game.States = {};

game.States.menu = function() {
    this.preload = () => {
        game.load.image('background', '/assets/background.png');
        game.load.image('ground', '/assets/ground.png');
        game.load.spritesheet('bird', '/assets/bird.png', 34, 24, 3);
        game.load.image('title', '/assets/title.png');
        game.load.image('start-button', '/assets/start-button.png');
        game.load.spritesheet('pipe', '/assets/pipes.png', 54, 320, 2);
        game.load.image('instruction', '/assets/instructions.png');
    };
    this.create = function() {
        const bg = game.add.tileSprite(0, 0, game.width, game.height, 'background');
        bg.autoScroll(-10, 0);
        const ground = game.add.tileSprite(0, game.height - 112, game.width, 112, 'ground');
        ground.autoScroll(-100, 0);
        const titleGroup = game.add.group();
        titleGroup.create(0, 0, 'title');
        const bird = titleGroup.create(190, 10, 'bird');
        bird.animations.add('fly');
        bird.animations.play('fly', 12, true);

        titleGroup.x = game.width * 0.15;
        titleGroup.y = game.height * 0.15;
        game.add.tween(titleGroup).to({ y: game.height * 0.25 }, 1000, null, true, 0, Number.MAX_VALUE, true);

        const btnStart = game.add.button(
                (game.width - 104) / 2,
                (game.height - 58) / 2,
                'start-button',
                () => {
                    console.log('tag', 'Turn to Play');
                    game.state.start('play');
                }
            );
            // 偏移中心点
            // btnStart.anchor.setTo(0.5, 0.5)
    }
}

game.States.play = function() {
    this.preload = () => {};
    this.create = function() {


        this.bg = game.add.tileSprite(0, 0, game.width, game.height, 'background');

        // 添加管道组
        this.pipeGroup = game.add.group();
        this.pipeGroup.enableBody = true;

        // 晚点添加地面, 这样就会遮挡管道的超出部分
        this.ground = game.add.tileSprite(0, game.height - 112, game.width, 112, 'ground');
            // ground.autoScroll(-100, 0)
        this.bird = game.add.sprite(50, 150, 'bird');
        this.bird.animations.add('fly');
        this.bird.animations.play('fly', 12, true);
        this.bird.anchor.setTo(0.5, 0.5);

        this.instruction = game.add.tileSprite(game.width / 2, this.ground.y - 98, 114, 98, 'instruction');
        this.instruction.anchor.setTo(0.5, 0);

        game.input.onDown.addOnce(this.startGame, this);
        // 添加物理引擎

        game.physics.enable(this.bird, Phaser.Physics.ARCADE);
        this.bird.body.gravity.y = 0;

        game.physics.enable(this.ground, Phaser.Physics.ARCADE);
        this.ground.body.immovable = true;

        this.hasStarted = false;

        game.time.events.loop(800, this.generatePipes, this);
        game.time.events.stop(false);
    }
    this.startGame = () => {
        console.log('Play', 'Start');
        this.instruction.destroy();
        this.bg.autoScroll(-10, 0);
        this.ground.autoScroll(-100, 0);
        this.bird.body.gravity.y = 1150;
        this.hasStarted = true;
        game.input.onDown.add(this.fly, this);
        game.time.events.start();
    };

    this.update = () => {
        if (!this.hasStarted) return;
        if (this.bird.body.gravity.y == 0 || this.bird.body.velocity.y == 0) return;
        game.physics.arcade.collide(this.bird, this.ground, this.hit, null, this);
        game.physics.arcade.overlap(this.bird, this.pipeGroup, this.hit, null, this); //检测与管道的碰撞
        if (this.bird.angle < 90) {
            this.bird.angle += 2.5 * 1 + Math.max(0, 1.0 - (Math.max((game.height - 112) - this.bird.y - 100, 0) / ((game.height - 112))));
            // console.log(this.bird.angle);
        }

    };
    this.hit = () => {
        this.bird.body.velocity.y = 0;
        this.bird.body.gravity.y = 0;
        // console.log('collide', '1');
        this.bg.autoScroll(0, 0);
        this.ground.autoScroll(0, 0);
        this.bird.animations.stop('fly');
        game.time.events.stop();
        // 停止重力作用, 使管道停留在原地
        this.pipeGroup.setAll('body.velocity.x', 0);
    };
    this.fly = () => {
        if(this.bird.body.gravity.y == 0 || this.bird.body.velocity.y == 0) return;
        this.bird.body.velocity.y = -300;
        game.add.tween(this.bird).to({ angle: -30 }, 100, null, true, 0, 0, false); //上升时头朝上的动画
    };

    this.generatePipes = (gap) => {
        console.log("管道出现了")
        // 设置两个管道间的间隔距离
        gap = gap || 100;
        // 上管道底部
        const gapTop = 110 + (Math.floor(((game.height - 112) - 110 - gap - 110) * Math.random()));
        // 下管道顶部
        const gapBottom = gapTop + gap;
        // console.log('gapTop', gapTop, 'gapBottom', gapBottom)

        const topPipe = game.add.sprite(game.width, gapTop - 320, 'pipe', 0, this.pipeGroup);
        const bottomPipe = game.add.sprite(game.width, gapBottom, 'pipe', 1, this.pipeGroup);
        this.pipeGroup.setAll('checkWorldBounds', true); //边界检测
        this.pipeGroup.setAll('outOfBoundsKill', true); //出边界后自动kill
        this.pipeGroup.setAll('body.velocity.x', -300);
    }
};

game.state.add('menu', game.States.menu);
game.state.add('play', game.States.play);
game.state.start('menu');
