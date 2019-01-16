#ifndef NPC_H
#define NPC_H

using namespace std;

#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QGraphicsItem>

#include "minespot.h"
#include "soldier.h"

class NPC: public QObject
{
    Q_OBJECT
public:
    NPC();
    void start();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    int amountOfMines();
    QList<Soldier*> getSoldiers();
    void buildMine();
    void spawnSoldier();
    MineSpot* getNearestMineSpot();
    CustomSprite* getNearestTarget();
    float distanceBetween(QPointF a, QPointF b);
    QPointF computeArmyPosition();

    string team;
    QPointF pos;
};

#endif // NPC_H
