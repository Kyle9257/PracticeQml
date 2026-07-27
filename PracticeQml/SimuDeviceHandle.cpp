#include "SimuDeviceHandle.h"
#include "SystemControlCore.h"


SimuDeviceHandle::SimuDeviceHandle() {
    SystemControlCore::instance()->simulatedDevice()->regidterDisplayComponent(this);
    SystemControlCore::instance()->simulatedDevice()->testSend();
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

    if(changed){
        emit deviceDataChanged();
    }
}



Devicedata SimuDeviceHandle::deviceData() const
{
    return m_deviceData;
}
