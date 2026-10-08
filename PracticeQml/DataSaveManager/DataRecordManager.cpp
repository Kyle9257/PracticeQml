#include "DataRecordManager.h"

DataRecordManager::DataRecordManager() {}

void DataRecordManager::appendData(QStringList &datalist)
{
    if ( m_dataWriteHandle == nullptr){
        m_curfileName = generateCurFileName().toStdString();
        m_dataWriteHandle = new std::ofstream(
            m_curfileName,std::ios::out | std::ios::trunc| std::ios::binary);
        // 1) 写入 UTF-8 BOM
        const char bom[3] = { '\xEF', '\xBB', '\xBF' };
        m_dataWriteHandle->write(bom, 3);

        QByteArray  title = QStringLiteral("电压,电流,电量\n").toUtf8();
        m_dataWriteHandle->write(title.constData(),title.size());
    }
    QString recordStr("");

    for( auto &ele : datalist){
        recordStr += (ele + ",");
    }
    recordStr.replace(recordStr.size() - 1, 1, '\n');

    QByteArray  retStr = recordStr.toUtf8();
    m_dataWriteHandle->write(retStr.constData(),retStr.size());

    static int countIndex = 0;
    countIndex ++ ;
    if( countIndex > 10){
        m_dataWriteHandle->flush();
        countIndex = 0;
    }

}

void DataRecordManager::stopRecord()
{
    if(m_dataWriteHandle != nullptr){
        m_dataWriteHandle->flush();
        m_dataWriteHandle->close();
    }
}

QString DataRecordManager::generateCurFileName()
{
    auto curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    auto curDir = QCoreApplication::applicationDirPath();
    auto curPath = curDir + "/dataRecord";
    QDir dir;
    dir.mkdir(curPath);
    auto curFileName = curPath + "/" + "Data" + curDate + ".csv";
    return curFileName;

}

