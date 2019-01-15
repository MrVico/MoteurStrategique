#include "soldier.h"
#include "game.h"
#include "customsprite.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Soldier::Soldier(QGraphicsItem *parent):QObject(), CustomSprite(parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/soldierSprite.png"));
}

// Start mining
void Soldier::start()
{
    QBasicTimer* timer = new QBasicTimer();
    timer->start(1000, this);
}

bool Soldier::canBePlaced()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size()>0){
        //setPixmap(QPixmap(":/images/miningDisabled.png"));
        return true;
    }
    //setPixmap(QPixmap(":/images/mining.png"));
    return false;
}

void Soldier::timerEvent(QTimerEvent *e)
{

}
