#ifndef COIN_H
#define COIN_H

#include <QPushButton>
#include <QTimer>
#include <QWidget>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    explicit Coin(bool state, QWidget * parent);
    void flip();
    bool isPositive() const;

signals:

private:
    bool mState;
    int mSeq;

    QTimer timer;
};

#endif // COIN_H
