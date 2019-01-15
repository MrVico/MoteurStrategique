#include "soldier.h"
#include "game.h"
#include "customsprite.h"
#include "bullet.h"

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Soldier::Soldier(QString team, QGraphicsItem *parent):QObject(), CustomSprite(team, parent){
    // Set the graphic
    setPixmap(QPixmap(":/images/soldierSprite.png"));
    viewRange = 200;
    speed = 2;
    reloadTime = 300;
}

// Start mining
void Soldier::start()
{
    updateUI();
    time = reloadTime;
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
    destination = QPoint(x,y);
}

void Soldier::stop() {
    destination = QPoint((int)this->pos().x(),(int)this->pos().y());
}

CustomSprite* Soldier::checkFOV()
{
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine)) {
            Mine* mine = dynamic_cast<Mine*>(item);
            if(!mine->isInOurTeam(this->team) && QVector2D(mine->pos().x()-this->pos().x(), mine->pos().y()-this->pos().y()).length() < viewRange){
                return mine;
            }
        }
    }
    return nullptr;
}

void Soldier::timerEvent(QTimerEvent *e)
{
    time++;
    CustomSprite* target = checkFOV();
    if(target && time > reloadTime){
        Bullet* bullet = new Bullet(this->team, QPoint(this->pos().x()+this->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()/2), target);
        time = 0;
    }
    else{
        int currentX = this->pos().x();
        int currentY = this->pos().y();
        QVector2D distToTarget = QVector2D(destination.x()-currentX, destination.y()-currentY);
        if (distToTarget.length() > 5) {
            distToTarget.normalize();
            this->setPos(currentX + distToTarget.x()*speed, currentY + distToTarget.y()*speed);
        }
        updateUI();
    }
}
