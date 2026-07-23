#include "SimulatedDevice.h"
#include "SimulatedDeviceEvent.h"
#include "QCoreApplication"

SimulatedDevice::SimulatedDevice(QObject*parent) {

    initDeviceInfo();   //模拟接收到，设备连接信息
    handleDeviceMessage();//模拟接收到设备通信信息
}

SimulatedDevice::~SimulatedDevice()
{

}

void SimulatedDevice::regidterDisplayComponent(QObject *obj)
{
    m_displayComponent = obj;
}

void SimulatedDevice::testSend()
{
    handleDeviceMessage();
}
//初始化设备连接状态
void SimulatedDevice::initDeviceInfo()
{
    std::map<int,bool> tempDeviceConnected= {
        {SystemDevice::ATP               ,true},
        {SystemDevice::LaserDevice       ,false},
        {SystemDevice::WaterCooler       ,true},
        {SystemDevice::AtpBMS            ,false},
        {SystemDevice::Inventer          ,true},
        {SystemDevice::DDRC              ,false},
        {SystemDevice::DehuimnDiffer     ,true},
        {SystemDevice::GNSS              ,false},
        {SystemDevice::Ins               ,true},
        {SystemDevice::NetDistributionBox,false},
        {SystemDevice::PowerBoard        ,true},
        {SystemDevice::ChillerBMS        ,false}

    };

    QVariantMap temDeviceMap;

    for(const auto [dev, connected] : tempDeviceConnected){
        temDeviceMap.insert(QString::number(static_cast<int>( dev)),connected);
    }
    if(m_handleDeviceInfo){
        m_handleDeviceInfo(temDeviceMap);
    }

}

void SimulatedDevice::handleDeviceMessage()
{
    auto  tempEvent = new SimulatedDeviceEvent();
    tempEvent->device_id = 12;
    tempEvent->voltage = 350.2;
    tempEvent->current = 10.2;
    tempEvent->soc = 99.8;
    tempEvent->version =  QString("2.25.103");

    if(m_displayComponent){

        QCoreApplication::postEvent(m_displayComponent,tempEvent);
    }

}
