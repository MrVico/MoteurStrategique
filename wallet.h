#ifndef WALLET_H
#define WALLET_H

using namespace std;

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class Wallet: public QGraphicsTextItem{
public:
    Wallet(string side, QGraphicsItem * parent=0);
    void add(int amount);
    void spend(int amount);
    int getGold();

private:
    void updateUI();

    QGraphicsPixmapItem* icon;
    string side;
    int gold;
};

#endif // WALLET_H
