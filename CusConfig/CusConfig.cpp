#include "CusConfig.h"
#include "QCoreApplication"
#include "QFile"
#include "QDir"


CusConfig *CusConfig::instance()
{
    auto instance = new CusConfig();
    return instance;
}

CusConfig::CusConfig() {
    QString filePath = QCoreApplication::applicationFilePath() + "/Config/Config.json";
    readConfig(filePath);
}

void CusConfig::readConfig(QString &filePath)
{
    QFile file(filePath);

    if( !file.exists()){
        qWarning() << "Config file dose not exist" << filePath;
        return;
    }

    if( !file.open(QIODevice::ReadOnly)){
        qWarning() << "Cannot open config file for reading:" << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

  try {
        m_json = nlohmann::json::parse( data.toStdString() ) ;

    } catch (const nlohmann::json::parse_error& e) {
      qWarning() << "Failed to parse config JSON:" << e.what();
      qWarning() << "Using default configuration";
      m_json = nlohmann::json::object();
    }

}

void CusConfig::writeJsonTofile()
{
    QString configDir = QCoreApplication::applicationDirPath() + "/Config";
    QString configPath = configDir + "/Config.json";

    QFile file(configPath);

    //写入之前需要保证路径存在
    QDir dir(configDir);
    if( !dir.exists()){
        if(!dir.mkdir(configDir)){
            qWarning() << "Failed to cerate config directory:" << configDir;
        }
    }
    //写入文件
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        qWarning() << "Cannot open config file for writing:" << file.errorString();
        return;
    }
    try {
        std::string jsonStr = m_json.dump(4);
        qint64 written = file.write(jsonStr.c_str(),jsonStr.size());    //文件写入，data和大小

        if (written == jsonStr.size()) {
            qDebug() << "Config saved successfully to:" << configPath;
            qDebug() << "Saved config:" << QString::fromStdString(jsonStr);
        } else {
            qWarning() << "Failed to write all config data, written:" << written
                       << "expected:" << jsonStr.size();
        }

    } catch (const std::exception& e) {
        qWarning() << "Error writing config:" << e.what();
    }

    file.close();
}

