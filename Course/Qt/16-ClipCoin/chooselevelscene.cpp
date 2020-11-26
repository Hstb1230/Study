#include "chooselevelscene.h"
#include "animationbutton.h"

#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QLabel>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    this->setFixedSize(320, 555);

    AnimationButton * btnBack = new AnimationButton(this, "://res/BackButton.png", "://res/BackButtonSelected.png");
    btnBack->move(this->width() - btnBack->width(), this->height() - btnBack->height());

    connect(btnBack, &AnimationButton::clicked, [=]{
        QTimer::singleShot(500, [=]{
            this->hide();
            emit this->chooseSceneBack();
        });
    });

    for(int i = 0; i < 20; i++)
    {
        AnimationButton * btnLevel = new AnimationButton(this, "://res/LevelIcon.png");
        btnLevel->move(15 + i % 4 * 75, 125 + i / 4 * 75);
        connect(btnLevel, &AnimationButton::clicked, [=]{
            qDebug() << QString("点击了关卡 %1").arg(i + 1);
        });

        QLabel * labelLevel = new QLabel(btnLevel);
        labelLevel->setFixedSize(btnLevel->width(), btnLevel->height());
        labelLevel->setText(QString::number(i + 1));
        labelLevel->setAlignment(Qt::AlignCenter);
        // 如果出现遮挡，可以设置穿透
        labelLevel->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPixmap pix(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix.scaled(this->width(), this->height()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 10, pix);
}
