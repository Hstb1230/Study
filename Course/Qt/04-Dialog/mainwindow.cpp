#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew, &QAction::triggered, [=](){
        // 阻塞对话框
//        QDialog dlg(this);
//        dlg.exec();

        // 非阻塞对话框
//        QDialog * dlg = new QDialog(this);
//        dlg->resize(200, 100);
//        dlg->setAttribute(Qt::WA_DeleteOnClose);
//        dlg->show();

        // 信息对话框
//        QMessageBox::information(this, "信息", "信息文本", QMessageBox::Close | QMessageBox::Cancel);

        // 文件对话框
        QFileDialog::getOpenFileName(this, "选择文件", "C:/Users/Lab-202/Documents/", "文本文件 (*.txt *.exe)");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

