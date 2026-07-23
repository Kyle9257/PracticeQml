#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>
#include "DeviceHandler.h"

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

    std::shared_ptr<DeviceHandler> m_deviceHandle = nullptr;

};

#endif // INTERACTOR_H
