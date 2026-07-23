#include "DeviceHandler.h"
#include "SystemControlCore.h"


DeviceHandler::DeviceHandler() {
    SystemControlCore::instance()->simulatedDevice()->regidterDisplayComponent(this);
    SystemControlCore::instance()->simulatedDevice()->testSend();
}

void DeviceHandler::customEvent(QEvent *event)
{
    auto type = event->type();

    if(type ==SimulatedDeviceEvent::device_type){
        auto temEvent = static_cast<SimulatedDeviceEvent*>(event);
        handleDevieEvent(temEvent);

    }
}

void DeviceHandler::handleDevieEvent(SimulatedDeviceEvent *evt)
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

    if(changed){
        emit deviceDataChanged();
    }
}



Devicedata DeviceHandler::deviceData() const
{
    return m_deviceData;
}
