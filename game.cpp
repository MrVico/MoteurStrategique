#include "game.h"
#include "button.h"
#include "buildmineicon.h"
#include "spawnsoldierbutton.h"
#include "soldier.h"
#include "minespot.h"
#include "citadel.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QPixmap>
#include <QLinearGradient>
#include <QPainter>

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

    scene->setBackgroundBrush(QBrush(QColor::fromRgb(144, 233, 147)));

    // Gradient spawnRegions
    QGraphicsRectItem* spawnRegionsRedSide = new QGraphicsRectItem();
    spawnRegionsRedSide->setRect(0, 0, 190, this->height());
    spawnRegionsRedSide->setPen(Qt::NoPen);
    QLinearGradient gradient1(0, 0, 190, 0);
    gradient1.setColorAt(0, QColor::fromRgb(27, 241, 34));
    gradient1.setColorAt(1, QColor::fromRgb(144, 233, 147));
    spawnRegionsRedSide->setBrush(QBrush(gradient1));
    scene->addItem(spawnRegionsRedSide);

    QGraphicsRectItem* spawnRegionsBlueSide = new QGraphicsRectItem();
    spawnRegionsBlueSide->setRect(this->width()-190, 0, this->width(), this->height());
    spawnRegionsBlueSide->setPen(Qt::NoPen);
    QLinearGradient gradient2(this->width(), 0, this->width()-190, 0);
    gradient2.setColorAt(0, QColor::fromRgb(27, 241, 34));
    gradient2.setColorAt(1, QColor::fromRgb(144, 233, 147));
    spawnRegionsBlueSide->setBrush(QBrush(gradient2));
    scene->addItem(spawnRegionsBlueSide);

    // Dotted lines
    QPen pen(Qt::PenStyle::DashDotLine);
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0, 80));
    QVector<qreal> dashes;
    dashes << 4 << 12 ;
    pen.setDashPattern(dashes);

    QGraphicsRectItem* lineRedSide = new QGraphicsRectItem();
    lineRedSide->setPen(pen);
    lineRedSide->setRect(190, 0, 0, this->height());
    scene->addItem(lineRedSide);

    QGraphicsRectItem* lineBlueSide = new QGraphicsRectItem();
    lineBlueSide->setPen(pen);
    lineBlueSide->setRect(this->width()-190, 0, 0, this->height());
    scene->addItem(lineBlueSide);

    // Spawn mine spots
    spawnGoldMineSpots();

    // Mine icon
    BuildMineIcon* mineIcon = new BuildMineIcon();

    // Soldier icon
    SpawnSoldierButton* soldierIcon = new SpawnSoldierButton();

    // Wallets
    redWallet = new Wallet("red");
    scene->addItem(redWallet);
    blueWallet = new Wallet("blue");
    scene->addItem(blueWallet);

    // Spawn the two citadels
    Citadel* redCitadel = new Citadel(QPoint(5, this->height()/2-spriteSize*2), "red");
    scene->addItem(redCitadel);
    Citadel* blueCitadel = new Citadel(QPoint(this->width()-spriteSize*2-5, this->height()/2-spriteSize*2), "blue");
    scene->addItem(blueCitadel);
}

void Game::spawnGoldMineSpots()
{
    Mine* redMine = new Mine("red", 0, true);
    redMine->setPos(QPoint(200, 100));
    redMine->updateUI();
    scene->addItem(redMine);
    redMine->start();

    //new MineSpot(QPoint(200, 100));
    new MineSpot(QPoint(300, 200));
    new MineSpot(QPoint(200, 400));
    new MineSpot(QPoint(400, 480));
    new MineSpot(QPoint(150, 600));

    Mine* blueMine = new Mine("blue", 0, true);
    blueMine->setPos(QPoint(this->width()-spriteSize-200, this->height()-spriteSize-100));
    blueMine->updateUI();
    scene->addItem(blueMine);
    blueMine->start();

    new MineSpot(QPoint(this->width()-spriteSize-300, this->height()-spriteSize-200));
    new MineSpot(QPoint(this->width()-spriteSize-200, this->height()-spriteSize-400));
    new MineSpot(QPoint(this->width()-spriteSize-400, this->height()-spriteSize-480));
    new MineSpot(QPoint(this->width()-spriteSize-150, this->height()-spriteSize-600));
}

Wallet *Game::getMyWallet(string team)
{
    if(team == "red")
        return redWallet;
    return blueWallet;
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
        if(typeid(*(sprite)) == typeid(Soldier)){
            redWallet->add(soldierPrice);
        }
        else if(typeid(*(sprite)) == typeid(Mine)){
            Mine* mine = dynamic_cast<Mine*>(sprite);
            redWallet->add(mine->price);
        }
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
