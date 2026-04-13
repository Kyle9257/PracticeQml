#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDateTime>
#include <QDebug>

// 算法类型定义 - 请根据你的 CommonDefine.hpp 调整
namespace CommonDefine {
    // 算法工作模式枚举
    enum class WORKINGMOD {
        DEFAULT = -1,      // 原图模式（无算法）
        ANGLElight = 0,    // 光斑角度算法
        ANGLElength = 1,   // 长度角度算法
        ANGLEnumber = 2,   // 数量角度算法
        ANGLEnoise = 3,    // 噪声角度算法
        ANGLEpupil = 4,    // 质心算法
        DARKPupil = 5,     // 暗瞳算法
        LIGHTPupil = 6     // 亮瞳算法
    };
}

// 质心参数结构
struct CentroidParams {
    double x = 0.0;
    double y = 0.0;
    double area = 0.0;
    double intensity = 0.0;
    qint64 timestamp = 0;
};

// 其他算法参数结构（按需扩展）
struct AngleLightParams {
    double angle = 0.0;
    double confidence = 0.0;
};

struct AngleLengthParams {
    double length = 0.0;
    double width = 0.0;
    double angle = 0.0;
};

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    // 获取当前算法类型
    CommonDefine::WORKINGMOD getCurrentAlgorithm() const;

    // 根据算法类型保存数据
    void saveDataByAlgorithm();

private slots:
    void onSaveButtonClicked();

private:
    // 根据当前Tab索引获取算法类型
    CommonDefine::WORKINGMOD getAlgorithmByTabIndex(int index) const;

    // 获取保存路径
    QString getSavePath(const QString &defaultFileName) const;

    // 保存质心参数
    void saveCentroidParams(const CentroidParams &params, const QString &filePath);

    // 保存角度光斑参数
    void saveAngleLightParams(const AngleLightParams &params, const QString &filePath);

    // 保存角度长度参数
    void saveAngleLengthParams(const AngleLengthParams &params, const QString &filePath);

    // 保存原图
    void saveOriginalImage(const QImage &image, const QString &filePath);

    // 生成带时间戳的文件名
    QString generateTimeStampedFileName(const QString &prefix, const QString &extension) const;

private:
    Ui::MainWidget *ui;
    
    // 模拟当前质心参数（实际应从图像处理模块获取）
    CentroidParams m_currentCentroidParams;
};

#endif // MAINWIDGET_H
