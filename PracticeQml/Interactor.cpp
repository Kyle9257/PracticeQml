#include "Interactor.h"

Interactor::Interactor() {
    init();
}

void Interactor::initEngine(QQmlEngine *engine)
{
    engine->rootContext()->setContextProperty("DeviceHandler",m_deviceHandle.get());
    engine->rootContext()->setContextProperty("ImageHandle",m_imageHandle.get());
}

void Interactor::init()
{
    m_deviceHandle = std::make_shared<DeviceHandler>();

    m_imageHandle = std::make_shared<ImageHandle>();

}
