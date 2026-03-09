import QtQuick 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    property var map1: new Map()//键-值对

    ColumnLayout{
        anchors.fill: parent

        Text {
            id: name
            Layout.preferredWidth: 100
            Layout.preferredHeight: 30
            text: qsTr("text")
        }
        Text {
            id: name1
            Layout.preferredWidth: 100
            Layout.preferredHeight: 30
            text: qsTr("text")
        }
    }



    function mapTest(){
        root.map1.set("name","kyle")
        root.map1.set("wife","lichi")

        //console.log("map1",map1)
    }

    Component.onCompleted: {

        mapTest()
        map1.forEach((value, key) =>{
                     console.log(key + ":", value)
                     })

        console.log("value",map1.get("name"))//获取当前键对应的值
        console.log("size",map1.size)
    }

}
