#ifndef SYSTEMCONTROLCORE_H
#define SYSTEMCONTROLCORE_H

#include <QObject>
#include <QCoreApplication>
#include "SimulatedDevice.h"

class SystemControlCore : public QObject
{
    Q_OBJECT
public:
//删除拷贝和移动构造函数，防止多实例
    SystemControlCore(const SystemControlCore&) = delete;
    SystemControlCore& operator=(const SystemControlCore&) = delete;

    static SystemControlCore* instance();

    //
    SimulatedDevicePtr simulatedDevice();

private:
    //私有化构造函数
    SystemControlCore(QObject* parent = nullptr);
    void init();

private:
    SimulatedDevicePtr m_simulatedDevice = nullptr;
};


#endif // SYSTEMCONTROLCORE_H
