#ifndef CUSCONFIG_H
#define CUSCONFIG_H

#include "CusConfig_global.h"
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
    T getValue(const std::string &key, const T& defaultValue = T());

    //获取嵌套参数
    template<typename T>
    T getNestedValue(const std::string &nestPath,const std::string &key,const T &defaultValue = T());

    //写入非嵌套参数
    template<typename T>
    void setValue (const std::string &key ,const T & value);

    template<typename T>
    void setNestValue(const std::string &nestPath ,
                      const std::string &key,
                      const T &value,
                      const std::string &defaultValue = T());

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
    class Impl;
    std::unique_ptr<Impl> m_implPtr;
    //nlohmann::json m_json;
};

#endif // CUSCONFIG_H
