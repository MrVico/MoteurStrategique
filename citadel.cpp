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

// Unused but inherited
void Citadel::start()
{

}

// Unused but inherited
bool Citadel::canBePlaced()
{
    return false;
}

// Called when the citadel's team lost the game
void Citadel::destroyed()
{
    game->scene->removeItem(hpText);
    // Victory or not
    game->displayEndScreen(!(this->team == "red"));
    game->gameOver = true;
}
