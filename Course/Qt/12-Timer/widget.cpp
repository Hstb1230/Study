#include "widget.h"
#include "ui_widget.h"

#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->timer1 = startTimer(500);
    this->timer2 = startTimer(1000);

    QTimer * timer3 = new QTimer(this);
//    timer3->start(300);
    connect(timer3, &QTimer::timeout, [=](){
        ui->label_3->setNum(++this->number3);
    });

    connect(ui->btnChange, &QPushButton::clicked, [=](){
        if(timer3->isActive())
            timer3->stop();
        else
            timer3->start(300);
    });

    connect(this, &Widget::locationChange, [=](bool leave){
        if(leave)
            timer3->stop();
        else
            timer3->start(300);
    });


}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent * e)
{
    if(e->timerId() == timer1)
        ui->label->setNum(++number1);
    else if(e->timerId() == timer2)
        ui->label_2->setNum(++number2);

}

void Widget::leaveEvent(QEvent *event)
{
    emit this->locationChange(true);
//    ui->btnChange->click();
}

void Widget::enterEvent(QEvent *event)
{
    qDebug() << __func__;
    emit this->locationChange(false);
//    ui->btnChange->click();
}

