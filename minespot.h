#ifndef MINESPOT_H
#define MINESPOT_H

#include <QGraphicsPixmapItem>

class MineSpot: public QGraphicsPixmapItem
{
public:
    MineSpot(QPoint pos, QGraphicsItem* parent=0);
};

#endif // MINESPOT_H
