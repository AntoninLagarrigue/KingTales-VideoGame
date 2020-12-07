#include "Platform.h"
#include <QPainter>

Platform::Platform(QGraphicsItem * parent) : QGraphicsItem(parent)
{
    sprite_image_ = new QPixmap(":/sprites/platform.png");

}

Platform::~Platform()
{

}

void Platform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(0, 0, 169, 112));

    Q_UNUSED(option);
    Q_UNUSED(widget);

}
