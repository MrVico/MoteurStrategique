#include "mine.h"
#include "game.h"
#include "customsprite.h"
#include "minespot.h";

#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QList>

extern Game* game;

Mine::Mine(string team, int price, bool initialMine, QGraphicsItem *parent):QObject(), CustomSprite(team, parent){
    if(this->team == "red")
        if(initialMine)
            setPixmap(QPixmap(":/images/redMine.png"));
        else
            setPixmap(QPixmap(":/images/redMineLow.png"));
    else
        setPixmap(QPixmap(":/images/blueMine.png"));
    this->price = price;
    this->initialMine = initialMine;
}

// Start mining
void Mine::start()
{
    placed = true;
    game->scene->addItem(hpText);
    // We set the position of the mine spot
    if(!this->initialMine){
        setPos(lastMineSpot->pos());
        game->removeMineSpot(lastMineSpot);
        game->scene->removeItem(lastMineSpot);
    }

    updateUI();

    timer = new QBasicTimer();
    timer->start(300, this);
}

// Returns if a mine can be placed, in other words if there's a mine spot nearby
bool Mine::canBePlaced()
{
    QList<QGraphicsItem*> colliders = collidingItems();
    if(colliders.size() > 0){
        for(int i=0; i<colliders.size(); i++){
            if(typeid(*(colliders[i])) == typeid(MineSpot)){
                if(this->team == "red")
                    setPixmap(QPixmap(":/images/redMine.png"));
                else
                    setPixmap(QPixmap(":/images/blueMine.png"));
                // We store the last mine so we can use it if needed
                lastMineSpot = dynamic_cast<MineSpot*>(colliders[i]);
                return true;
            }
        }
    }
    setPixmap(QPixmap(":/images/redMineLow.png"));
    return false;
}

// Called when the mine got destroyed by the enemy
void Mine::destroyed()
{
    // We replace the mine with a mine spot on which anyone can place a mine
    game->addMineSpot(new MineSpot(QPoint(this->pos().x(), this->pos().y())));
    game->scene->removeItem(this->hpText);
    game->scene->removeItem(this);
    timer->stop();
}

// Called over and over to mine gold
void Mine::timerEvent(QTimerEvent *e)
{
    if(!game->gameOver)
        game->getMyWallet(this->team)->add(1);
    else
        timer->stop();
}
