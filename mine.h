#ifndef MINE_H
#define MINE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class Mine: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Mine(QGraphicsItem * parent=0);
    void startMiningGold();

protected:
    void timerEvent(QTimerEvent *e) override;
};

#endif // MINE_H
