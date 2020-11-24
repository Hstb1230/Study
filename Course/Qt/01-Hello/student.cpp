#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}


void Student::Treat()
{
    qDebug() << "恰饭";
}

void Student::Treat(QString eat)
{
    qDebug() << "吃" + eat;
}
