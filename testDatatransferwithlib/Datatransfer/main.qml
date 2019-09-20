import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import DevDataTransfer_wr 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("DataTransfer")

    ColumnLayout{
        Button{
           text: qsTr("test")
           onClicked: {
               dev_wr.test()
           }
        }
    }



    DevDataTransfer_wr{
        id:dev_wr
    }


}
