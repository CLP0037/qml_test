import QtQuick 2.0
import CustomPlot 1.0

import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: plotForm

//    Text {
//        id: text
//        text: qsTr("Plot form")
//    }

//    CustomPlotItem {
//        id: customPlot
//        anchors.fill: parent

//        Component.onCompleted: initCustomPlot()
//    }






    property int modelnum:18//5

    TabBar {
          id: bar
          width: parent.width

          Repeater{
              id:tabbar_repeat
              model: modelnum
              TabButton {
                  text: qsTr("Page")+index
              }
          }
    }

    StackLayout {
        anchors.fill: parent
        anchors.topMargin: bar.height
        //width: parent.width
        currentIndex: bar.currentIndex

        Repeater{
            model:modelnum

            Item {
                id: discoverTab

                anchors.fill: parent

                RowLayout{
                    spacing: 10
                    anchors.fill: parent

                    Rectangle{
                        id:rec_01
                        anchors.fill: parent
                        anchors.rightMargin: 900
                        color: "red"

                        CustomPlotItem {
                            //id:
                            anchors.fill: parent

                            Component.onCompleted: //initCustomPlot()
                            initCustomPlot_Lines(index)
                        }
                    }

                    Rectangle{
                        id:rec_02
                        //anchors.fill: parent

                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        //anchors.left: rec_01.right
                        //anchors.leftMargin: 1
                        Layout.fillHeight: true
                        width: 900
                        color: "blue"

                        CustomPlotItem{
                            //id:
                            anchors.fill: parent
                            Component.onCompleted: initCustomPlot_CPBars(index)//tabbar_repeat.index
                        }
                    }



                }


            }
        }
    }


}
