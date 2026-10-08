import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root

    Rectangle{
        id:backgroudRec
        anchors.fill: parent
        color: "#000080"
        radius: 4
    }

    Text {
        id: titleName
        text: qsTr("SimulateDevie")
        font.pixelSize: 16
        font.bold: true
        color: "white"

        anchors{
            top: parent.top
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }

    }

    RowLayout{
        id: infoRow
        width: parent.width * 0.95
        height: 70
        spacing: 5
        anchors{
            top: titleName.bottom
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }

        Rectangle{
            id:votageRec
            color: "#FFFAFA"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: parent.height - titleName.height
            radius: 4
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: voltageValue
                    text: SimuDeviceHandle.deviceData.voltage.toFixed(2)
                    font.pixelSize: 18
                }

                Text {
                    id: vlotageTtile
                    text: qsTr("Vlotage(V)")
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
        }

        Rectangle{
            id:currentRec
            color: "#FFFAFA"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: votageRec.height
            radius: 4
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: currentValue
                    text: SimuDeviceHandle.deviceData.current.toFixed(2)
                    font.pixelSize: 18
                }

                Text {
                    id: currentTtile
                    text: qsTr("Current(A)")
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
        }

        Rectangle{
            id:socRec
            color: "#FFFAFA"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: votageRec.height
            radius: 4
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: soctValue
                    text: SimuDeviceHandle.deviceData.soc.toFixed(2)
                    font.pixelSize: 18
                }

                Text {
                    id: socTtile
                    text: qsTr("Soc(%)")
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
        }

    }

    Row{
        spacing: 5
        anchors{
            top: infoRow.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }
        Button{
            text: qsTr("Record")
            width: 100
            height: 30


            onClicked: {
                SimuDeviceHandle.devieDataSave(true)
            }
        }
        Button{
            text: qsTr("Stop")
            width: 100
            height: 30

            onClicked: {
                SimuDeviceHandle.devieDataSave(false)
            }
        }
    }
}
