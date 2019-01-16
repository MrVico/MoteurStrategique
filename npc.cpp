#include "npc.h"
#include "game.h"
#include "soldier.h"
#include "math.h"
#include "citadel.h"

#include <QDebug>

extern Game* game;

NPC::NPC(): QObject()
{
    this->team = "blue";
    pos = QPoint(game->width(), game->height()/2-game->spriteSize);
}

// Called over and over
void NPC::timerEvent(QTimerEvent *event)
{
    if(getSoldiers().length() == 0 && game->getMyWallet(team)->getGold() >= game->soldierPrice){
        spawnSoldier();
    }
    else if(getSoldiers().length() == 1 && amountOfMines() == 1 && game->getMyWallet(team)->getGold() >= game->minePrice*amountOfMines() && getNearestMineSpot()){
        buildMine();
    }
    else if(amountOfMines() >= 2 && getSoldiers().length() < 4 && game->getMyWallet(team)->getGold() >= game->soldierPrice){
        spawnSoldier();
    }
    else if(game->getMyWallet(team)->getGold() >= game->minePrice*amountOfMines() && getNearestMineSpot()){
        buildMine();
    }

    // As soon as the NPC has 3 or more soldiers he goes for an attack
    if(getSoldiers().length() >= 3){
        foreach(Soldier* soldier, getSoldiers()){
            // His soldiers always attack the nearest target from their position
            soldier->setDestination(getNearestTarget()->pos());
        }
    }
}

// Purchases, creates and adds a mine for the NPC
void NPC::buildMine()
{
    game->getMyWallet(team)->spend(game->minePrice*amountOfMines());

    Mine* mine = new Mine(team, game->minePrice*amountOfMines(), true);
    MineSpot* mineSpot = getNearestMineSpot();
    mine->setPos(mineSpot->pos());
    // We have to remove the minespot that was previously there
    game->removeMineSpot(mineSpot);
    game->scene->removeItem(mineSpot);
    game->scene->addItem(mine);
    mine->start();
}

// Purchases, creates and adds a soldier for the NPC
void NPC::spawnSoldier()
{
    game->getMyWallet(team)->spend(game->soldierPrice);

    Soldier* soldier = new Soldier(team);
    soldier->setPos(game->width()-game->spriteSize*3, game->height()/2-soldier->boundingRect().height()/2 + rand()%10);
    game->scene->addItem(soldier);
    soldier->start();
}

// Returns the nearest free mine spot from the NPC citadel
MineSpot* NPC::getNearestMineSpot()
{
    if(game->getOpenMineSpots().length() == 0)
        return nullptr;
    MineSpot* nearest = game->getOpenMineSpots()[0];
    foreach(MineSpot* mineSpot, game->getOpenMineSpots()){
        if(distanceBetween(mineSpot->pos(), pos) < distanceBetween(nearest->pos(), pos)){
            nearest = mineSpot;
        }
    }
    return nearest;
}

// Returns the nearest enemy target from the army's position
CustomSprite *NPC::getNearestTarget()
{
    QList<CustomSprite*> possibleTargets;
    // Get all possible enemy targets
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine) || typeid(*(item)) == typeid(Soldier) || typeid(*(item)) == typeid(Citadel)) {
            CustomSprite* sprite = dynamic_cast<CustomSprite*>(item);
            if(sprite->placed && !sprite->isInOurTeam(team)){
                possibleTargets.append(sprite);
            }
        }
    }

    // If there's a target (else the game would be over) we get the nearest one
    if(possibleTargets.length() > 0){
        CustomSprite* nearest = possibleTargets[0];
        foreach(CustomSprite* target, possibleTargets){
            QPointF armyPos = computeArmyPosition();
            if(distanceBetween(target->pos(), armyPos) < distanceBetween(nearest->pos(), armyPos)){
                nearest = target;
            }
        }
        return nearest;
    }
    return nullptr;
}

// Returns the distance between two locations
float NPC::distanceBetween(QPointF a, QPointF b)
{
    return sqrt(pow((a.x()-b.x()), 2) + pow((a.y()-b.y()), 2));
}

// Returns the center position of all the soldiers, of the army
QPointF NPC::computeArmyPosition()
{
    int counter = 0;
    QPointF sumOfPositions = QPointF(0, 0);
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Soldier)) {
            Soldier* soldier = dynamic_cast<Soldier*>(item);
            if(soldier->isInOurTeam(team)){
                sumOfPositions += soldier->pos();
                counter++;
            }
        }
    }
    return sumOfPositions/counter;
}

// Returns the amount of mines the NPC has placed
int NPC::amountOfMines()
{
    int counter = 0;
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine)) {
            Mine* mine = dynamic_cast<Mine*>(item);
            if(mine->isInOurTeam("blue")){
                counter++;
            }
        }
    }
    return counter;
}

// Starts the NPC's life
void NPC::start()
{
    QBasicTimer* timer = new QBasicTimer();
    timer->start(10, this);
}

// Returns the amount of soldiers the NPC has placed
QList<Soldier*> NPC::getSoldiers()
{
    QList<Soldier*> soldiers;
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Soldier)) {
            Soldier* soldier = dynamic_cast<Soldier*>(item);
            if(soldier->isInOurTeam("blue")){
                soldiers.append(soldier);
            }
        }
    }
    return soldiers;
}
