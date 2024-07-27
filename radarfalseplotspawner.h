#ifndef RADARFALSEPLOTSPAWNER_H
#define RADARFALSEPLOTSPAWNER_H

#include "qtmetamacros.h"
#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class RadarFalsePlotSpawner : public QObject
{
    Q_OBJECT
public:
    explicit RadarFalsePlotSpawner(QObject *parent = nullptr);
    bool isRunning;
    double emitterDegree;
    double emitterDistance;
    int rpm1;

signals:
    void newPlot(double distance, double degree);

public slots:
    void start(int spawnRate);
    void setRate(int newRate);
    void stop();
    double generateRandomDistance();
    void spawnPlot();

private slots:

private:
    QTimer *spawnTimer;
    int spawnRate;

    RadarFalsePlotSpawner *spawner;
    double generateRandomDegree();
};
#endif
