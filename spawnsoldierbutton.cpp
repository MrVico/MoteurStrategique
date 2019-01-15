#include "spawnsoldierbutton.h"
#include "game.h"
#include "soldier.h"

#include <QDebug>

// Reference to the game instance
extern Game *game;

SpawnSoldierButton::SpawnSoldierButton(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // Draw the icon
    setPixmap(QPixmap(":/images/soldierIconLow.png"));
    offset = 10;
    setPos(boundingRect().width()+offset, 5);

    // Draw the price text
    text = new QGraphicsTextItem();
    text->setPlainText(QString::number(game->soldierPrice));
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("times", 10));
    text->setPos(boundingRect().width() + offset + 5, boundingRect().height());
    game->scene->addItem(text);

    QBasicTimer* timer = new QBasicTimer();
    timer->start(100, this);
}

void SpawnSoldierButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    // If we have enough gold
    if (game->wallet->getGold() >= game->soldierPrice){
        game->sprite = new Soldier(QString("red"));
        game->sprite->setPos(event->pos().x()+game->sprite->boundingRect().width()+offset - game->sprite->boundingRect().width()/2, event->pos().y() - game->sprite->boundingRect().height()/2);
        game->scene->addItem(game->sprite);

        game->wallet->spend(game->soldierPrice);
    }
}

void SpawnSoldierButton::timerEvent(QTimerEvent *event)
{
    if(game->wallet->getGold() >= game->soldierPrice)
        setPixmap(QPixmap(":/images/soldierIcon.png"));
    else
        setPixmap(QPixmap(":/images/soldierIconLow.png"));
}
