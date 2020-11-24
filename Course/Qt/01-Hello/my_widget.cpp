#include "my_widget.h"
#include "ui_my_widget.h"
#include <QPushButton>

My_Widget::My_Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::My_Widget)
{
    ui->setupUi(this);

    this->setFixedSize(600, 400);

    QPushButton * btn = new QPushButton("按钮", this);
    btn->move(200, 100);
    btn->resize(200, 100);


    this->stu = new Student();
    this->tea = new Teacher();

    void (Teacher::*hungrySignal)(QString) = &Teacher::hungry;
    void (Student::*treatSignal)(QString) = &Student::Treat;

    connect(this->tea, hungrySignal, this->stu, treatSignal);

    connect(btn, &QPushButton::clicked, this->tea, [=]() {
        emit tea->hungry("菜");
        this->close();
    });

//    emit this->tea->hungry();
}

My_Widget::~My_Widget()
{
    delete ui;
}

