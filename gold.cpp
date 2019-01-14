#include "Gold.h"
#include "Game.h"

#include <QFont>

extern Game* game;

Gold::Gold(QGraphicsItem *parent): QGraphicsTextItem(parent){
    gold = 0;

    // Draw the icon
    icon = new QGraphicsPixmapItem();
    icon->setPixmap(QPixmap(":/images/goldIngots.png"));
    icon->setPos(game->width() - icon->boundingRect().width() - 5, 5);
    game->scene->addItem(icon);
    // Draw the text
    setPlainText(QString::number(gold));
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    setPos(game->width() - this->boundingRect().width() - icon->boundingRect().width() - 5, 5);
}

void Gold::increase(){
    gold++;
    setPlainText(QString::number(gold));
    setPos(game->width() - this->boundingRect().width() - icon->boundingRect().width() - 5, 5);
}

int Gold::getGold(){
    return gold;
}
