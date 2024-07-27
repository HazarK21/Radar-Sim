#ifndef RADARBEAMCONTROLLER_H
#define RADARBEAMCONTROLLER_H

#include <QObject>
#include <QTimer>

class RadarBeamController : public QObject
{
    Q_OBJECT
public:
    explicit RadarBeamController(QObject *parent = nullptr);
    double degreeCounter;
    double degreeCounter1;
    int rpm;

signals:
    void rotationChanged(int angle);
    void timerUpdated(int seconds);
    void degreeUpdated(int degrees);

public slots:
    void start();
    void stop();
    void setRpm(int newRpm);
    int getTimerValue() const;

private slots:
    void updateRotation();
    void updateTimer();

private:
    double rotationAngle;
    QTimer *rotationTimer;
    QTimer *timer;
    int timerSeconds;
};
#endif
