#include "bullet.h"
#include "game.h"
#include "customsprite.h"

#include <QDebug>

extern Game* game;

Bullet::Bullet(string team, QPoint pos, CustomSprite* target, QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));
    setPos(pos);
    this->team = team;
    this->target = target;
    this->speed = 4;

    timer = new QBasicTimer();
    timer->start(10, this);

    game->scene->addItem(this);
}

void Bullet::timerEvent(QTimerEvent *e)
{
    if(!game->scene->items().contains(target)){
        timer->stop();
        game->scene->removeItem(this);
    }
    else{
        QList<QGraphicsItem*> colliders = collidingItems();
        if(colliders.size() > 0){
            for(int i=0; i<colliders.size(); i++){
                CustomSprite* sprite = dynamic_cast<CustomSprite*>(colliders[i]);
                if(sprite == target){
                    sprite->takeHit();
                    timer->stop();
                    game->scene->removeItem(this);
                }
            }
        }

        int currentX = this->pos().x();
        int currentY = this->pos().y();
        QVector2D direction = QVector2D(target->pos().x()-currentX+target->boundingRect().width()/2, target->pos().y()-currentY+target->boundingRect().height()/2);
        direction.normalize();
        this->setPos(currentX + direction.x()*speed, currentY + direction.y()*speed);
    }
}
