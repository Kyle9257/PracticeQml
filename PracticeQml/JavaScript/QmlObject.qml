import QtQuick 2.15

Item {

    property var errorS: {
        "sevro":[1,2,3,5],
        "image":[5,4,3,2,1],
        "power":[9,8,7,6,5]
    }


    Component.onCompleted: {
        objectTest()
    }

    function objectTest(){
        console.log("sevro",errorS.sevro)
    }

}
