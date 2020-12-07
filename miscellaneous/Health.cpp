#include "Health.h"
#include <QFont>
#include<QFontDatabase>
#include <QDebug>

Health::Health(int nb, QGraphicsItem *parent)
    : QGraphicsTextItem(parent), healthMax_(nb)
{
    healthNb_ = healthMax_ - 5;
}

Health::~Health()
{

}

void Health::increaseHealth(int lifePoint) {
    if (healthNb_ <= healthMax_) healthNb_ += lifePoint;
    if(healthNb_ > healthMax_) healthNb_ = healthMax_;
    if (healthNb_ >= healthMax_/3 ) {
        setDefaultTextColor(Qt::darkGreen);
    }
    setPlainText(QString::number(healthNb_)+QString(" HP"));

}

int Health::getHealthNb()
{
    return healthNb_;
}

void Health::setHealthNb(int healthNb)
{
    healthNb_ = healthNb;
    if (healthNb_< 5 ) {
        setDefaultTextColor(Qt::red);
    }
    setPlainText(QString::number(healthNb_)+QString(" HP"));
}

void Health::display() {
    int id = QFontDatabase::addApplicationFont(":/fonts/Joystix Monospace.ttf");
    QFontDatabase::applicationFontFamilies(id);

    setPlainText(QString::number(healthNb_)+QString(" HP"));
    setDefaultTextColor(Qt::darkGreen);

    setFont(QFont("Joystix Monospace",20));
}
