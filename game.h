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

    QGraphicsScene* scene;
    Wallet* wallet;
    CustomSprite* sprite;
    int soldierPrice = 50;

public slots:
    void displayGame();

private:
    void spawnGoldMineSpots();
    void createMineSpot(QPoint pos);

    int spriteSize;
};

#endif // GAME_H
