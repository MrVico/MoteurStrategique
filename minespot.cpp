#include "minespot.h"

MineSpot::MineSpot(QPoint pos, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mine.png"));
    setPos(pos);
}
