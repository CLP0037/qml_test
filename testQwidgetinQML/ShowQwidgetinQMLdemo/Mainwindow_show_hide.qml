import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    anchors.top: parent.top
    anchors.topMargin: 50

    RowLayout{
        spacing: 20

        Button{
            text: qsTr("显示")
            onClicked: {
                //Widget.show()
                Mainwindow.showFullScreen()
            }
        }

        Button{
            text: qsTr("关闭")
            onClicked: {
                Mainwindow.close()
            }
        }
    }

}
