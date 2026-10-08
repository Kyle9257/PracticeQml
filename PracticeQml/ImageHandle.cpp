#include "ImageHandle.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include "CusConfig.h"
#include "Commondefine.h"


ImageHandle::ImageHandle() {}

void ImageHandle::getMat()
{
    auto tempPath = CusConfig::instance()->getValue<std::string>(ConfigKeys::SINGLE_MAT_PATH);

    QString configPath = QString::fromStdString(tempPath);
    //打开一个文件选择窗口
    QString filePath = QFileDialog::getOpenFileName(NULL,tr("select a file"),configPath);
    if(filePath.isNull()){
        return;
    }

    if(configPath != filePath){
        CusConfig::instance()->setValue(ConfigKeys::SINGLE_MAT_PATH,filePath.toStdString());
    }

    qDebug()<< "fileName:" << filePath;

    cv::Mat tempMat = cv::imread(filePath.toStdString(),cv::ImreadModes::IMREAD_COLOR);

    cv::namedWindow("tempWindow",cv::WINDOW_AUTOSIZE);
    cv::resizeWindow("tempWindow",300,400);

    cv::imshow("tempWindow",tempMat);

}

void ImageHandle::getSeriesMat()
{
    auto tempPath = CusConfig::instance()->getValue<std::string>(ConfigKeys::SAVE_IMAGE_PATH);

    QString configPath = QString::fromStdString(tempPath);

    QString filePath = QFileDialog::getExistingDirectory(nullptr,tr("选择一个文件夹"),configPath);

    if( filePath.isEmpty() ){
        return;
    }

    //文件不同时候，修改配置文件内容
    if(configPath != filePath ){
        CusConfig::instance()->setValue(ConfigKeys::SAVE_IMAGE_PATH,filePath.toStdString());
    }

    //QDir操作目录和文件系统路径
    QDir dir(filePath);
    QStringList fileFilter;
    fileFilter << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp" << "*.tif" << "*.tiff";

    //获取路劲下，文件的信息
    QFileInfoList fileInfo = dir.entryInfoList(fileFilter,
                                               QDir::Files,//类型/属性过滤器 (QDir::Filters)作用：控制包含哪些类型的文件和目录，以及它们的属性
                                               QDir::Name);//排序方式 (QDir::SortFlags)；作用：控制返回列表的排序顺序

    //按照名称排序
    std::sort(fileInfo.begin(),fileInfo.end(),[](const QFileInfo &a,const QFileInfo &b){

        bool okA,okB;
        int numA = a.baseName().toInt(&okA);
        int numB = b.baseName().toInt(&okB);

        if (!okA && !okB) return false;
        if (!okA) return false;
        if (!okB) return true;

        return numA < numB;

    });

    for( auto &fileName : fileInfo){

        qDebug()<<fileName.dir().dirName()<<":" <<fileName.baseName();

    }



}
