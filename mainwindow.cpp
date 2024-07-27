#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "RadarFalsePlotSpawner.h"
#include "RadarBeamController.h"
#include <QPolarChart>
#include <QValueAxis>
#include <QScatterSeries>
#include <QtCore/QtCore>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(new RadarBeamController(this))
    , spawner(new RadarFalsePlotSpawner(this))
    , scope(new RadarPPIScope)

{
    ui->setupUi(this);
    ui->horizontalSlider->setMaximum(200);
    RadarFalsePlotSpawner radarFalsePlotSpawner;
    connect(ui->spawnRateSlider, &QSlider::valueChanged, this, &MainWindow::updateSpawnRate);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow::updateRpm);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startRotation);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopRotation);
    connect(controller, &RadarBeamController::rotationChanged, this, &MainWindow::updateDialRotation);
    connect(controller, &RadarBeamController::timerUpdated, this, &MainWindow::updateTimerDisplay);
    connect(controller, &RadarBeamController::degreeUpdated, this, &MainWindow::updateDegreeDisplay);
    connect(controller, &RadarBeamController::timerUpdated, this, &MainWindow::updateTimerDisplay);
    connect(ui->startButton, &QPushButton::clicked, spawner, &RadarFalsePlotSpawner::start);
    connect(ui->stopButton, &QPushButton::clicked, spawner, &RadarFalsePlotSpawner::stop);
    connect(spawner, &RadarFalsePlotSpawner::newPlot, scope, &RadarPPIScope::getNewPlot);
    ui->verticalLayout_2->insertWidget(0,scope->getChartView());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startRotation()
{
    controller->start();
}

void MainWindow::stopRotation()
{
    controller->stop();
}

void MainWindow::updateRpm(int value)
{
    ui->rpmLabel->setText(QString("RPM: %1").arg(value));
    controller->setRpm(value);
}

void MainWindow::updateSpawnRate(int newRate)
{
    ui->spawnRateLabel->setText(QString("spawn per sec: %1").arg(newRate));
    spawner->setRate(newRate);
}

void MainWindow::updateDialRotation(int angle)
{
    scope->stickAngle = angle;
    scope->stick->setRotation(angle-90);
    ui->degreeLabel->setText(QString("%1°").arg(angle % 360));
}

void MainWindow::updateTimerDisplay(int seconds)
{
    ui->sayacLabel->setText(QString("Timer: %1 seconds").arg(seconds));
}

void MainWindow::updateDegreeDisplay(int degrees)
{
    ui->degreeLabel->setText(QString("%1°").arg(degrees));
    spawner->emitterDegree = controller->degreeCounter1;
    spawner->rpm1 = controller->rpm;
}
