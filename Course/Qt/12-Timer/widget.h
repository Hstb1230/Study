#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void timerEvent(QTimerEvent *) override;

    void leaveEvent(QEvent *event) override;
    void enterEvent(QEvent *event) override;

private:
    Ui::Widget *ui;

    int number1 = 0, number2 = 0, number3 = 0;
    int timer1 = NULL;
    int timer2 = NULL;

signals:
    void locationChange(bool leave);

};
#endif // WIDGET_H
