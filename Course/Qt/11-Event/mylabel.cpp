#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>
#include <QString>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
//    setMouseTracking(true);  // 开启鼠标追踪，只要鼠标经过区域就会触发移动事件
}

void MyLabel::enterEvent(QEvent *event)
{
//    qDebug() << __func__;
}

void MyLabel::leaveEvent(QEvent *event)
{
//    qDebug() << __func__;
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
//    if(ev->buttons() & Qt::LeftButton)  // 鼠标按键中有左键
//        qDebug() << __FUNCTION__ << QString("x = %1 , y = %2").arg(ev->x()).arg(ev->y());

//    qDebug() << __FUNCTION__ << QString("x = %1 , y = %2").arg(ev->x()).arg(ev->y());
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() & Qt::LeftButton)  // 鼠标按键中有左键
        qDebug() << __FUNCTION__ << QString("x = %1 , y = %2").arg(ev->x()).arg(ev->y());
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
        qDebug() << __func__;
}

bool MyLabel::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent * ev = static_cast<QMouseEvent *>(e);
        qDebug() << __FUNCTION__ << QString("x = %1 , y = %2").arg(ev->x()).arg(ev->y());
        return true;  // 拦截事件
    }
    return QLabel::event(e);
}
