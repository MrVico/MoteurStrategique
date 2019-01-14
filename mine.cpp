#include "Mine.h"
#include "Game.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>

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

void Mine::timerEvent(QTimerEvent *e)
{
    // Mine gold
    game->gold->increase();
}
