#include "customsprite.h"

CustomSprite::CustomSprite(QString team, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->team = team;
}

bool CustomSprite::isInOurTeam(QString team)
{
    return this->team == team;
}
