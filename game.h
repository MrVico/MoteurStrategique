#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);

    void displayMainMenu();

    QGraphicsScene* scene;

public slots:
    void startGame();
};

#endif // GAME_H
