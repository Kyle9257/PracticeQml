#include "CusConfig.h"
#include "QCoreApplication"
#include "QFile"
#include "QDir"
#include "json.hpp"

class CusConfig::Impl {
public:
    nlohmann::json data;
};


//真正单例
CusConfig *CusConfig::instance()
{
    static  CusConfig s_instance;
    return &s_instance;
}

CusConfig::CusConfig():m_implPtr(std::make_unique<Impl>()) {

    QString filePath = QCoreApplication::applicationDirPath() + "/Config/Config.json";
    readConfig(filePath);
}

void CusConfig::readConfig(QString &filePath)
{
    QFile file(filePath);

    if( !file.exists()){
        qWarning() << "Config file does not exist" << filePath;
        return;
    }

    if( !file.open(QIODevice::ReadOnly)){
        qWarning() << "Cannot open config file for reading:" << file.errorString();
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    try {
        m_implPtr->data = nlohmann::json::parse( data.toStdString() ) ;

    } catch (const nlohmann::json::parse_error& e) {
        qWarning() << "Failed to parse config JSON:" << e.what();
        qWarning() << "Using default configuration";
        m_implPtr->data = nlohmann::json::object();
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
        if(!dir.mkpath(configDir)){
            qWarning() << "Failed to create config directory:" << configDir;
        }
    }
    //写入文件
    if(!file.open(QIODevice::WriteOnly|QIODevice::Truncate)){
        qWarning() << "Cannot open config file for writing:" << file.errorString();
        return;
    }
    try {
        std::string jsonStr = m_implPtr->data.dump(4);
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


template<typename T>
T CusConfig::getValue(const std::string &key, const T &defaultValue){
    try {
        if(m_implPtr->data.contains(key))
        {
            return m_implPtr->data[key].get<T>();
        }

    } catch (const std::exception &e) {
        qWarning()<< "getValue failed:" <<QString::fromStdString(key) << e.what();
    }
    return defaultValue;
}



template<typename T>
void CusConfig::setNestValue(const std::string &nestPath, const std::string &key, const T &value, const std::string &defaultValue){
    m_implPtr->data[nestPath][key] = value;
    writeJsonTofile();
}

template<typename T>
void CusConfig::setValue(const std::string &key, const T &value){
    m_implPtr->data[key] = value;    //不管有没有key，都写入缓存
    writeJsonTofile();      //再写入文件
}

template<typename T>
T CusConfig::getNestedValue(const std::string &nestPath, const std::string &key, const T &defaultValue)
{
    try {
        if(!m_implPtr->data.contains(nestPath)){
            qWarning()<< "Path does not exist, please check config file.";
            m_implPtr->data[nestPath][key] = defaultValue;
            writeJsonTofile();
            return defaultValue;
        }
        if(!m_implPtr->data[nestPath].contains(key)){
            qWarning()<< "Key does not exist, please check config file.";
            m_implPtr->data[nestPath][key] = defaultValue;
            writeJsonTofile();
            return defaultValue;
        }
        return m_implPtr->data[nestPath][key].get<T>();
    } catch (const std::exception &e) {
        qWarning() << "getNestedValue failed:" << QString::fromStdString(nestPath)
        << "/" << QString::fromStdString(key) << e.what();
    }
    return defaultValue;
}

// ── 显式实例化（从 DLL 导出） ──

template CUSCONFIG_EXPORT int         CusConfig::getValue<int>(const std::string&, const int&);
template CUSCONFIG_EXPORT double      CusConfig::getValue<double>(const std::string&, const double&);
template CUSCONFIG_EXPORT bool        CusConfig::getValue<bool>(const std::string&, const bool&);
template CUSCONFIG_EXPORT std::string CusConfig::getValue<std::string>(const std::string&, const std::string&);

template CUSCONFIG_EXPORT void CusConfig::setValue<int>(const std::string&, const int&);
template CUSCONFIG_EXPORT void CusConfig::setValue<double>(const std::string&, const double&);
template CUSCONFIG_EXPORT void CusConfig::setValue<bool>(const std::string&, const bool&);
template CUSCONFIG_EXPORT void CusConfig::setValue<std::string>(const std::string&, const std::string&);

template CUSCONFIG_EXPORT int         CusConfig::getNestedValue<int>(const std::string&, const std::string&, const int&);
template CUSCONFIG_EXPORT double      CusConfig::getNestedValue<double>(const std::string&, const std::string&, const double&);
template CUSCONFIG_EXPORT bool        CusConfig::getNestedValue<bool>(const std::string&, const std::string&, const bool&);
template CUSCONFIG_EXPORT std::string CusConfig::getNestedValue<std::string>(const std::string&, const std::string&, const std::string&);

template CUSCONFIG_EXPORT void CusConfig::setNestValue<int>(const std::string&, const std::string&, const int&, const std::string&);
template CUSCONFIG_EXPORT void CusConfig::setNestValue<double>(const std::string&, const std::string&, const double&, const std::string&);
template CUSCONFIG_EXPORT void CusConfig::setNestValue<bool>(const std::string&, const std::string&, const bool&, const std::string&);
template CUSCONFIG_EXPORT void CusConfig::setNestValue<std::string>(const std::string&, const std::string&, const std::string&, const std::string&);
