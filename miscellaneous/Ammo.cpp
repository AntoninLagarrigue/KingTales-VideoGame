#include "Ammo.h"

#include <QFont>
#include<QFontDatabase>
#include <QDebug>

Ammo::Ammo(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    ammoNb_ = 3;
    int id = QFontDatabase::addApplicationFont(":/fonts/Joystix Monospace.ttf");
    QFontDatabase::applicationFontFamilies(id);

    setPlainText(QString::number(ammoNb_)+QString(" AMMO"));
    setDefaultTextColor(QColor(255,112,81));

    setFont(QFont("Joystix Monospace",15));


}

Ammo::~Ammo()
{

}

void Ammo::increaseAmmo(int ammoNb) {
    if (ammoNb_ <= 15) ammoNb_ += ammoNb;
    if(ammoNb_ > 15) ammoNb_ = 15;
    if (ammoNb_ > 2 ) {
        setDefaultTextColor(QColor(255,112,81));
    }
    setPlainText(QString::number(ammoNb_)+QString(" AMMO"));

}
void Ammo::decreaseAmmo(int ammoNb) {
    if (ammoNb_ > 0) ammoNb_ -= ammoNb;
    if (ammoNb_ <= 2 ) {
        setDefaultTextColor(QColor(232,176,164));
    }
    setPlainText(QString::number(ammoNb_)+QString(" AMMO"));

}

int Ammo::getAmmoNb()
{
    return ammoNb_;
}

void Ammo::setAmmoNb(int ammoNb)
{
    ammoNb_ = ammoNb;
    if (ammoNb_<= 2 ) {
        setDefaultTextColor(QColor(232,176,164));
    }
    setPlainText(QString::number(ammoNb_)+QString(" AMMO"));
}

