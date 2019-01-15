#ifndef CITADEL_H
#define CITADEL_H

#include <QGraphicsPixmapItem>

class Citadel: public QGraphicsPixmapItem
{
public:
    Citadel(QPoint pos, QString team, QGraphicsItem* parent=0);
};

#endif // CITADEL_H
