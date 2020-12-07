#ifndef RECTPLATFORM_H
#define RECTPLATFORM_H

#include <QGraphicsItem>
#include <QPen>
#include <qdebug.h>

#define SCENE_WIDTH 1600
#define SCENE_HEIGHT 400

#define SCENE_GROUND_HEIGHT 368

class RectPlatform : public QGraphicsRectItem {


 public:
    RectPlatform(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = 0);
    ~RectPlatform();
    qreal getWidth();
    qreal getHeight();

    qreal getX() const;
    void setX(const qreal &x);

    qreal getY() const;
    void setY(const qreal &y);

private:
    qreal width_;
    qreal height_;
    qreal x_;
    qreal y_;



};

#endif // RECTPLATFORM_H
