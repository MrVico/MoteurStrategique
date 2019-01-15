#include "minespot.h"
#include "game.h"

extern Game* game;

MineSpot::MineSpot(QPoint pos, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mineSpot.png"));
    setPos(pos);
    game->scene->addItem(this);
}
