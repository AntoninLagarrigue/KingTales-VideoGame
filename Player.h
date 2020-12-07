#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPixmap>
#include <QKeyEvent>

#define SCENE_WIDTH 3000
#define SCENE_HEIGHT 400

#define SCENE_GROUND_HEIGHT 368

#include <FireBall.h>
#include "Health.h"

class Player : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0);

   // Draw
   void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
   void nextFrame();

   // Getters & Setters
   QRectF boundingRect() const { return QRectF(0, 0, 23, 32); }
   QGraphicsItem * getTouchedPlatform();
   void setTouchedPlatform(QGraphicsItem * item);
   bool getIs_Left();
   void setIs_Left(bool direction);
   int getState() const;
   void setState(int state);
   Health * getHealth() { return health_;};
   void setHealth(Health * health) {health_ = health;};

   // Actions
   FireBall * throwFireball();

   // Collisions
   bool isTouchingFeet(QGraphicsItem *item);
   bool isTouchingHead(QGraphicsItem *item);
   bool isTouchingPlatform(QGraphicsItem *item);


private:

   //Draw
   QPixmap * sprite_image_;
    int current_frame_;

    // State
    int state_; // -1 for left, 0 for transition, 1 for right
    bool is_Left_;

    // Items related to the player
    QGraphicsItem *touchedPlatform_;
    FireBall * fireball_;
    Health * health_;

};

#endif // PLAYER_H
