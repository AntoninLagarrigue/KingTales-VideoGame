#include "MyRect.h"

void MyRect::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 0) setPos(x() - 10, y());
    } else if (event->key() == Qt::Key_Right) {
        if (pos().x() + this->rect().width() < 800) setPos(x() + 10, y());
    } else if (event->key() == Qt::Key_Up) {
        setPos(x(), y() - 10);
    }
}
