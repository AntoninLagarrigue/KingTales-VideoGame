#ifndef HOLE_H
#define HOLE_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Hole : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Hole(int width, int height, QGraphicsItem * parent = 0);
    ~Hole();
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QRectF boundingRect() const;
private:

   //Draw
   QPixmap * sprite_image_;
   int width_;
   int height_;
};


#endif // HOLE_H
