import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

// 封装一个ColorManagedText组件
Rectangle {
    width: 400
    height: 300
    color: "#f5f5f5"

    // 全局颜色管理器
    QtObject {
        id: colorManager

        // 使用组件对象作为键的Map
        property var colorMap: new Map()

        // 注册组件并设置颜色
        function register(component, defaultColor) {
            colorMap.set(component, defaultColor)
            component.color = defaultColor
        }

        // 更新组件颜色
        function setColor(component, newColor) {
            if (colorMap.has(component)) {
                colorMap.set(component, newColor)
                component.color = newColor
            }
        }

        // 获取组件颜色
        function getColor(component) {
            return colorMap.get(component)
        }

        // 显示所有颜色
        function dump() {
            console.log("=== 颜色管理器内容 ===")
            colorMap.forEach((color, component) => {
                console.log(`${component.text}: ${color}`)
            })
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        // 使用封装的文本组件
        Text {
            id: text1
            text: "红色文本"

            Component.onCompleted: {
                colorManager.register(text1, "red")
            }
        }

        Text {
            id: text2
            text: "蓝色文本"

            Component.onCompleted: {
                colorManager.register(text2, "blue")
            }
        }

        Text {
            id: text3
            text: "绿色文本"

            Component.onCompleted: {
                colorManager.register(text3, "green")
            }
        }

        Row {
            spacing: 10
            Button {
                text: "交换颜色"
                onClicked: {
                    let color1 = colorManager.getColor(text1)
                    let color2 = colorManager.getColor(text2)
                    let color3 = colorManager.getColor(text3)
                    colorManager.setColor(text1, color3)
                    colorManager.setColor(text2, color1)
                    colorManager.setColor(text3, color2)
                }
            }

            Button {
                text: "显示Map内容"
                onClicked: colorManager.dump()
            }
        }
    }
}
