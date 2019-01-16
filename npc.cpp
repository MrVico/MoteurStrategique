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

    if(getSoldiers().length() >= 3){
        foreach(Soldier* soldier, getSoldiers()){
            soldier->setDestination(getNearestTarget()->pos());
        }
    }
}

void NPC::buildMine()
{
    game->getMyWallet(team)->spend(game->minePrice*amountOfMines());

    Mine* mine = new Mine(team, game->minePrice*amountOfMines(), true);
    MineSpot* mineSpot = getNearestMineSpot();
    mine->setPos(mineSpot->pos());
    game->removeMineSpot(mineSpot);
    game->scene->removeItem(mineSpot);
    game->scene->addItem(mine);
    mine->start();
}

void NPC::spawnSoldier()
{
    Soldier* soldier = new Soldier(team);
    soldier->setPos(game->width()-game->spriteSize*3, game->height()/2-soldier->boundingRect().height()/2 + rand()%10);
    game->scene->addItem(soldier);
    soldier->start();

    game->getMyWallet(team)->spend(game->soldierPrice);
}

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

CustomSprite *NPC::getNearestTarget()
{
    QList<CustomSprite*> possibleTargets;
    foreach (QGraphicsItem* item, game->scene->items()) {
        if(typeid(*(item)) == typeid(Mine) || typeid(*(item)) == typeid(Soldier) || typeid(*(item)) == typeid(Citadel)) {
            CustomSprite* sprite = dynamic_cast<CustomSprite*>(item);
            if(sprite->placed && !sprite->isInOurTeam(team)){
                possibleTargets.append(sprite);
            }
        }
    }

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

float NPC::distanceBetween(QPointF a, QPointF b)
{
    return sqrt(pow((a.x()-b.x()), 2) + pow((a.y()-b.y()), 2));
}

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

void NPC::start()
{
    QBasicTimer* timer = new QBasicTimer();
    timer->start(10, this);
}

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
