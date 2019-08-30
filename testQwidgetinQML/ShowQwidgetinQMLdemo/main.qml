import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    //title: qsTr("Hello World")
//    property alias titleBar: title

//    Rectangle
//        {
//            id:title
//            width: parent.width
//            height:25
//            color: "gray"
//            Text
//            {
//                anchors.centerIn: parent
//                text: "title: hello widget"
//                font.bold: true
//            }
//        }

    Rectangle{
            id:qmlRec
            height: 180
            width: 180
            x:180
            color: "dimgray"
            Text {
                id: label
                height: 40
                width: 140
                y:10
                text: qsTr("this is qmlRec")
            }
            Rectangle{
                id:inputText
                height:20
                width: 100
                x:2
                border.color: "white"
                y:50
                color: "lightgray"
                TextInput{
                    height: parent.height
                    width: parent.width
                    x:2
                    y:4
                }
            }
            Rectangle{
                id:sendeBtn
                height: 20
                width: 60
                x:100
                y:100
                border.color: "lightgray"
                border.width: 1
                color: sendeBtnMosue.containsMouse?"#008792":"darkgray"
                Text {
                    id: sendeBtnLabel
                    text: qsTr("send")
                    anchors.centerIn: parent
                }
                MouseArea{
                    id:sendeBtnMosue
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked: {
                        console.log("sendBtn Clicked")
                    }
                }
            }

    }
}
