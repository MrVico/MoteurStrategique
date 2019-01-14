#include "BuildMineIcon.h"
#include "Game.h"

// Reference to the game instance
extern Game *game;

BuildMineIcon::BuildMineIcon(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/m.png"));
    setPos(5, 5);
}

void BuildMineIcon::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (!game->build){
        game->build = new Mine();
        game->setCursor(QString(":/images/mining.png"));
    }
}
