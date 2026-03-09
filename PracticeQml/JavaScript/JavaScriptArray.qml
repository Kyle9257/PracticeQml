import QtQuick 2.15

//JavaScriptArray的练习
//C++使用信号将QVariantList发送到qml端，该列表自动被转换为JavaScriptArray
Item {
    id:root

    //数组内为纯数字
    property var array1: [1,2,3,4,5]

    //数组内为JavaScript对象，对象
    property var array: [{name : "a" , age : 30},
     {name : "b" , age: 35 , level:1}]


    function outputArray(arry){
        console.log("array",arry)
    }

    Component.onCompleted: {
        arrayParse1()

        var newArray = array1.filter(function(a,b){

        })


    }


    function arrayParse1(){
        var array = [ 1, 1,2 ,3,3,4,4,5,5,6,6,7,8,9,10]

        var removed = array.slice(2,5) //索引从2到5（不包括5）
        console.log("removed",removed)

        array.splice(4,2)//
        console.log("spliced",array)//删除从索引1开始，2个长度数

        var newA = array.findIndex(value=>value>5)
        console.log("newA",newA)

        let newArr = array.filter(value=>value>5)
        console.log("newArr",newArr)

    }
}
