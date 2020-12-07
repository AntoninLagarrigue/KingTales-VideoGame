#ifndef GROUND_H
#define GROUND_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>

class Ground : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Ground(QGraphicsItem * parent = 0);
    ~Ground();
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    QRectF boundingRect() const { return QRectF(15, 50, 100, 128); }
private:

   //Draw
   QPixmap * sprite_image_;
};

#endif // GROUND_H
