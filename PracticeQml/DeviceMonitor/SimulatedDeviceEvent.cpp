#include "SimulatedDeviceEvent.h"

SimulatedDeviceEvent::SimulatedDeviceEvent() :QEvent(device_type)
{}

SimulatedDeviceEvent::SimulatedDeviceEvent(SimulatedDeviceEvent &other) :
    QEvent(device_type),
    device_id(other.device_id),
    voltage(other.voltage),
    current(other.current),
    soc(other.soc),
    version(other.version)
{

}

SimulatedDeviceEvent::~SimulatedDeviceEvent()
{

}
