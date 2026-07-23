#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <QObject>
#include "SimulatedDeviceEvent.h"

struct Devicedata
{
    Q_GADGET
    Q_PROPERTY(int deviceID     MEMBER deviceID)
    Q_PROPERTY(double voltage   MEMBER voltage)
    Q_PROPERTY(double current   MEMBER current)
    Q_PROPERTY(double soc       MEMBER soc)
    Q_PROPERTY(QString version  MEMBER version)

public:
    int deviceID    = 0;
    double voltage = 359.8;
    double current = 10.9;
    double soc = 100;
    QString version = "1.20.36";
};

Q_DECLARE_METATYPE(Devicedata)

class DeviceHandler :public QObject
{
    Q_OBJECT

    Q_PROPERTY(Devicedata deviceData READ deviceData  NOTIFY deviceDataChanged FINAL)
public:
    DeviceHandler();


    Devicedata deviceData() const;

signals:
    void deviceDataChanged();

protected:
    void customEvent(QEvent* event)override;
    void handleDevieEvent(SimulatedDeviceEvent * evt);
private:
    Devicedata m_deviceData;
};

#endif // DEVICEHANDLER_H
