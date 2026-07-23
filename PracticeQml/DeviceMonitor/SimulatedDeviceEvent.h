#ifndef SIMULATEDDEVICEEVENT_H
#define SIMULATEDDEVICEEVENT_H

#include <QObject>
#include <QEvent>

//可发送事件的类
//根据构造继承概念，继承类构造必须先构造基类
//QEvent没有默认构造函数，只有一个带参构造函数 explicit QEvent(Type type);


class SimulatedDeviceEvent : public QEvent
{
public:
    const static Type  device_type = static_cast<Type>(QEvent::User + 1);

    SimulatedDeviceEvent();
    //拷贝构造函数
    SimulatedDeviceEvent(SimulatedDeviceEvent & other);


    ~SimulatedDeviceEvent();

public:
    int device_id;
    double voltage;
    double current;
    double soc;
    QString version;


};

#endif // SIMULATEDDEVICEEVENT_H
