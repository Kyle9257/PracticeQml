#include "SystemControlCore.h"

SystemControlCore *SystemControlCore::instance(){

    static SystemControlCore *instance = new SystemControlCore();
    return instance;
}

SimulatedDevicePtr SystemControlCore::simulatedDevice()
{
    return m_simulatedDevice;
}

SystemControlCore::SystemControlCore(QObject* parent)
    :QObject(parent){
    init();
}

void SystemControlCore::init()
{
    m_simulatedDevice = std::make_shared<SimulatedDevice>();
}

