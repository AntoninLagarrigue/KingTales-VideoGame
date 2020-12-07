#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsPixmapItem>
#include "RectPlatform.h"

#define SCENE_WIDTH 5000
#define SCENE_HEIGHT 400

#define SCENE_GROUND_HEIGHT 368

class FireBall : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

public :
    FireBall(int direction, bool is_left,  QGraphicsItem * parent = 0);
    ~FireBall();
    bool handleCollisions();

private slots :
    void move();

private:
    QTimer * fireballTimer_;
    int direction_;
    bool is_left_;
    QPixmap * fireball_image_;



};


#endif // FIREBALL_H
