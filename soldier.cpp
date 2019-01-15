#include "soldier.h"
#include "game.h"
#include "customsprite.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Soldier::Soldier(QGraphicsItem *parent):QObject(), CustomSprite(parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/soldierSprite.png"));
    speed = 2;
}

// Start mining
void Soldier::start()
{
    QBasicTimer* timer = new QBasicTimer();
    timer->start(10, this);
    this->stop();
}

bool Soldier::canBePlaced()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size()>0){
        //setPixmap(QPixmap(":/images/miningDisabled.png"));
        return false;
    }
    //setPixmap(QPixmap(":/images/mining.png"));
    return true;
}

void Soldier::moveTo(int x, int y) {
    target = QPoint(x,y);
}

void Soldier::stop() {
    target = QPoint((int)this->pos().x(),(int)this->pos().y());
}

void Soldier::timerEvent(QTimerEvent *e)
{
    int currentX = this->pos().x();
    int currentY = this->pos().y();
    QVector2D distToTarget = QVector2D(target.x()-currentX, target.y()-currentY);
    if (distToTarget.length() > 5) {
        distToTarget.normalize();
        this->setPos(currentX + distToTarget.x()*speed, currentY + distToTarget.y()*speed);
    } else {
        // Check collison/attack
    }
}
