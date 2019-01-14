#include "Mine.h"
#include "Game.h"
#include "CustomSprite.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Mine::Mine(QGraphicsItem *parent):QObject(), CustomSprite(parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/mining.png"));
}

// Start mining
void Mine::start()
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
    game->wallet->add(1);
}
