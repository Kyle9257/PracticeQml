import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

Item {
    id: root

    RowLayout{
        id: infoRow
        width: parent.width * 0.95
        height: 70
        spacing: 5
        anchors{
            top: parent.top
            topMargin: 10
            horizontalCenter: parent.horizontalCenter
        }
        Rectangle{
            id:votageRec
             color: "blue"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: parent.height
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: voltageValue
                    text: DeviceHandler.deviceData.voltage
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
             color: "blue"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: parent.height
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: currentValue
                    text: DeviceHandler.deviceData.current.toFixed(2)
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
            color: "blue"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredWidth: (parent.width - 2*infoRow.spacing) / 3
            Layout.preferredHeight: parent.height
            Column{
                anchors.centerIn: parent
                spacing: 5
                Text {
                    id: soctValue
                    text: DeviceHandler.deviceData.soc
                    font.pixelSize: 18
                }

                Text {
                    id: socTtile
                    text: qsTr("Soc")
                    font.pixelSize: 12
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
        }

    }

}
