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
    Soldier(QGraphicsItem * parent=0);
    void start();
    bool canBePlaced();

protected:
    void timerEvent(QTimerEvent *e) override;
};

#endif // SOLDIER_H
