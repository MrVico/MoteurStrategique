#ifndef SOLDIER_H
#define SOLDIER_H

#include "customsprite.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class Soldier: public QObject, public CustomSprite
{
    Q_OBJECT
public:
    Soldier(string team, QGraphicsItem * parent=0);
    void start();
    bool canBePlaced();
    void destroyed();
    void setDestination(QPointF pos);
    void setDestination(int x, int y);

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    CustomSprite* checkFOV();
    bool fixCollision();
    void move();

    QBasicTimer* timer;
    int viewRange;
    QPointF destination;
    int speed;
    int reloadTime;

    int time;
};

#endif // SOLDIER_H
