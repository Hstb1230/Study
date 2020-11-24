#ifndef CONNUMBER_H
#define CONNUMBER_H

#include <QWidget>

namespace Ui {
class ConNumber;
}

class ConNumber : public QWidget
{
    Q_OBJECT

public:
    explicit ConNumber(QWidget *parent = nullptr);
    ~ConNumber();

    int getNumber();
    void setNumber(int value);

private:
    Ui::ConNumber *ui;
};

#endif // CONNUMBER_H
