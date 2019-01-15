#include "mine.h"
#include "game.h"
#include "customsprite.h"
#include "minespot.h";

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Mine::Mine(QGraphicsItem *parent):QObject(), CustomSprite(parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/miningDisabled.png"));
}

// Start mining
void Mine::start()
{
    // We set the position of the mine spot
    setPos(lastMineSpot->pos());
    game->scene->removeItem(lastMineSpot);
    QBasicTimer* timer = new QBasicTimer();
    timer->start(1000, this);
}

bool Mine::canBePlaced()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size() > 0){
        for(int i=0; i<colliders.size(); i++){
            if(typeid(*(colliders[i])) == typeid(MineSpot)){
                setPixmap(QPixmap(":/images/mining.png"));
                // We store the last mine so we can use it if needed
                lastMineSpot = dynamic_cast<MineSpot*>(colliders[i]);
                return true;
            }
        }
    }
    setPixmap(QPixmap(":/images/miningDisabled.png"));
    return false;
}

void Mine::timerEvent(QTimerEvent *e)
{
    // Mine gold
    game->wallet->add(1);
}
