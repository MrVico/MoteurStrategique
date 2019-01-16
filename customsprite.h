#ifndef CUSTOMSPRITE_H
#define CUSTOMSPRITE_H

using namespace std;

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class CustomSprite: public QGraphicsPixmapItem
{
public:
    CustomSprite(string team, QGraphicsItem* parent=0);
    virtual void start() = 0;
    virtual bool canBePlaced() = 0;
    virtual void destroyed() = 0;
    void takeHit();
    void updateUI();
    bool isInOurTeam(string team);

    QGraphicsTextItem* hpText;
    string team;
    bool placed = false;

protected:
    int healthPoints;
};


#endif // CUSTOMSPRITE_H
