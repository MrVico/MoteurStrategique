#ifndef CUSTOMSPRITE_H
#define CUSTOMSPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CustomSprite: public QGraphicsPixmapItem
{
public:
    CustomSprite(QGraphicsItem* parent=0);
    virtual void start() = 0;
    virtual bool canBePlaced() = 0;
};


#endif // CUSTOMSPRITE_H
