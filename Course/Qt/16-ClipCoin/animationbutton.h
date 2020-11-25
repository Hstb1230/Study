#ifndef ANIMATIONBUTTON_H
#define ANIMATIONBUTTON_H

#include <QObject>
#include <QPushButton>

class AnimationButton : public QPushButton
{

private:
    QString mDefaultImage, mPressImage;

    Q_OBJECT
public:
//    explicit AnimationButton(QWidget *parent = nullptr);
    AnimationButton(QWidget *parent, QString DefaultImage, QString PressImage = "");


    void animationUp();
    void animationDown();

signals:

};

#endif // ANIMATIONBUTTON_H
