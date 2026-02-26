import QtQuick 2.15

//JavaScriptArray的练习
//C++使用信号将QVariantList发送到qml端，该列表自动被转换为JavaScriptArray
Item {
    id:root

    property var array1: [1,2,3,4,5]


    function outputArray(arry){
        console.log("array",arry)
    }

    Component.onCompleted: {

        //判断是否所有参数满足条件
        var arr1 = [1, 2, 3];
        var arr2 = [4, 5, 6];
        var arr3 = [7, 8, 9];

        var carray = arr1.concat(arr2,arr3);
        console.log("combine",carray)


        //遍历
        for(var i = 0; i < root.array1.length; i++){
            console.log("value",array1[i])
        }
        //第二种遍历
        for(var value of array1){
            console.log("for...of..",value)
        }
        //第三种遍历
        array1.forEach(function(value,index){

        console.log("for..Each",index,"值:",value);
        })

        array1.forEach(function(index,value){

        console.log("index",index,"value",value)//在JavaScript中，forEach的回调函数参数顺序是固定的：第一个参数是当前元素的值，第二个参数是当前索引，第三个参数是数组本身。
        })
    }
}
