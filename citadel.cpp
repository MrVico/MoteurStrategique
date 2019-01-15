#include "citadel.h"

Citadel::Citadel(QPoint pos, QString team, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    if(team == QString("red"))
        setPixmap(QPixmap(":/images/redCitadel.png"));
    else if(team == QString("blue"))
        setPixmap(QPixmap(":/images/blueCitadel.png"));
    setPos(pos);
}
