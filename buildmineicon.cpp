#include "buildmineicon.h"
#include "game.h"

#include <QDebug>

// Reference to the game instance
extern Game *game;

BuildMineIcon::BuildMineIcon(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mineIcon.png"));
    setPos(10, 5);
}

void BuildMineIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!game->sprite){
        game->sprite = new Mine(QString("red"));
        game->sprite->setPos(event->pos().x() - game->sprite->boundingRect().width()/2, event->pos().y() - game->sprite->boundingRect().height()/2);
        game->scene->addItem(game->sprite);
    }
}

void BuildMineIcon::timerEvent(QTimerEvent *event)
{

}
