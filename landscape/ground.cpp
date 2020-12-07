#include "ground.h"

Ground::Ground(QGraphicsItem * parent) : QGraphicsItem(parent)
{
     sprite_image_ = new QPixmap(":/sprites/mordor.png");
     setFlag(QGraphicsItem::ItemIsFocusable);
     setFlag(ItemClipsToShape);
     setFocus();

}
Ground::~Ground()
{

}
void Ground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(
                boundingRect(),
                *sprite_image_,
                QRectF(100, 10, 100, 128));
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
