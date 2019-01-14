#ifndef WALLET_H
#define WALLET_H

#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>

class Wallet: public QGraphicsTextItem{
public:
    Wallet(QGraphicsItem * parent=0);
    void add(int amount);
    void spend(int amount);
    int getGold();

private:
    void updateUI();

    QGraphicsPixmapItem* icon;
    int gold;
};

#endif // WALLET_H
