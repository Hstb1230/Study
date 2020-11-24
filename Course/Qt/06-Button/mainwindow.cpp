#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 选中与取消选中时都会触发
    connect(ui->radioSexMan, &QRadioButton::toggled, [=](bool checked){
        qDebug() << checked << ' ' << ui->radioSexMan->isChecked();
    });

    // 0/不选 1/半选 2/全选
    connect(ui->cBox4, &QCheckBox::stateChanged, [=](int state){
        qDebug() << state;
    });

//    QListWidgetItem * item = new QListWidgetItem("锄禾日当午");
//    ui->listWidget->addItem(item);
//    item->setTextAlignment(Qt::AlignHCenter);
    QStringList poem;
    poem << "锄禾日当午"
         << "汗滴禾下土"
         << "谁知盘中餐"
         << "粒粒皆辛苦";
    ui->listWidget->addItems(poem);
    for(int i = 0; i < ui->listWidget->count(); i++)
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

