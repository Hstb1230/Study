#include "mainscene.h"
#include "ui_mainscene.h"
#include "animationbutton.h"
#include "chooselevelscene.h"
#include <QPainter>
#include <QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    setFixedSize(320, 555);

    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币");

    AnimationButton * btnStart = new AnimationButton(this, ":/res/MenuSceneStartButton.png");
    btnStart->move((this->width() - btnStart->width()) / 2, (this->height() - btnStart->height()) * 0.8);


    ChooseLevelScene * chooseLevelScene = new ChooseLevelScene(this);

    connect(btnStart, &AnimationButton::clicked, [=]{
        btnStart->animationUp();
        btnStart->animationDown();

        QTimer::singleShot(500, this, [=]{
            this->hide();
            chooseLevelScene->show();
        });
    });

    connect(chooseLevelScene, &ChooseLevelScene::chooseSceneBack, [=]{
        this->show();
    });
}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPixmap pix(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 10, pix.scaled(pix.width() / 2, pix.height() / 2));
}

