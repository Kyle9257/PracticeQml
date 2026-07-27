#include "Interactor.h"

Interactor::Interactor() {
    init();
}

void Interactor::initEngine(QQmlEngine *engine)
{
    engine->rootContext()->setContextProperty("SimuDeviceHandle",m_deviceHandle.get());
    engine->rootContext()->setContextProperty("ImageHandle",m_imageHandle.get());
}

void Interactor::init()
{
    m_deviceHandle = std::make_shared<SimuDeviceHandle>();

    m_imageHandle = std::make_shared<ImageHandle>();

}
