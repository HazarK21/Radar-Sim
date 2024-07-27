#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RadarBeamController.h"
#include "RadarFalsePlotSpawner.h"
#include <QGraphicsEllipseItem>
#include <QChart>
#include "radarppiscope.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;

public slots:

private slots:
    void startRotation();
    void stopRotation();
    void updateRpm(int value);
    void updateSpawnRate(int newRate);
    void updateDialRotation(int angle);
    void updateTimerDisplay(int seconds);
    void updateDegreeDisplay(int degrees);

private:
    RadarBeamController *controller;
    RadarFalsePlotSpawner *spawner;
    QGraphicsScene *Scene;
    QGraphicsEllipseItem *ItemEllipse;
    RadarPPIScope *scope;
};
#endif
