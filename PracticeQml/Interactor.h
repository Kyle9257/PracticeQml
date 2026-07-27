#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include "SimuDeviceHandle.h"
#include "ImageHandle.h"

class Interactor :public QObject
{
    Q_OBJECT
public:
    Interactor();

    //与qml界面交互管理类

    void initEngine(QQmlEngine* engine);
private:
    void init();
private:

    std::shared_ptr<SimuDeviceHandle> m_deviceHandle = nullptr;

    ImageHandlePtr  m_imageHandle  = nullptr;

};

#endif // INTERACTOR_H
