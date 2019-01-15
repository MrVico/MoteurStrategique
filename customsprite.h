#ifndef CUSTOMSPRITE_H
#define CUSTOMSPRITE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CustomSprite: public QGraphicsPixmapItem
{
public:
    CustomSprite(QString team, QGraphicsItem* parent=0);
    virtual void start() = 0;
    virtual bool canBePlaced() = 0;
    virtual void destroyed() = 0;
    void takeHit();
    void updateUI();
    bool isInOurTeam(QString team);

    QGraphicsTextItem* hpText;

protected:
    bool placed = false;
    QString team;
    int healthPoints;
};


#endif // CUSTOMSPRITE_H
