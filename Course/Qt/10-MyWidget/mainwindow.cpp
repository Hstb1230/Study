#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnGet, &QPushButton::clicked, [=](){
        qDebug() << ui->widget->getNumber();
    });

    connect(ui->btnSet, &QPushButton::clicked, [=](){
        ui->widget->setNumber(ui->widget->getNumber() / 2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

