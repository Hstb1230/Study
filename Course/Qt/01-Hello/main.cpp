#include "my_widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // 有且只有一个
    My_Widget w;  // 窗口对象
    w.show();
    return a.exec();
}
