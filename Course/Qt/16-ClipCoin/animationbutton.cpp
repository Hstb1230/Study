#include "animationbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

/*
AnimationButton::AnimationButton(QWidget *parent) : QWidget(parent)
{

}
*/

AnimationButton::AnimationButton(QWidget *parent, QString DefaultImage, QString PressImage)
    : mDefaultImage(DefaultImage), mPressImage(PressImage)
{
    this->setParent(parent);

    QPixmap pix(mDefaultImage);
    if(pix.isNull())
    {
        qDebug() << "图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton { border: 0; }");

    this->setIcon(pix);
    this->setIconSize(this->size());
}

void AnimationButton::animationUp()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y() + 15, this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void AnimationButton::animationDown()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(this->x(), this->y() + 15, this->width(), this->height()));
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void AnimationButton::mousePressEvent(QMouseEvent * e)
{
    if(this->mPressImage.length())
    {
        QPixmap pix(mPressImage);
        if(pix.isNull())
        {
            qDebug() << "图片加载失败";
            return;
        }
        this->setIcon(pix);
    }
    // 如果不添加，就会失去动画效果
    return QPushButton::mousePressEvent(e);
}

void AnimationButton::mouseReleaseEvent(QMouseEvent * e)
{
    if(this->mPressImage.length())
    {
        QPixmap pix(mDefaultImage);
        if(pix.isNull())
        {
            qDebug() << "图片加载失败";
            return;
        }
        this->setIcon(pix);
    }
    return QPushButton::mouseReleaseEvent(e);
}

