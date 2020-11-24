#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(375, 250);


    connect(ui->btnExit, &QPushButton::clicked, [=](){
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

