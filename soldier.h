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
    Soldier(QString team, QGraphicsItem * parent=0);
    void start();
    bool canBePlaced();
    void moveTo(int x, int y);

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    void stop();
    bool checkFOV();

    int viewRange;
    QPoint target;
    int speed;
};

#endif // SOLDIER_H
