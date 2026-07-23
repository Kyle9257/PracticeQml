#ifndef SIMULATEDDEVICE_H
#define SIMULATEDDEVICE_H

#include <QObject>
#include <QVariantMap>

enum SystemDevice{
    ATP                = 0x01,
    LaserDevice        = 0x02,
    WaterCooler        = 0x03,
    AtpBMS             = 0x05,
    Inventer           = 0x06,
    DDRC               = 0x07,
    DehuimnDiffer      = 0x08,
    GNSS               = 0x09,
    Ins                = 0x0A,
    NetDistributionBox = 0x0B,
    PowerBoard         = 0x0C,
    ChillerBMS         = 0x0D
};

class SimulatedDevice : public QObject
{
    Q_OBJECT
public:
    explicit SimulatedDevice(QObject *parent  = nullptr);
    ~SimulatedDevice();

    void regidterDisplayComponent(QObject *);

    void testSend();

signals:
    void deviceInfoChanged(QVariantMap deviceConnectedInfo);
    void deviceConnectedChanged(QVariantMap);

private :
    std::function<void(QVariantMap)> m_handleDeviceInfo;
    void initDeviceInfo();
    void handleDeviceMessage();

private:
    QObject *m_displayComponent = nullptr;
};

using SimulatedDevicePtr = std::shared_ptr<SimulatedDevice>;

#endif // SIMULATEDDEVICE_H
