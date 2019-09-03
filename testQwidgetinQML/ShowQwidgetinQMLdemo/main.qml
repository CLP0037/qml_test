import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
//import Form01 1.0

Window {
    id: mainWindow
    visible: true
    width: 640*2
    height: 480*2
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

    TabBar {
          id: bar
          width: parent.width
          TabButton {
              text: qsTr("Home")
          }
          TabButton {
              text: qsTr("Discover")
          }
          TabButton {
              text: qsTr("Activity")
          }
      }

      StackLayout {
          width: parent.width
          currentIndex: bar.currentIndex
          Item {
              id: homeTab
              Rectangle{
                      id:qmlRec
                      height: 180
                      width: 180
                      x:180
                      y:100
                      color: "dimgray"
                      Text {
                          id: label
                          x: 95
                          height: 40
                          width: 140
                          y:15
                          text: qsTr("this is qmlRec")
                      }
                      Rectangle{
                          id:inputText
                          height:20
                          width: 100
                          x:95
                          border.color: "white"
                          y:61
                          color: "lightgray"
                          TextInput{
                              height: parent.height
                              width: parent.width
                              x:85
                              y:8
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
                                  //Widget.show();

                                  console.log("sendBtn Clicked")
                              }
                          }
                      }

              }

          }
          Item {
              id: discoverTab

              Widget_show_hide{

              }
          }
          Item {
              id: activityTab

              Mainwindow_show_hide{

              }
          }
      }


}
