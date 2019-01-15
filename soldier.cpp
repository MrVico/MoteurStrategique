#include "soldier.h"
#include "game.h"
#include "customsprite.h"
#include "bullet.h"
#include "citadel.h"

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
    placed = true;
    game->scene->addItem(hpText);
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

void Soldier::destroyed()
{

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
        if(typeid(*(item)) == typeid(Mine) || typeid(*(item)) == typeid(Soldier) || typeid(*(item)) == typeid(Citadel)) {
            CustomSprite* sprite = dynamic_cast<CustomSprite*>(item);
            if(!sprite->isInOurTeam(this->team) && QVector2D(sprite->pos().x()-this->pos().x(), sprite->pos().y()-this->pos().y()).length() < viewRange){
                return sprite;
            }
        }
    }
    return nullptr;
}

bool Soldier::isCollidingWithSoldier()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size() > 1){
        for(int i=0; i<colliders.size(); i++){
            if(typeid(*(colliders[i])) == typeid(Soldier)){
                Soldier* soldier = dynamic_cast<Soldier*>(colliders[i]);
                if(soldier->placed){
                    QVector2D direction = QVector2D(soldier->pos().x()-this->pos().x(), soldier->pos().y()-this->pos().y());
                    direction.normalize();
                    this->setPos(this->pos().x()-direction.x()*speed, this->pos().y()-direction.y()*speed);
                    return true;
                }
            }
        }
    }
    return false;
}

void Soldier::timerEvent(QTimerEvent *e)
{
    time++;
    CustomSprite* target = checkFOV();
    // Shoot
    if(target && time > reloadTime){
        Bullet* bullet = new Bullet(this->team, QPoint(this->pos().x()+this->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()/2), target);
        time = 0;
    }
    // Move
    else if(!isCollidingWithSoldier()){
        QVector2D distToTarget = QVector2D(destination.x()-this->pos().x(), destination.y()-this->pos().y());
        if (distToTarget.length() > 32) {
            distToTarget.normalize();
            this->setPos(this->pos().x() + distToTarget.x()*speed, this->pos().y() + distToTarget.y()*speed);
        }
        updateUI();
    }
}
