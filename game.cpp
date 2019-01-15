#include "game.h"
#include "button.h"
#include "buildmineicon.h"
#include "spawnsoldierbutton.h"
#include "soldier.h"
#include "minespot.h"
#include "citadel.h"

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

    spriteSize = 32;
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

    // Spawn mine spots
    spawnGoldMineSpots();

    // Spawn the two citadels
    Citadel* redCitadel = new Citadel(QPoint(5, this->height()/2-spriteSize*2), QString("red"));
    scene->addItem(redCitadel);
    Citadel* blueCitadel = new Citadel(QPoint(this->width()-spriteSize*2-5, this->height()/2-spriteSize*2), QString("blue"));
    scene->addItem(blueCitadel);
}

void Game::spawnGoldMineSpots()
{
    createMineSpot(QPoint(200, 100));
    createMineSpot(QPoint(300, 200));
    createMineSpot(QPoint(200, 400));
    createMineSpot(QPoint(400, 480));
    createMineSpot(QPoint(150, 600));


    Mine* mine = new Mine(QString("blue"));
    mine->setPos(QPoint(this->width()-spriteSize-200, this->height()-spriteSize-100));
    mine->updateUI();
    scene->addItem(mine);
    //createMineSpot(QPoint(this->width()-spriteSize-200, this->height()-spriteSize-100));
    createMineSpot(QPoint(this->width()-spriteSize-300, this->height()-spriteSize-200));
    createMineSpot(QPoint(this->width()-spriteSize-200, this->height()-spriteSize-400));
    createMineSpot(QPoint(this->width()-spriteSize-400, this->height()-spriteSize-480));
    createMineSpot(QPoint(this->width()-spriteSize-150, this->height()-spriteSize-600));
}

void Game::createMineSpot(QPoint pos)
{
    MineSpot* spot = new MineSpot(pos);
    scene->addItem(spot);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(sprite){
        sprite->setPos(event->pos().x() - sprite->boundingRect().width()/2, event->pos().y() - sprite->boundingRect().height()/2);
        sprite->canBePlaced();
    }
    else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void Game::mousePressEvent(QMouseEvent *event)
{
    // If we left click with a sprite and the sprite can be placed we do so
    if(event->button() == Qt::LeftButton && sprite && sprite->canBePlaced()){
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
    else if(event->button() == Qt::RightButton){
       foreach (QGraphicsItem* item, scene->items()) {
           if(typeid(*(item)) == typeid(Soldier)) {
               Soldier* itemSprite = dynamic_cast<Soldier*>(item);
               itemSprite->moveTo(event->pos().x() - itemSprite->boundingRect().width()/2, event->pos().y() - itemSprite->boundingRect().height()/2);
           }
       }
   }
    // Else we delegate to the parent
    else{
        QGraphicsView::mousePressEvent(event);
    }
}
