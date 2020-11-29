#include "animationbutton.h"
#include "playscene.h"
#include <gamedata.h>

#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

PlayScene::PlayScene(QWidget *parent, int level)
    : QMainWindow(parent), mLevel(level)
{
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    this->setFixedSize(320, 555);

    AnimationButton * btnBack = new AnimationButton(this, "://res/BackButton.png", "://res/BackButtonSelected.png");
    btnBack->move(this->width() - btnBack->width(), this->height() - btnBack->height());

    connect(btnBack, &AnimationButton::clicked, [=]{
        QTimer::singleShot(300, [=]{
            this->hide();
            emit this->backToChooseScene();
        });
    });

    {
        winLabel = new QLabel(this);
        QPixmap pix(":/res/LevelCompletedDialogBg.png");
        winLabel->setFixedSize(pix.size());
        winLabel->setPixmap(pix);
        winLabel->move((this->width() - pix.width()) * 0.5, -pix.height());
    }

    QLabel * labelLevel = new QLabel(this);
    labelLevel->setText(QString("Level: %1").arg(this->mLevel));
    labelLevel->setFont(QFont("黑体", 20));
    labelLevel->setGeometry(15, this->height() - 50, 130, 50);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
        {
            QLabel * bgCoin = new QLabel(this);
            bgCoin->setPixmap(QPixmap("://res/BoardNode.png"));
            bgCoin->setGeometry(0, 0, 50, 50);
            bgCoin->move(60 + 50 * i, 200 + 50 * j);
//            coin->setAlignment(Qt::AlignCenter);
            coin[i][j] = new Coin(GameData::mData[mLevel][i][j], bgCoin);
            connect(coin[i][j], &Coin::clicked, [=]{

                if(isWin)
                    return;

                coin[i][j]->flip();

                QTimer::singleShot(250, [=]{

                    int dx[] = { 0, 1, 0, -1 };
                    int dy[] = { 1, 0, -1, 0 };
                    for(int t = 0; t < 4; t++)
                    {
                        int x = dx[t] + i, y = dy[t] + j;
                        if(x < 0 || x >= 4 || y < 0 || y >= 4)
                            continue;
    //                    qDebug() << QString("( %1 , %2 )").arg(x).arg(y);
                        coin[x][y]->flip();
                    }

                    QTimer::singleShot(300, [this]{
                        int cnt = 0;
                        for(int i = 0; i < 4; i++)
                            for(int j = 0; j < 4; j++)
                                cnt += (coin[i][j]->isPositive());
                        if(cnt == 16)
                        {
                            isWin = true;
                            //将胜利的图片移动下来
                            QPropertyAnimation *animation=new QPropertyAnimation(winLabel, "geometry");
                            //设置时间间隔
                            animation->setDuration(1000);

                            //设置开始位置
                            animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->x() + winLabel->width(), winLabel->height()));
                            //设置结束位置
                            animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 120, winLabel->x() + winLabel->width(), winLabel->height() + 120));

                            //设置缓和曲线
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            //执行动画
                            animation->start();
                        }
                    });

                });

            });
        }
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPixmap pix(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix.scaled(this->width(), this->height()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 10, pix);
}
