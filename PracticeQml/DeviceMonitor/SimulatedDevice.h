#ifndef SIMULATEDDEVICE_H
#define SIMULATEDDEVICE_H

#include <QObject>

class SimulatedDevice : public QObject
{
    Q_OBJECT
public:
   explicit SimulatedDevice(QObject *parent  = nullptr);
    ~SimulatedDevice();
};

#endif // SIMULATEDDEVICE_H
