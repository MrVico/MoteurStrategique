#ifndef SPAWNSOLDIERBUTTON_H
#define SPAWNSOLDIERBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class SpawnSoldierButton: public QGraphicsPixmapItem
{
public:
    SpawnSoldierButton(QGraphicsItem* parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsTextItem* text;
    int offset;
};

#endif // SPAWNSOLDIERBUTTON_H
