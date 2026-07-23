#include "Interactor.h"

Interactor::Interactor() {
    init();
}

void Interactor::initEngine(QQmlEngine *engine)
{
    engine->rootContext()->setContextProperty("DeviceHandler",m_deviceHandle.get());
}

void Interactor::init()
{
    m_deviceHandle = std::make_shared<DeviceHandler>();

}
