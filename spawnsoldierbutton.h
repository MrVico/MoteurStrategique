#ifndef SPAWNSOLDIERBUTTON_H
#define SPAWNSOLDIERBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class SpawnSoldierButton: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SpawnSoldierButton(QGraphicsItem* parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QGraphicsTextItem* text;
    int offset;
};

#endif // SPAWNSOLDIERBUTTON_H
