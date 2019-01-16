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

Soldier::Soldier(string team, QGraphicsItem *parent): QObject(), CustomSprite(team, parent){
    // Set the graphic
    if(this->team == "red")
        setPixmap(QPixmap(":/images/redSoldierLow.png"));
    else
        setPixmap(QPixmap(":/images/blueSoldier.png"));
    viewRange = 200;
    speed = 2;
    reloadTime = 100;
}

void Soldier::start()
{
    placed = true;
    game->scene->addItem(hpText);
    updateUI();
    time = reloadTime;
    timer = new QBasicTimer();
    timer->start(10, this);
    destination = this->pos();
}

bool Soldier::canBePlaced()
{
    // Can only be spawned near our camp
    if(this->pos().x() > 190){
        setPixmap(QPixmap(":/images/redSoldierLow.png"));
        return false;
    }
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size()>1){
        setPixmap(QPixmap(":/images/redSoldierLow.png"));
        return false;
    }
    setPixmap(QPixmap(":/images/redSoldier.png"));
    return true;
}

void Soldier::destroyed()
{
    timer->stop();
    game->scene->removeItem(hpText);
    game->scene->removeItem(this);
}

void Soldier::setDestination(QPointF pos) {
    setDestination(pos.x(), pos.y());
}

void Soldier::setDestination(int x, int y) {
    destination = QPoint(x ,y);
}

CustomSprite* Soldier::checkFOV()
{
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine) || typeid(*(item)) == typeid(Soldier) || typeid(*(item)) == typeid(Citadel)) {
            CustomSprite* sprite = dynamic_cast<CustomSprite*>(item);
            if(sprite->placed && !sprite->isInOurTeam(this->team) && QVector2D(sprite->pos().x()-this->pos().x(), sprite->pos().y()-this->pos().y()).length() < viewRange){
                return sprite;
            }
        }
    }
    return nullptr;
}

void Soldier::fixCollision()
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
                    return;
                }
            }
        }
    }
}

void Soldier::timerEvent(QTimerEvent *e)
{
    if(game->gameOver)
        timer->stop();
    else{
        time++;

        CustomSprite* target = checkFOV();
        // Shoot
        if(target && time > reloadTime){
            new Bullet(this->team, QPoint(this->pos().x()+this->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()/2), target);
            time = 0;
        }
        // Move
        move();
    }
}

void Soldier::move()
{
    fixCollision();
    QVector2D distToTarget = QVector2D(destination.x()-this->pos().x(), destination.y()-this->pos().y());
    if ((this->team == "red" && distToTarget.length() > 32) || (this->team == "blue" && distToTarget.length()> 100)) {
        distToTarget.normalize();
        this->setPos(this->pos().x() + distToTarget.x()*speed, this->pos().y() + distToTarget.y()*speed);
    }
    updateUI();
}
