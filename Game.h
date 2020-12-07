#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QObject>
#include <QGraphicsView>
#include <QTimer>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include "Button.h"
#include "Scene.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400

#define GROUND_HEIGHT 368

#define JUMP_HEIGHT 100

class Game : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpCoeff READ jumpCoeff WRITE setJumpCoeff NOTIFY jumpCoeffChanged)

public:
    Game(QWidget * parent = 0);
    ~Game();

    // Events
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void handleEvents();
    void gameOver();
    void displayGameOver();
    // Getters & Setters
    QPropertyAnimation *getJumpAnimation();
    qreal jumpCoeff() const;
    void setJumpCoeff(const qreal &jumpCoeff);

    // Collisions
    bool handleCollisionWhileFalling();
    bool handleCollisionWhileJumpingDown();
    void checkIfTheFloorIsLava();
    void checkIfMonster();


    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);
    void start();


signals:
    void jumpCoeffChanged(qreal);

public slots:
    void move();
    void jump();
    void gravity();
    void isGameOver();
    void restartGame();


private:
    // Timer
    QTimer move_timer_;
    QTimer gravity_timer_;
    QTimer health_timer;
    // Scene
    Scene * scene_;
    Button * playAgainButton_;
    bool isMovable;
    void moveView();

    //Animation
    QPropertyAnimation * jumpAnimation_;
    qreal jumpCoeff_;

    //Collisions
    bool on_a_platform_;
    //qreal new_jumpLevel_;
    QGraphicsItem * new_ground;

};

#endif // GAME_H
