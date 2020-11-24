#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabels(QStringList() << "英雄" << "英雄介绍");

    QTreeWidgetItem * powerItem = new QTreeWidgetItem(QStringList() << "力量");
    QStringList powerA;
    powerA << "a" << "b";
    powerItem->addChild(new QTreeWidgetItem(powerA));
    ui->treeWidget->addTopLevelItem(powerItem);

    ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << "敏捷"));
    ui->treeWidget->addTopLevelItem(new QTreeWidgetItem(QStringList() << "智力"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

