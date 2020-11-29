#include "coin.h"
#include <QDebug>

Coin::Coin(bool state, QWidget * parent)
    : mState(state), mSeq(state ? 1 : 8)
{
    this->setParent(parent);
    QPixmap pix;
    QString imgPath = QString(":/res/Coin000%1.png").arg(mSeq);
    if(!pix.load(imgPath))
    {
        qDebug() << QString("图片 %1 加载失败").arg(imgPath);
        return;
    }

    this->setFixedSize(parent->width(), parent->height());
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));
    this->setStyleSheet("QPushButton{border:0;}");

    timer.setInterval(30);
    connect(&timer, &QTimer::timeout, [=]{
        if(mState)
        {
            if(++mSeq > 8)
            {
                mSeq = 8;
                mState = false;
                timer.stop();
                return;
            }
        }
        else
        {
            if(--mSeq < 1)
            {
                mSeq = 1;
                mState = true;
                timer.stop();
                return;
            }
        }
        this->setIcon(QPixmap(QString(":/res/Coin000%1.png").arg(mSeq)));
    });
}

void Coin::flip()
{
    timer.start();
}

bool Coin::isPositive() const
{
    return mState;
}
