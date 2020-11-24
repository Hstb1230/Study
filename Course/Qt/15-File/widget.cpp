#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnChoose, &QPushButton::clicked, [=]{
        QString path = QFileDialog::getOpenFileName(this, "选择文本", "", "文本文件|(*.txt)");
        ui->textPath->setText(path);

        QFileInfo info(path);
        qDebug() << info;

        return;

        QFile file(path);
        file.open(QIODevice::ReadOnly);

        /*
        QByteArray content = file.readAll();
        // 转换编码（默认UTF-8)
        QTextCodec * code = QTextCodec::codecForName("gb2312");
        ui->textContent->setText(code->toUnicode(content));
        */

        // 会多一行
        while(!file.atEnd())
            ui->textContent->append(file.readLine());

        file.close();

    });

}

Widget::~Widget()
{
    delete ui;
}

