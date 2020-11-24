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

    void paintEvent(QPaintEvent *) override;

    void timerEvent(QTimerEvent *) override;

private:
    Ui::Widget *ui;
    int posX = 0;
    int timer = 0;
};
#endif // WIDGET_H
