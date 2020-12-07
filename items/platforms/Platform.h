#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>

class Platform : public QGraphicsItem {

public :
    Platform(QGraphicsItem * parent = 0);
    ~Platform();

   // Draw
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
  // void nextFrame();

   // Getters & Setters
   QRectF boundingRect() const { return QRectF(0, 0, 100, 50); }

private:

   QPixmap * sprite_image_;

};

#endif // PLATFORM_H
