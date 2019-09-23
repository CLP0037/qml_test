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

        Button{
           text: qsTr("sendParamCommunicate")
           onClicked: {
               dev_wr.wr_sendParamCommunicate(2,
                                              "COM1",9600,0,
                                              "COM2",9600,0)
           }
        }

    }



    DevDataTransfer_wr{
        id:dev_wr
    }


}
