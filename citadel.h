#ifndef CITADEL_H
#define CITADEL_H

#include "customsprite.h"

#include <QGraphicsPixmapItem>

class Citadel: public CustomSprite
{
public:
    Citadel(QPoint pos, QString team, QGraphicsItem* parent=0);
    void start();
    bool canBePlaced();
    void destroyed();
};

#endif // CITADEL_H
