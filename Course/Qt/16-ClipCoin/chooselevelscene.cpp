#include "chooselevelscene.h"
#include "animationbutton.h"

#include <QPainter>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    this->setFixedSize(320, 555);

    AnimationButton * btnBack = new AnimationButton(this, "://res/BackButton.png", "://res/BackButtonSelected.png");
    btnBack->move(this->width() - btnBack->width(), this->height() - btnBack->height());
}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    QPixmap pix(":/res/OtherSceneBg.png");
    QPainter painter(this);
    painter.drawPixmap(0, 0, pix.scaled(this->width(), this->height()));

    pix.load(":/res/Title.png");
    painter.drawPixmap(10, 10, pix);
}
