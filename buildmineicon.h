#ifndef BUILDMINEICON_H
#define BUILDMINEICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QBasicTimer>
#include <QTimerEvent>

class BuildMineIcon: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    BuildMineIcon(QGraphicsItem* parent=0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void setMinePrice();

    QGraphicsTextItem* text;
    int price;
};

#endif // BUILDMINEICON_H
