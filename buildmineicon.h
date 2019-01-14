#ifndef BUILDMINEICON_H
#define BUILDMINEICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class BuildMineIcon: public QGraphicsPixmapItem
{
public:
    BuildMineIcon(QGraphicsItem* parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // BUILDMINEICON_H
