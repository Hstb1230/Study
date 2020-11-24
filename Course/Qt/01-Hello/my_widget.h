#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include <QWidget>


#include "teacher.h"
#include "student.h"

QT_BEGIN_NAMESPACE
namespace Ui { class My_Widget; }
QT_END_NAMESPACE

class My_Widget : public QWidget
{
    Q_OBJECT

public:
    My_Widget(QWidget *parent = nullptr);
    ~My_Widget();

private:
    Ui::My_Widget *ui;

    Student * stu;
    Teacher * tea;

};
#endif // MY_WIDGET_H
