#ifndef BULLET_H
#define BULLET_H

#include "customsprite.h"

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QString team, QPoint pos, CustomSprite* target, QGraphicsItem * parent=0);

protected:
    void timerEvent(QTimerEvent *e) override;

private:
    QString team;
    CustomSprite* target;
    int speed;
};

#endif // BULLET_H
