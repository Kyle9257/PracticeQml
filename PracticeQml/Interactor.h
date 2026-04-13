#ifndef INTERACTOR_H
#define INTERACTOR_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlContext>

class Interactor :public QObject
{
    Q_OBJECT
public:
    Interactor();

    //与qml界面交互管理类
    void initEngine(QQmlEngine* engine);
};

#endif // INTERACTOR_H
