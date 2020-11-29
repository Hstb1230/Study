#ifndef PLAYSCENE_H
#define PLAYSCENE_H

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
};

#endif // PLAYSCENE_H
