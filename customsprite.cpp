#include "customsprite.h"
#include "game.h"

extern Game* game;

CustomSprite::CustomSprite(QString team, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    this->team = team;

    // And set up the health system
    healthPoints = 10;
    hpText = new QGraphicsTextItem();
    hpText->setFont(QFont("times", 10));
    updateUI();
    game->scene->addItem(hpText);
}

void CustomSprite::takeHit()
{
    healthPoints--;
    updateUI();
}

bool CustomSprite::isInOurTeam(QString team)
{
    return this->team == team;
}

void CustomSprite::updateUI()
{
    hpText->setPlainText(QString::number(healthPoints));
    hpText->setPos(this->pos().x()+this->boundingRect().width()/2-hpText->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()-8);
}
