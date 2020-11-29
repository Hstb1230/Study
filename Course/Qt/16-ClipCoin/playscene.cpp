#include "animationbutton.h"
#include "playscene.h"

#include <QLabel>
#include <QPainter>
#include <QTimer>

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

    QLabel * labelLevel = new QLabel(this);
    labelLevel->setText(QString("Level: %1").arg(this->mLevel));
    labelLevel->setFont(QFont("黑体", 20));
    labelLevel->setGeometry(15, this->height() - 50, 130, 50);
}

void PlayScene::paintEvent(QPaintEvent *)
{
    QPixmap pix(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix.scaled(this->width(), this->height()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 10, pix);
}
