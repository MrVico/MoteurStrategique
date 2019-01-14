#ifndef GOLD_H
#define GOLD_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class Gold: public QGraphicsTextItem{
public:
    Gold(QGraphicsItem * parent=0);
    void increase();
    int getGold();

private:
    QGraphicsPixmapItem* icon;
    int gold;
};

#endif // GOLD_H
