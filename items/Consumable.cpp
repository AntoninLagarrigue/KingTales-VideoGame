#include "Consumable.h"
#include <QPainter>
#include <QDebug>


Consumable::Consumable(QGraphicsItem * parent) : QGraphicsItem(parent)
{
}

Consumable::~Consumable()
{

}

void Consumable::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(0, 0, 32, 32));

    Q_UNUSED(option);
    Q_UNUSED(widget);

}
