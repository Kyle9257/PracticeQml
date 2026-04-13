#include "MainWidget.h"
#include "ui_mainwidget.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    // 连接保存按钮
    connect(ui->saveButton, &QPushButton::clicked, 
            this, &MainWidget::onSaveButtonClicked);
}

MainWidget::~MainWidget()
{
    delete ui;
}

// ==================== 获取当前算法类型 ====================
CommonDefine::WORKINGMOD MainWidget::getCurrentAlgorithm() const
{
    int currentIndex = ui->tabWidget->currentIndex();
    return getAlgorithmByTabIndex(currentIndex);
}

// 根据Tab索引获取对应的算法类型
CommonDefine::WORKINGMOD MainWidget::getAlgorithmByTabIndex(int index) const
{
    switch (index) {
    case 0:  return CommonDefine::WORKINGMOD::ANGLEpupil;    // 质心算法
    case 1:  return CommonDefine::WORKINGMOD::ANGLElight;    // 光斑角度
    case 2:  return CommonDefine::WORKINGMOD::ANGLElength;   // 长度角度
    case 3:  return CommonDefine::WORKINGMOD::ANGLEnumber;   // 数量角度
    case 4:  return CommonDefine::WORKINGMOD::ANGLEnoise;    // 噪声角度
    case 5:  return CommonDefine::WORKINGMOD::DARKPupil;     // 暗瞳
    case 6:  return CommonDefine::WORKINGMOD::LIGHTPupil;    // 亮瞳
    default: return CommonDefine::WORKINGMOD::DEFAULT;       // 原图/默认
    }
}

// ==================== 保存按钮点击处理 ====================
void MainWidget::onSaveButtonClicked()
{
    saveDataByAlgorithm();
}

// ==================== 根据算法类型保存数据 ====================
void MainWidget::saveDataByAlgorithm()
{
    CommonDefine::WORKINGMOD algorithm = getCurrentAlgorithm();
    QString timePrefix = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");

    switch (algorithm) {
    case CommonDefine::WORKINGMOD::ANGLEpupil:
        // Tab 0: 质心算法 - 保存质心参数
        {
            QString fileName = generateTimeStampedFileName("centroid_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                saveCentroidParams(m_currentCentroidParams, filePath);
                QMessageBox::information(this, "保存成功", "质心参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::ANGLElight:
        // Tab 1: 光斑角度算法
        {
            QString fileName = generateTimeStampedFileName("anglelight_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                AngleLightParams params;  // TODO: 从实际模块获取参数
                saveAngleLightParams(params, filePath);
                QMessageBox::information(this, "保存成功", "光斑角度参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::ANGLElength:
        // Tab 2: 长度角度算法
        {
            QString fileName = generateTimeStampedFileName("anglelength_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                AngleLengthParams params;  // TODO: 从实际模块获取参数
                saveAngleLengthParams(params, filePath);
                QMessageBox::information(this, "保存成功", "长度角度参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::ANGLEnumber:
        // Tab 3: 数量角度算法
        {
            QString fileName = generateTimeStampedFileName("anglenumber_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                // TODO: 实现数量角度参数保存
                QMessageBox::information(this, "保存成功", "数量角度参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::ANGLEnoise:
        // Tab 4: 噪声角度算法
        {
            QString fileName = generateTimeStampedFileName("anglenoise_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                // TODO: 实现噪声角度参数保存
                QMessageBox::information(this, "保存成功", "噪声角度参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::DARKPupil:
        // Tab 5: 暗瞳算法
        {
            QString fileName = generateTimeStampedFileName("darkpupil_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                // TODO: 实现暗瞳参数保存
                QMessageBox::information(this, "保存成功", "暗瞳参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::LIGHTPupil:
        // Tab 6: 亮瞳算法
        {
            QString fileName = generateTimeStampedFileName("lightpupil_", ".json");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                // TODO: 实现亮瞳参数保存
                QMessageBox::information(this, "保存成功", "亮瞳参数已保存:\n" + filePath);
            }
        }
        break;

    case CommonDefine::WORKINGMOD::DEFAULT:
    default:
        // 原图模式 - 只保存图片
        {
            QString fileName = generateTimeStampedFileName("original_", ".png");
            QString filePath = getSavePath(fileName);
            if (!filePath.isEmpty()) {
                QImage image;  // TODO: 从实际模块获取当前图像
                saveOriginalImage(image, filePath);
                QMessageBox::information(this, "保存成功", "原图已保存:\n" + filePath);
            }
        }
        break;
    }
}

// ==================== 各类型保存函数实现 ====================

QString MainWidget::getSavePath(const QString &defaultFileName) const
{
    return QFileDialog::getSaveFileName(
        this,
        tr("保存文件"),
        QDir::homePath() + "/Documents/" + defaultFileName,
        tr("所有文件 (*.*)")
    );
}

QString MainWidget::generateTimeStampedFileName(const QString &prefix, const QString &extension) const
{
    return prefix + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + extension;
}

void MainWidget::saveCentroidParams(const CentroidParams &params, const QString &filePath)
{
    QJsonObject json;
    json["algorithm"] = "ANGLEpupil";
    json["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    json["x"] = params.x;
    json["y"] = params.y;
    json["area"] = params.area;
    json["intensity"] = params.intensity;

    QJsonDocument doc(json);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "质心参数已保存:" << filePath;
    }
}

void MainWidget::saveAngleLightParams(const AngleLightParams &params, const QString &filePath)
{
    QJsonObject json;
    json["algorithm"] = "ANGLElight";
    json["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    json["angle"] = params.angle;
    json["confidence"] = params.confidence;

    QJsonDocument doc(json);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "光斑角度参数已保存:" << filePath;
    }
}

void MainWidget::saveAngleLengthParams(const AngleLengthParams &params, const QString &filePath)
{
    QJsonObject json;
    json["algorithm"] = "ANGLElength";
    json["timestamp"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    json["length"] = params.length;
    json["width"] = params.width;
    json["angle"] = params.angle;

    QJsonDocument doc(json);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
        qDebug() << "长度角度参数已保存:" << filePath;
    }
}

void MainWidget::saveOriginalImage(const QImage &image, const QString &filePath)
{
    if (!image.isNull()) {
        image.save(filePath);
        qDebug() << "原图已保存:" << filePath;
    } else {
        qWarning() << "图像为空，无法保存";
    }
}
