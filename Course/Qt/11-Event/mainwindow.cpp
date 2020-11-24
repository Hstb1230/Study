#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 在事件分发器（Event）前执行
bool MainWindow::eventFilter(QObject *watched, QEvent *e)
{
    if(watched == ui->label)
    {
        if(e->type() == QEvent::MouseButtonPress)
        {
            qDebug() << __func__;
            return true;
        }
    }

    return QMainWindow::eventFilter(watched, e);
}

