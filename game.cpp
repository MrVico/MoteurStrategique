#include "Game.h"
#include "Button.h"
#include "BuildMineIcon.h"
#include "SpawnSoldierButton.h"
#include "Soldier.h"

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
    sprite = nullptr;
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

void Game::displayGame()
{
    // Clear the screen
    scene->clear();

    // Mine icon
    BuildMineIcon* mineIcon = new BuildMineIcon();
    scene->addItem(mineIcon);

    // Soldier icon
    SpawnSoldierButton* soldierIcon = new SpawnSoldierButton();
    scene->addItem(soldierIcon);

    // Wallet
    wallet = new Wallet();
    scene->addItem(wallet);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(sprite){
        sprite->setPos(event->pos().x() - sprite->boundingRect().width()/2, event->pos().y() - sprite->boundingRect().height()/2);
        sprite->checkForCollisions();
    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // If we left click with a sprite and there aren't any collisions we build it
    if(event->button() == Qt::LeftButton && sprite && !sprite->checkForCollisions()){
        sprite->start();
        sprite = nullptr;
    }
    // If we right click with a sprite we remove it, cancel
    else if(event->button() == Qt::RightButton && sprite){
        // We get our money back since we didn't place the item
        if(typeid(*(sprite)) == typeid(Soldier))
            wallet->add(soldierPrice);
        scene->removeItem(sprite);
        sprite = nullptr;
    }
    // Else we delegate to the parent
    else{
        QGraphicsView::mousePressEvent(event);
    }
}
