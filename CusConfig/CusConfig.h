#ifndef CUSCONFIG_H
#define CUSCONFIG_H

#include "CusConfig_global.h"
#include "json.hpp"
#include "QString"
#include "QDebug"

//程序运行自动，读取配置文件
//程序中可以修改配置文件

//帮助我理解qt的文件IO操作，从文件中读取数据，向文件中写入数据
//QDir:路径，文件夹创建，查找等
//QFile:具体到某一个文件，QIODevice



class CUSCONFIG_EXPORT CusConfig
{
public:
    static CusConfig *instance();

    //获取键对应值
    template<typename T>
    inline T getValue(const std::string &key, const T& defaultValue = T()){
        try {
            if(m_json.contains(key))
            {
                return m_json[key].get<T>();
            }else {
                m_json[key] = defaultValue;
                writeJsonTofile();
            }

        } catch (const std::exception &e) {
            qWarning()<< "getValue failed:" <<QString::fromStdString(key) << e.what();
        }
        return defaultValue;
    }

    //获取嵌套参数
    template<typename T>
    inline T getNestedValue(const std::string &nestPath,const std::string &key,const T &defaultValut = T()){
        try {
            if(!m_json.contains(nestPath)){
                qWarning()<< "Path dose not exists, please check config file.";
                m_json[nestPath][key] = defaultValut;
                writeJsonTofile();
                return defaultValut;
            }
            if(!m_json[nestPath].contains(key)){
                qWarning()<< "Key dose not exists,please check config file.";
                m_json[nestPath][key] = defaultValut;
                writeJsonTofile();
                return defaultValut;
            }
            return m_json[nestPath][key].get<T>();
        } catch (const std::exception &e) {
            qWarning() << "getNestedValue failed:" << QString::fromStdString(nestPath)
            << "/" << QString::fromStdString(key) << e.what();
        }
        return defaultValut;
    }

    //写入非嵌套参数
    template<typename T>
    inline void setValue (const std::string &key ,const T & value,const T&defaultValue = T()){
        m_json[key] = value;    //不管有没有key，都写入缓存
        writeJsonTofile();      //再写入文件
    }

    template<typename T>
    inline void setNestValue(const std::string &nestPath ,
                             const std::string &key,
                             const T &value,
                             const std::string &defaultValue = T()){
        m_json[nestPath][key] = value;
    }

    //拷贝构造函数
    CusConfig(const CusConfig&) = delete;
    CusConfig & operator=(const CusConfig&) = delete;

private:
    CusConfig();
    //读取配置文件
    void readConfig(QString &filePath);

    //将改动写入配置文件
    void writeJsonTofile();


private:
    //读取的程序配置，json格式
    nlohmann::json m_json;
};

#endif // CUSCONFIG_H
