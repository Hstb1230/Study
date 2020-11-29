#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include "coin.h"

#include <QLabel>
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PlayScene(QWidget *parent = nullptr, int level = 0);
    void paintEvent(QPaintEvent *) override;

signals:
    void backToChooseScene();

private:
    int mLevel;
    Coin * coin[4][4];
    bool isWin = false;
    QLabel * winLabel;
};

#endif // PLAYSCENE_H
