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
            text: "获系列图片"
            onTriggered: {
            ImageHandle.getSeriesMat();
            }
        }
    }
}

    DevicePractice{
        id:deviceMonitor
        width: 400
        height: 80
        y:100
    }

    // JavaScriptArray{
    // }

    // JavaScriptMap{

    // }

    // MapPractice{
    //     id:mapPractice
    //     width: 200
    //     height: 320
    // }

    // QmlObject{

    // }

    // 数组高级操作 - reduce/sort/some/every/flat
    // ArrayAdvanced {
    //     anchors.fill: parent
    // }

    // 数组链式调用实战 - 取消注释后可切换
    // ArrayChainPractice {
    //     anchors.fill: parent
    // }
}
