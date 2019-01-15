#ifndef GAME_H
#define GAME_H

#include "mine.h"
#include "wallet.h"
#include "customsprite.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);

    void displayMainMenu();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    Wallet* getMyWallet(string team);

    QGraphicsScene* scene;
    CustomSprite* sprite;
    int soldierPrice = 50;
    int spriteSize;

public slots:
    void displayGame();

private:
    void spawnGoldMineSpots();
    Wallet* redWallet;
    Wallet* blueWallet;

};

#endif // GAME_H
