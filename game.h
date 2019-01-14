#ifndef GAME_H
#define GAME_H

#include "Mine.h"
#include "Gold.h"

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
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    QGraphicsScene* scene;
    Gold* gold;
    QGraphicsPixmapItem* cursor;
    Mine* build;

public slots:
    void displayGame();
};

#endif // GAME_H
