
import QtQuick 2.6
import QtQuick.Controls 1.4

ApplicationWindow {
    id: root
    visible: true
    width: 250
    height: 50
    flags: Qt.FramelessWindowHint

    MouseArea {
        anchors.fill: parent
        property int mx: 0
        property int my: 0
        onPressed: {
            mx=mouseX
            my=mouseY
        }
        onPositionChanged: {
            root.x+=mouseX-mx
            root.y+=mouseY-my
        }
    }
    Row {
        Rectangle {
            id: rcpu
            width: root.width/5
            height: root.height
            color: "red"
            property double ratio: 0
            Rectangle{
                anchors.bottom: parent.bottom
                width: parent.width
                height: parent.ratio*parent.height
                color: "blue"
            }
            Text {
                id: cpuTitle
                text: "CPU"
                y: 8
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                text: (parent.ratio*100).toFixed(1)+"%"
                anchors.top:cpuTitle.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
    Timer {
        repeat: true
        running: true
        property int workTime: 0
        property int totalTime: 0
        onTriggered: {
            var xhr = new XMLHttpRequest()
            //CPU
            xhr.open("GET","file:///proc/stat",false)
            xhr.send()
            var cpu=xhr.responseText.split("\n")[0].split(/\s+/)
            var add=function(sum,v){
                return sum+v
            }
            var wtime=cpu.slice(1,4).map(Number).reduce(add)
            var ttime=cpu.slice(1,9).map(Number).reduce(add)
            var c=(wtime-workTime)/(ttime-totalTime)
            console.log("CPU利用率",c)
            rcpu.ratio=c
            workTime=wtime
            totalTime=ttime
        }
    }
}




//import QtQuick 2.9
//import QtQuick.Window 2.2
//import QtQml 2.2
//import QtQuick.Controls 2.2
//import QtQuick.Controls.Styles 1.3
//import QtQuick.Layouts 1.3

//Window {
//    visible: true
//    width: 640
//    height: 480
//    title: qsTr("Hello World")

//    property int dates
//    property int months
//    property int years

//    function timeChanged() {
//        var date = new Date
//        dates = date.getUTCDate()
//        months = date.getUTCMonth()
//        years = date.getUTCFullYear()
//    }

//    Timer {
//        interval: 1000; running: true; repeat: true
//        onTriggered: {
//            timeChanged()
//        }
//    }

//    RowLayout{
//        spacing: 10
//        id:row
//        height: 40

//        TextField{
//            id:textEdit
//            width:300//rect.width-25
//            height:40//rect.height-2

//            inputMask: "9999/99/99 99:99:99:999"
//            validator: RegExpValidator { regExp: /^(((([0\s][1-9\s]|[1\s][0-9\s]|[2\s][0-8\s])[\/]([0\s][1-9\s]|[1\s][012\s]))|((29|30|31)[\/]([0\s][13578\s]|[1\s][02\s]))|((29|30)[\/]([0\s][4,6,9]|11)))[\/]([19\s[2-9\s][0-9\s])\d\d|(^29[\/]02[\/]([19\s]|[2-9\s][0-9\s])(00|04|08|12|16|20|24|28|32|36|40|44|48|52|56|60|64|68|72|76|80|84|88|92|96)))\s([0-1\s]?[0-9\s]|2[0-3\s]):([0-5\s][0-9\s]):([0-5\s][0-9\s])$/}



//        }

//        Button{
//            onClicked: {
//                sel_calendar.visible = !(sel_calendar.visible)
//            }
//        }
//    }



//    Calendar {
//        id:sel_calendar
//        //anchors.horizontalCenter: parent.horizontalCenter
//        anchors.left: row.left
//        anchors.top: row.bottom
//        anchors.topMargin: 2
//        month: months
//        year: years

//        visible: false
//    }




//}
