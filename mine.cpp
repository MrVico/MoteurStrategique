#include "mine.h"
#include "game.h"
#include "customsprite.h"
#include "minespot.h";

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Mine::Mine(QString team, QGraphicsItem *parent):QObject(), CustomSprite(team, parent){
    if(this->team == QString("red"))
        setPixmap(QPixmap(":/images/miningDisabled.png"));
    else
        setPixmap(QPixmap(":/images/blueMine.png"));
}

// Start mining
void Mine::start()
{
    // We set the position of the mine spot
    setPos(lastMineSpot->pos());
    game->scene->removeItem(lastMineSpot);

    updateUI();
/*
    // And set up the health system
    healthPoints = 10;
    hpText = new QGraphicsTextItem();
    hpText->setFont(QFont("times", 10));
    hpText->setPlainText(QString::number(healthPoints));
    hpText->setPos(this->pos().x()+this->boundingRect().width()/2-hpText->boundingRect().width()/2, this->pos().y()+this->boundingRect().height()-8);
    game->scene->addItem(hpText);
*/
    QBasicTimer* timer = new QBasicTimer();
    timer->start(1000, this);
}

bool Mine::canBePlaced()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size() > 0){
        for(int i=0; i<colliders.size(); i++){
            if(typeid(*(colliders[i])) == typeid(MineSpot)){
                if(this->team == QString("red"))
                    setPixmap(QPixmap(":/images/redMine.png"));
                else
                    setPixmap(QPixmap(":/images/blueMine.png"));
                // We store the last mine so we can use it if needed
                lastMineSpot = dynamic_cast<MineSpot*>(colliders[i]);
                return true;
            }
        }
    }
    setPixmap(QPixmap(":/images/miningDisabled.png"));
    return false;
}

void Mine::timerEvent(QTimerEvent *e)
{
    // Mine gold
    game->wallet->add(1);
}
