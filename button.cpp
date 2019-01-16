#include "button.h"

#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // Draw the rect
    setRect(0, 0, 200, 50);
    changeColor(Qt::darkCyan);

    // Draw the text inside the button
    text = new QGraphicsTextItem(name, this);
    // Center the text inside the button
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos, yPos);

    // Enable mouse hovering
    setAcceptHoverEvents(true);
}

// When we click the button we emit a signal
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

// When we enter the button area with the mouse
void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // We change the color of the button
    changeColor(Qt::cyan);
}

// When we leave the button area with the mouse
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // We change the color back to its original color
    changeColor(Qt::darkCyan);
}

// Changes the button's color
void Button::changeColor(Qt::GlobalColor color)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}
