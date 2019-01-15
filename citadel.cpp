#include "citadel.h"

Citadel::Citadel(QPoint pos, QString team, QGraphicsItem *parent): CustomSprite(team, parent)
{
    if(team == QString("red"))
        setPixmap(QPixmap(":/images/redCitadel.png"));
    else if(team == QString("blue"))
        setPixmap(QPixmap(":/images/blueCitadel.png"));
    setPos(pos);
    healthPoints = 100;
    updateUI();
}

void Citadel::start()
{

}

bool Citadel::canBePlaced()
{

}

void Citadel::destroyed()
{

}
