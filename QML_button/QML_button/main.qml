import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Column{
        anchors.topMargin: 20
        anchors.leftMargin: 20
        spacing: 20

        QmlButton_Text{
            width:80
            height:40

            text:qsTr("文本按钮")
            property color btnColor:"#4682B4"//"#009688"
            color: containsPress ? Qt.darker(btnColor, 1.2) : (containsMouse ? Qt.lighter(btnColor, 1.2) : btnColor)
            onClicked:{

            }
        }

        QmlButton_Text{
            width:120
            height:40
            radius:5
            text:qsTr("圆角文本按钮")
            textColor:"white"
            textfontSize:12
            property color btnColor:"#4682B4"//"#009688"
            property color btnBorderColor:"lightblue"
            color: containsPress ? Qt.darker(btnColor, 1.2) : (containsMouse ? Qt.lighter(btnColor, 1.2) : btnColor)
            border.width: containsMouse ? 2 : 0 //鼠标悬浮时有宽度，才能看到边框
            border.color: btnBorderColor
            onClicked:{

            }
        }

    }






}
