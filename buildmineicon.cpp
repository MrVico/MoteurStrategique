#include "buildmineicon.h"
#include "game.h"

#include <QDebug>

// Reference to the game instance
extern Game *game;

BuildMineIcon::BuildMineIcon(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/mineIcon.png"));
    setPos(game->spriteSize*2, 5);
    game->scene->addItem(this);

    setMinePrice();

    // Draw the price text
    text = new QGraphicsTextItem();
    text->setPlainText(QString::number(price));
    text->setDefaultTextColor(Qt::red);
    text->setFont(QFont("times", 10));
    text->setPos(this->pos().x()+this->boundingRect().width()/2-text->boundingRect().width()/2, boundingRect().height());
    game->scene->addItem(text);

    QBasicTimer* timer = new QBasicTimer();
    timer->start(100, this);
}

void BuildMineIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if (!game->sprite){
    if (game->getMyWallet("red")->getGold() >= price){
        game->sprite = new Mine("red", price);
        game->sprite->setPos(event->pos().x() + this->pos().x()  - game->spriteSize/2, event->pos().y() - game->sprite->boundingRect().height()/2);
        game->scene->addItem(game->sprite);

        game->getMyWallet("red")->spend(price);
    }
}

void BuildMineIcon::timerEvent(QTimerEvent *event)
{
    setMinePrice();
    if(game->getMyWallet("red")->getGold() >= price)
        setPixmap(QPixmap(":/images/mineIcon.png"));
    else
        setPixmap(QPixmap(":/images/mineIconLow.png"));
    text->setPlainText(QString::number(price));
    text->setPos(this->pos().x()+this->boundingRect().width()/2-text->boundingRect().width()/2, boundingRect().height());
}

// number of mines placed by the player
void BuildMineIcon::setMinePrice()
{
    int counter = 0;
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine)) {
            Mine* mine = dynamic_cast<Mine*>(item);
            if(mine->isInOurTeam("red")){
                counter++;
            }
        }
    }
    price = game->minePrice*counter;
}
