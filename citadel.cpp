#include "citadel.h"
#include "game.h"

extern Game* game;

Citadel::Citadel(QPoint pos, string team, QGraphicsItem *parent): CustomSprite(team, parent)
{
    if(team == "red")
        setPixmap(QPixmap(":/images/redCitadel.png"));
    else
        setPixmap(QPixmap(":/images/blueCitadel.png"));
    setPos(pos);
    healthPoints = 50;
    placed = true;
    game->scene->addItem(hpText);
    updateUI();
}

void Citadel::start()
{

}

bool Citadel::canBePlaced()
{
    return false;
}

void Citadel::destroyed()
{
    // Victory or not
    game->scene->removeItem(hpText);
    game->displayEndScreen(!(this->team == "red"));
    game->gameOver = true;
}
