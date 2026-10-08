#ifndef DATARECORDMANAGER_H
#define DATARECORDMANAGER_H

#include <QObject>
#include <QDateTime>

#include <iostream>
#include <fstream>
#include <QCoreApplication>
#include <QDir>
#include <QStringList>

//数据存储管理类

class DataRecordManager : public QObject
{
    Q_OBJECT
public:
    DataRecordManager();
    ~DataRecordManager();

    //需要保存数据的地方直接调用该函数，传入数据信息直接保存
    void appendData(QStringList &datalist);
    void stopRecord();


private:
    QString generateCurFileName();



private:
    std::ofstream       *m_dataWriteHandle = nullptr;
    std::string         m_curfileName = "";
    int                 m_countIndex = 0;
};

#endif // DATARECORDMANAGER_H
