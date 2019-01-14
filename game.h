#ifndef GAME_H
#define GAME_H

#include "Mine.h"
#include "Wallet.h"
#include "CustomSprite.h"

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
};

#endif // GAME_H
