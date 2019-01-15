#include "spawnsoldierbutton.h"
#include "game.h"
#include "soldier.h"

#include <QDebug>

// Reference to the game instance
extern Game *game;

SpawnSoldierButton::SpawnSoldierButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    // Draw the icon
    setPixmap(QPixmap(":/images/soldierIcon.png"));
    offset = 5;
    setPos(boundingRect().width()+offset, offset);

    // Draw the price text
    text = new QGraphicsTextItem();
    text->setPlainText(QString::number(game->soldierPrice));
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("times", 10));
    text->setPos(boundingRect().width()*2 - text->boundingRect().width(), boundingRect().height());
    game->scene->addItem(text);
}

void SpawnSoldierButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //qDebug() << "SOLDIER PRESSED " << event->pos();
    // If we have enough gold
    if (game->wallet->getGold() >= game->soldierPrice){
        game->sprite = new Soldier(QString("red"));
        game->sprite->setPos(event->pos().x()+game->sprite->boundingRect().width()+offset - game->sprite->boundingRect().width()/2, event->pos().y() - game->sprite->boundingRect().height()/2);
        game->scene->addItem(game->sprite);

        game->wallet->spend(game->soldierPrice);
    }
}
