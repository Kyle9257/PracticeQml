#ifndef IMAGEHANDLE_H
#define IMAGEHANDLE_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QFileDialog>
#include <opencv2/opencv.hpp>



class ImageHandle : public QObject
{
    Q_OBJECT
public:
    ImageHandle();

    Q_INVOKABLE void getMat();

    //批量读取文件
    Q_INVOKABLE void getSeriesMat();
};

using ImageHandlePtr = std::shared_ptr<ImageHandle>;

#endif // IMAGEHANDLE_H
