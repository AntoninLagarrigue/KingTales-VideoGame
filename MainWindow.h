#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QMainWindow>
#include <QGraphicsView>
#include "Scene.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 400

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private:
    Scene * scene_;
    QGraphicsView * view_;
};

#endif // MAINWINDOW_H
