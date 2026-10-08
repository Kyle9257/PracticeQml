import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "JavaScript"
import "./DevicePractice"

ApplicationWindow {
    width: 800
    height: 900
    visible: true
    title: qsTr("QML数组操作学习")

MenuBar{

    Menu{
        title: "图片操作"
        MenuItem{
            text: "获取单张图片"
            onTriggered: {
            ImageHandle.getMat();
            }
        }
        MenuItem{
            text: "获取系列图片"
            onTriggered: {
            ImageHandle.getSeriesMat();
            }
        }
    }
}

    DevicePractice{
        id:deviceMonitor
        width: 400
        height: 150
        y:50
        x:10
    }
}
