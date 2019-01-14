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
    setFixedSize(1768, 992);
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1768, 992);
    setScene(scene);
    cursor = nullptr;
    build = nullptr;
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

void Game::setCursor(QString filename)
{
    // If the cursor is already set (not nullptr) we delete it
    if(cursor){
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(cursor){
        cursor->setPos(event->pos());
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    if(build){
        scene->addItem(build);
        build->setPos(event->pos());
        build->startMiningGold();
        cursor = nullptr;
        build = nullptr;
    }
    else{
        /*
         * We pass the event to the parent
         * so it can be called on any other object
         * */
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
