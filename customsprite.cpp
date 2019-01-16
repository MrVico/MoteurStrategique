#include "customsprite.h"
#include "game.h"

extern Game* game;

CustomSprite::CustomSprite(string team, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->team = team;

    // Sets up the health system
    healthPoints = 10;
    hpText = new QGraphicsTextItem();
    hpText->setFont(QFont("times", 10));
    updateUI();
}

// Called when shot by a soldier
void CustomSprite::takeHit()
{
    healthPoints--;
    // If we have no more HP we destroy ourselves
    if(healthPoints <= 0)
        this->destroyed();
    // We update the UI
    updateUI();
}

// Returns true if of the same team else otherwise
bool CustomSprite::isInOurTeam(string team)
{
    return this->team == team;
}

// Updates the value and position of the text HP UI
void CustomSprite::updateUI()
{
    hpText->setPlainText(QString::number(healthPoints));
    hpText->setPos(this->pos().x()+this->boundingRect().width()/2-hpText->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()-5);
}
