#include "RadarFalsePlotSpawner.h"
#include <QRandomGenerator>
#include <QDebug>

RadarFalsePlotSpawner::RadarFalsePlotSpawner(QObject *parent) : QObject(parent), isRunning(false), spawnTimer(new QTimer(this))
{
    connect(spawnTimer, &QTimer::timeout, this, &RadarFalsePlotSpawner::spawnPlot);
}

void RadarFalsePlotSpawner::start(int spawnRate)
{
    isRunning = true;
    spawnTimer->start(10);
}

void RadarFalsePlotSpawner::stop()
{
    isRunning = false;
    spawnTimer->stop();
}

void RadarFalsePlotSpawner::spawnPlot()
{
    if (rpm1>0 && isRunning && QRandomGenerator::global()->bounded(100) < spawnRate)
    {
        double distance = generateRandomDistance();
        double degree = emitterDegree;
        emitterDistance=distance;
        emit newPlot(distance, degree);
        qDebug() << "Yeni plot - Uzaklik:" << distance << " Derece:" << degree<< " spawn orani: saniyede" << spawnRate;
    }
}

double RadarFalsePlotSpawner::generateRandomDistance()
{
    return QRandomGenerator::global()->bounded(100, 10000);
}

void RadarFalsePlotSpawner::setRate(int newRate)
{
    spawnRate = newRate;
}
