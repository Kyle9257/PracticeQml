#include "SimulatedDevice.h"
#include "SimulatedDeviceEvent.h"
#include "QCoreApplication"
#include <QRandomGenerator>

SimulatedDevice::SimulatedDevice(QObject*parent) {

    initDeviceInfo();   //模拟接收到，设备连接信息

    m_simulateTimer = new QTimer(this);

    connect(m_simulateTimer,&QTimer::timeout,this,&SimulatedDevice::onSimulateTimeout);

    m_simulateTimer->start(1000);

    //handleDeviceMessage();//模拟接收到设备通信信息
}

SimulatedDevice::~SimulatedDevice()
{
    m_simulateTimer->stop();
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

double uniforNoise(double min, double max){
    double r = QRandomGenerator::global()->generateDouble();
    return min + r * (max - min);
}

void SimulatedDevice::handleDeviceMessage()
{

    auto  tempEvent = new SimulatedDeviceEvent();

    double randomV = uniforNoise(350,360);
    double randomC = uniforNoise(10,11);
    double randomS = uniforNoise(90,100);

    tempEvent->device_id = 12;
    tempEvent->voltage = randomV;
    tempEvent->current = randomC;
    tempEvent->soc = randomS;
    tempEvent->version =  QString("2.25.103");

    if(m_displayComponent){

        QCoreApplication::postEvent(m_displayComponent,tempEvent);
    }

}

void SimulatedDevice::onSimulateTimeout()
{
    handleDeviceMessage();
}
