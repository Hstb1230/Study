#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    index = ui->stackedWidget->currentIndex();
    connect(ui->btnChange, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(++index % 3);
    });

    ui->comboBox->addItems(QStringList() << "a" << "b" << "c");

    // 标签显示图片
//    ui->label->setPixmap(QPixmap(":/img/coin.png"));

    // 标签显示动图
    QMovie * gif = new QMovie(":/img/fan.gif");
    gif->start();
    ui->label->setFixedSize(gif->currentPixmap().width(), gif->currentPixmap().height());
    qDebug() << gif->currentPixmap().width() << " " << gif->currentPixmap().height();
    ui->label->setMovie(gif);
}

MainWindow::~MainWindow()
{
    delete ui;
}

