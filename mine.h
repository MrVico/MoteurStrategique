#ifndef MINE_H
#define MINE_H

#include "customsprite.h"
#include "minespot.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class Mine: public QObject, public CustomSprite
{
    Q_OBJECT
public:
    Mine(QString team, QGraphicsItem * parent=0);
    void start();
    bool canBePlaced();

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    MineSpot* lastMineSpot;
};

#endif // MINE_H
