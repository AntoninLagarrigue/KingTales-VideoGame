#ifndef CONSUMABLE_H
#define CONSUMABLE_H


#include <QGraphicsItem>
#include <QPixmap>

class Consumable : public QGraphicsItem {

public :
    Consumable(QGraphicsItem * parent = 0);
    ~Consumable();

   // Draw
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
  // void nextFrame();

   // Getters & Setters
   QRectF boundingRect() const { return QRectF(0, 0, 32, 32); }

protected :

   QPixmap * sprite_image_;

};

#endif // CONSUMABLE_H
