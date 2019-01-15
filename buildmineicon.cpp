#include "buildmineicon.h"
#include "game.h"

#include <QDebug>

// Reference to the game instance
extern Game *game;

BuildMineIcon::BuildMineIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/m.png"));
    offset = 5;
    setPos(offset, offset);
}

void BuildMineIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "MINE PRESSED " << event->pos();
    if (!game->sprite){
        game->sprite = new Mine();
        game->sprite->setPos(event->pos().x() - game->sprite->boundingRect().width()/2, event->pos().y() - game->sprite->boundingRect().height()/2);
        game->scene->addItem(game->sprite);
    }
}
