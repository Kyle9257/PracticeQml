#include "SimuDeviceHandle.h"
#include "SystemControlCore.h"
#include "qdatetime.h"
#include "QCoreApplication"
#include "QDir"


SimuDeviceHandle::SimuDeviceHandle() {
    SystemControlCore::instance()->simulatedDevice()->regidterDisplayComponent(this);
    SystemControlCore::instance()->simulatedDevice()->testSend();
    m_dataRecord = new DataRecordManager();
}

void SimuDeviceHandle::devieDataSave(bool ok)
{
    m_deviceData.isRecord = ok;

    if(!ok){
        m_dataRecord->stopRecord();
    }

}

void SimuDeviceHandle::customEvent(QEvent *event)
{
    auto type = event->type();

    if(type ==SimulatedDeviceEvent::device_type){
        auto temEvent = static_cast<SimulatedDeviceEvent*>(event);
        handleDevieEvent(temEvent);

    }
}

void SimuDeviceHandle::handleDevieEvent(SimulatedDeviceEvent *evt)
{
    bool changed = false;
    auto updateValue = [&](auto &member, const auto &val) {
        if (member != val) {
            member = val;
            changed = true;
        }
    };

    updateValue(m_deviceData.deviceID,evt->device_id);
    updateValue(m_deviceData.voltage,evt->voltage);
    updateValue(m_deviceData.current,evt->current);
    updateValue(m_deviceData.soc,evt->soc);
    updateValue(m_deviceData.soc,evt->soc);
    updateValue(m_deviceData.version,evt->version);

    QStringList recordList;
    recordList.append(QString::number(m_deviceData.voltage));
    recordList.append(QString::number(m_deviceData.current));
    recordList.append(QString::number(m_deviceData.soc));

    if(m_deviceData.isRecord){
        m_dataRecord->appendData(recordList);
    }

    if(changed){
        emit deviceDataChanged();
    }
}



Devicedata SimuDeviceHandle::deviceData() const
{
    return m_deviceData;
}

QString SimuDeviceHandle::getCurFileName()
{
    auto curDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd#hh_mm_ss");
    auto curDir = QCoreApplication::applicationDirPath();
    auto targetDirName = curDir + "/dataRecord";
    QDir dir;
    dir.mkdir(targetDirName);//创建文件路径？

    auto fileName = targetDirName + "/" + "DataSave" + curDateTime + ".csv";
    return fileName;
}
