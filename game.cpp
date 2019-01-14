#include "Game.h"
#include "Button.h"
#include "BuildMineIcon.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QPixmap>

Game::Game(QWidget *parent)
{
    // Remove the scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Resize the game window
    //setFixedSize(1768, 992);
    setFixedSize(1080, 720);
    scene = new QGraphicsScene();
    //scene->setSceneRect(0, 0, 1768, 992);
    scene->setSceneRect(0, 0, 1080, 720);
    setScene(scene);
    mine = nullptr;
    setMouseTracking(true);
}

void Game::displayMainMenu()
{
    // Title
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Moteur Strategique"));
    QFont titleFont("comis sans", 50);
    titleText->setFont(titleFont);
    int xTxtPos = this->width()/2 - titleText->boundingRect().width()/2;
    int yTxtPos = 150;
    titleText->setPos(xTxtPos, yTxtPos);
    scene->addItem(titleText);

    // Play button
    Button* playButton = new Button(QString("Play"));
    int xButtonPos = this->width()/2 - playButton->boundingRect().width()/2;
    int yButtonPos = 275;
    playButton->setPos(xButtonPos, yButtonPos);
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(displayGame()));
    scene->addItem(playButton);

    // Quit button
    Button* quitButton = new Button(QString("Quit"));
    xButtonPos = this->width()/2 - quitButton->boundingRect().width()/2;
    yButtonPos = 350;
    quitButton->setPos(xButtonPos, yButtonPos);
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(mine){
        mine->setPos(event->pos().x() - mine->boundingRect().width()/2, event->pos().y() - mine->boundingRect().height()/2);
        mine->checkForCollisions();
    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // If we left click with a mine and there aren't any collisions we build it
    if(event->button() == Qt::LeftButton && mine && !mine->checkForCollisions()){
        mine->startMiningGold();
        mine = nullptr;
    }
    // If we right click with a mine we remove it, cancel
    else if(event->button() == Qt::RightButton && mine){
        scene->removeItem(mine);
        mine = nullptr;
    }
    // Else we delegate to the parent
    else{
        QGraphicsView::mousePressEvent(event);
    }
}

void Game::displayGame()
{
    // Clear the screen
    scene->clear();

    BuildMineIcon* icon = new BuildMineIcon();
    scene->addItem(icon);

    gold = new Gold();
    scene->addItem(gold);
}
