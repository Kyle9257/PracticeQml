#ifndef SIMUDEVICEHANDLE_H
#define SIMUDEVICEHANDLE_H

#include <QObject>
#include "SimulatedDeviceEvent.h"
#include <fstream>
#include <iostream>
#include "DataSaveManager/DataRecordManager.h"

struct Devicedata
{
    Q_GADGET
    Q_PROPERTY(int deviceID     MEMBER deviceID)
    Q_PROPERTY(double voltage   MEMBER voltage)
    Q_PROPERTY(double current   MEMBER current)
    Q_PROPERTY(double soc       MEMBER soc)
    Q_PROPERTY(QString version  MEMBER version)
    Q_PROPERTY(bool isRecord  MEMBER isRecord)

public:
    int deviceID    = 0;
    double voltage = 359.8;
    double current = 10.9;
    double soc = 100;
    bool isRecord = false;
    QString version = "1.20.36";
};

Q_DECLARE_METATYPE(Devicedata)

class SimuDeviceHandle :public QObject
{
    Q_OBJECT

    Q_PROPERTY(Devicedata deviceData READ deviceData  NOTIFY deviceDataChanged FINAL)
public:
    SimuDeviceHandle();
    ~SimuDeviceHandle();

    //数据保存
    Q_INVOKABLE void devieDataSave(bool ok);


    Devicedata deviceData() const;


signals:
    void deviceDataChanged();

protected:
    void customEvent(QEvent* event)override;
    void handleDevieEvent(SimulatedDeviceEvent * evt);
private:
    Devicedata m_deviceData;

    DataRecordManager *m_dataRecord = nullptr;
};

#endif // SIMUDEVICEHANDLE_H
