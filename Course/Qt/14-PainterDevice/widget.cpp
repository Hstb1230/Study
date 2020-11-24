#include "widget.h"
#include "ui_widget.h"
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //////////////// Pixmap 绘图设备 /////////////
    /*
    QPixmap pix(500, 500);
    pix.fill();

    QPainter painter(&pix);  // 设置绘图设备为pixmap
    painter.setPen(QColor(Qt::black));
    painter.drawEllipse(50, 50, 250, 250);

    ui->label->setGeometry(50, 50, 500, 500);
    ui->label->setPixmap(pix);
    */

    //////////////// Image 绘图设备 //////////////
    /*
    QImage img(500, 500, QImage::Format_RGB32);
    img.fill(Qt::white);

    QPainter painter(&img);  // 设置绘图设备为pixmap
    painter.setPen(QColor(Qt::black));
    painter.drawEllipse(50, 50, 250, 250);

    img.save("E:/img.jpg");
    */


    ///////////// Picture 重现绘图 ////////////

    QPicture pic;
    QPainter painter(&pic);
    painter.setPen(QColor(Qt::black));
    painter.drawEllipse(50, 50, 250, 250);
    painter.end();

    pic.save(".picture");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    /////////// Qimage可以像素级修改图片 //////////////
    /*
    QImage img(":/img/coin.png");
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            img.setPixel(10 + i, 10 + j, Qt::white);
    QPainter painter(this);
    painter.drawImage(100, 100, img);
    */

    ////////// 还原Picture ///////////////////
    QPicture pic;
    pic.load(".picture");
    QPainter painter(this);
    painter.drawPicture(100, 100, pic);


}

