#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "性别" << "年龄");
    ui->tableWidget->setRowCount(5);

    QStringList data[3];
    data[0] << "a" << "b" << "c" << "d" << "e";
    data[1] << "boy" << "boy" << "girl" << "boy" << "girl";
    data[2] << "15" << "18" << "21" << "19" << "13";

    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 3; j++)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(data[j].at(i)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

