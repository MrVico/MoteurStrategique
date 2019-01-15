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
    Mine(string team, bool initialMine = false, QGraphicsItem * parent=0);
    void start();
    bool canBePlaced();
    void destroyed();

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    bool initialMine;
    MineSpot* lastMineSpot;
    QBasicTimer* timer;
};

#endif // MINE_H
