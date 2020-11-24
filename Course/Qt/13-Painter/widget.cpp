#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    QTimer * timerMove = new QTimer(this);
    connect(timerMove, &QTimer::timeout, [=]{
        update();
    });
    connect(ui->btnMove, &QPushButton::clicked, [=]{
        if(timerMove->isActive())
            timerMove->stop();
        else
            timerMove->start(300);
    });
    /*
    connect(ui->btnMove, &QPushButton::clicked, [=]{
        if(timer == 0)
            timer = startTimer(300);
        else
        {
            killTimer(timer);
            timer = 0;
        }
    });
    */
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{

    /*
    QPainter painter(this);

    // 画线
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));

    painter.setPen(QPen(QColor(255, 0, 0)));

    // 画圆
    painter.drawEllipse(QPoint(100, 100), 50, 50);

    painter.setPen(QPen(QColor(0, 255, 0)));
    painter.setBrush(QBrush(Qt::darkCyan, Qt::Dense6Pattern));

    // 画矩形
//    painter.drawRect(QRect(QPoint(100, 100), QPoint(200, 200)));
    painter.drawRect(QRect(QPoint(100, 100), QSize(100, 100)));

    painter.setPen(QPen(QColor(0, 0, 255)));

    painter.drawText(QRectF(15, 300, 150, 50), "好好学习，天天向上");
    */

    /*
    QPainter painter(this);
    // 画圆
    painter.drawEllipse(QPoint(100, 100), 50, 50);
    // 设置清晰度
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(QPoint(200, 100), 50, 50);
    */

    /*

    ////////////////// 偏移位置 ////////////////
    QPainter painter(this);
    painter.drawRect(QRect(QPoint(100, 100), QPoint(200, 200)));
    // 设置偏移位置
    painter.translate(100, 100);
    // 保存状态
    painter.save();

    painter.setPen(QPen(QColor(0, 255, 0)));
    painter.drawRect(QRect(QPoint(100, 100), QPoint(200, 200)));

    // 还原状态
    painter.restore();
    painter.translate(50, 50);

    painter.setPen(QPen(QColor(0, 0, 255)));
    painter.drawRect(QRect(QPoint(100, 100), QPoint(200, 200)));
    */


    //////////////// 画图 ////////////////
    QPainter painter(this);
    posX = (posX + 20) % width();
    painter.drawPixmap(posX, 100, QPixmap(":/img/coin.png"));

}

void Widget::timerEvent(QTimerEvent * e)
{
//    if(e->timerId() == timer)
//        update();
}












