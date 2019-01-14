#include "Mine.h"
#include "Game.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Mine::Mine(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/mining.png"));
}

void Mine::startMiningGold()
{
    QBasicTimer* timer = new QBasicTimer();
    timer->start(1000, this);
}

bool Mine::checkForCollisions()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size()>0){
        setPixmap(QPixmap(":/images/miningDisabled.png"));
        return true;
    }
    setPixmap(QPixmap(":/images/mining.png"));
    return false;
}

void Mine::timerEvent(QTimerEvent *e)
{
    // Mine gold
    game->gold->increase();
}
