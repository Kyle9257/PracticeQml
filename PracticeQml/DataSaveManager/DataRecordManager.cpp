#include "DataRecordManager.h"

DataRecordManager::DataRecordManager() {}

DataRecordManager::~DataRecordManager()
{
    stopRecord();
}

void DataRecordManager::appendData(QStringList &datalist)
{
    if (datalist.isEmpty()) return;
    if ( m_dataWriteHandle == nullptr){
        m_curfileName = generateCurFileName().toStdString();

        m_dataWriteHandle = new std::ofstream(
            m_curfileName,std::ios::out | std::ios::trunc| std::ios::binary);

        //检查是否可以读写
        if (!m_dataWriteHandle->is_open()) {
            delete m_dataWriteHandle;
            m_dataWriteHandle = nullptr;
            // 记录日志/抛异常
            return;
        }

        // 1) 写入 UTF-8 BOM
        const char bom[3] = { '\xEF', '\xBB', '\xBF' };
        m_dataWriteHandle->write(bom, 3);

        QByteArray  title = QStringLiteral("电压,电流,电量\n").toUtf8();
        m_dataWriteHandle->write(title.constData(),title.size());
    }

    QString recordStr = datalist.join(',');
    recordStr += '\n';

    QByteArray  retStr = recordStr.toUtf8();
    m_dataWriteHandle->write(retStr.constData(),retStr.size());

    m_countIndex ++ ;
    if( m_countIndex > 10){
        m_dataWriteHandle->flush();
        m_countIndex = 0;
    }
}

void DataRecordManager::stopRecord()
{
    if(m_dataWriteHandle != nullptr){
        m_dataWriteHandle->flush();
        m_dataWriteHandle->close();
        delete m_dataWriteHandle;
        m_dataWriteHandle = nullptr;
    }
}

QString DataRecordManager::generateCurFileName()
{
    auto curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss");
    auto curDir = QCoreApplication::applicationDirPath();
    auto curPath = curDir + "/dataRecord";
    QDir dir;
    dir.mkdir(curPath);
    auto curFileName = curPath + "/" + "Device-" + curDate + ".csv";
    return curFileName;

}

