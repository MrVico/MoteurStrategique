#ifndef MINE_H
#define MINE_H

#include "CustomSprite.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class Mine: public QObject, public CustomSprite
{
    Q_OBJECT
public:
    Mine(QGraphicsItem * parent=0);
    void start();
    bool checkForCollisions();

protected:
    void timerEvent(QTimerEvent *e) override;
};

#endif // MINE_H
