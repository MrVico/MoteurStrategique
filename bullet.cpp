#include "bullet.h"
#include "game.h"
#include "customsprite.h"

#include <QDebug>

extern Game* game;

Bullet::Bullet(QString team, QPoint pos, CustomSprite* target, QGraphicsItem *parent):QObject(), CustomSprite(team, parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));
    setPos(pos);
    this->target = target;
    this->speed = 4;

    QBasicTimer* timer = new QBasicTimer();
    timer->start(10, this);

    game->scene->addItem(this);
}

void Bullet::start()
{

}

bool Bullet::canBePlaced()
{
    return false;
}

void Bullet::destroyed()
{

}

void Bullet::timerEvent(QTimerEvent *e)
{
    //qDebug() << "destination: " << target->pos();
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size() > 0){
        for(int i=0; i<colliders.size(); i++){
            CustomSprite* sprite = dynamic_cast<CustomSprite*>(colliders[i]);
            if(sprite == target){
                sprite->takeHit();
                game->scene->removeItem(this);
            }
        }
    }

    int currentX = this->pos().x();
    int currentY = this->pos().y();
    QVector2D direction = QVector2D(target->pos().x()-currentX+game->spriteSize/2, target->pos().y()-currentY+game->spriteSize/2);
    direction.normalize();
    this->setPos(currentX + direction.x()*speed, currentY + direction.y()*speed);
}
