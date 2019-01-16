#include "wallet.h"
#include "game.h"

#include <QFont>

extern Game* game;

Wallet::Wallet(string side, QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    this->gold = 50;
    this->side = side;

    setFont(QFont("times", 14));

    // Draw the icon
    icon = new QGraphicsPixmapItem();
    icon->setPixmap(QPixmap(":/images/goldIngots.png"));
    if(side == "red"){
        setDefaultTextColor(Qt::red);
        icon->setPos(5, 0);
    }
    else if(side == "blue"){
        setDefaultTextColor(Qt::blue);
        icon->setPos(game->width() - icon->boundingRect().width() - 5, 0);
    }
    game->scene->addItem(icon);

    updateUI();
}

// Adds amount to the gold reserve
void Wallet::add(int amount)
{
    gold += amount;
    updateUI();
}

// Takes amount from the gold reserve
void Wallet::spend(int amount)
{
    gold -= amount;
    updateUI();
}

// Returns the amount of gold in reserve
int Wallet::getGold(){
    return gold;
}

// Updates the UI gold amount
void Wallet::updateUI()
{
    setPlainText(QString::number(gold));
    if(side == "blue")
        setPos(game->width() - this->boundingRect().width() - icon->boundingRect().width() - 5, 0);
    else if(side == "red")
        setPos(icon->boundingRect().width()*2/3, icon->boundingRect().height()/2);
}
