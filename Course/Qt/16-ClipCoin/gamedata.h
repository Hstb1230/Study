#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QObject>

class GameData : public QObject
{
    Q_OBJECT
public:
    static const int mData[21][4][4];

signals:

};

#endif // GAMEDATA_H

