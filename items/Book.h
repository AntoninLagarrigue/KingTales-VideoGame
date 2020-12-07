#ifndef BOOK_H
#define BOOK_H


#include <QGraphicsItem>
#include <QPixmap>
#include "Consumable.h"

class Book : public Consumable {

public :
    Book(QGraphicsItem * parent = 0);
    ~Book();
};

#endif // BOOK_H
