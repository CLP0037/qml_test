import QtQuick 2.9
import QtQuick.Window 2.2
//import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import "./VirtualKeyboard"
//import VirtualKey 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    ColumnLayout{
        spacing: 20
        //anchors.margins: 20


        TextField_vkb{
            //anchors.centerIn: parent

            onFocusChanged: {//失去焦点隐藏显示
                if(!focus)
                {
                    vkb_flag_hide = true
                    console.log("1 focus change to false")
                }
                else
                {
                    console.log("1 focus change to true")
                }
            }

            onActiveFocusChanged: {
                if(!activeFocus)
                {
                    vkb_flag_hide = true
                    console.log("1 activeFocus change to false")
                }
                else
                {
                    console.log("1 activeFocus change to true")
                }
            }

        }

        TextField_vkb{
            height: 50
            width: 300
            //anchors.centerIn: parent
            txt_isNum:false



        }


    }


}
