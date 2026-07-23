import QtQuick 2.15
import QtQuick.Window 2.15
import "JavaScript"
import "./DevicePractice"

Window {
    width: 800
    height: 900
    visible: true
    title: qsTr("QML数组操作学习")


    DevicePractice{
        id:deviceMonitor
        width: 400
        height: 80
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
