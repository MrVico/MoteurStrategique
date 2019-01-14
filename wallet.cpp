#include "Wallet.h"
#include "Game.h"

#include <QFont>

extern Game* game;

Wallet::Wallet(QGraphicsItem *parent): QGraphicsTextItem(parent)
{
    gold = 0;

    // Draw the icon
    icon = new QGraphicsPixmapItem();
    icon->setPixmap(QPixmap(":/images/goldIngots.png"));
    icon->setPos(game->width() - icon->boundingRect().width() - 5, 5);
    game->scene->addItem(icon);

    // Draw the text
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    updateUI();
}

void Wallet::add(int amount)
{
    gold += amount;
    updateUI();
}

void Wallet::spend(int amount)
{
    gold -= amount;
    updateUI();
}

int Wallet::getGold(){
    return gold;
}

void Wallet::updateUI()
{
    setPlainText(QString::number(gold));
    setPos(game->width() - this->boundingRect().width() - icon->boundingRect().width() - 5, 5);
}
