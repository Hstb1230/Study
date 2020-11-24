#include "widget.h"
#include <QPushButton>
#include "test_windows.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    auto btnChange = new QPushButton("Open", this);
    btnChange->move(200, 200);

    auto win2 = new Test_Windows;

    connect(btnChange, &QPushButton::clicked, this, [=](){
        if(btnChange->text().compare("Open") == 0)
        {
            win2->show();
            btnChange->setText("Close");
        }
        else
        {
            win2->close();
            btnChange->setText("Open");
        }
        // window2->show();
    });

}

Widget::~Widget()
{
}

