import QtQuick 2.9
import QtQuick.Window 2.2

import QtQuick.Controls 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Test serialport info")

    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 10

        ComboBox {
            id: serialPorts
            width: 100
            model: portsNameModel
        }

        ComboBox {
            id: baudRate
            width: 100
            model: baudsModel
        }

        Button {

            id: testBtn
            text: qsTr("测试")
            onClicked: {
                console.log("串口号："+serialPorts.currentText+"；波特率："+baudRate.currentText)
            }
        }
    }



}
