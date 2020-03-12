import QtQuick 2.0
import QtQuick.Controls 2.0

import "."

Rectangle {
    //z:9
    height: 50
    width: 200
    radius: 5

    //TextField
    property bool txt_isNum:true
    property real txt_value:0
    property string txt_value_str:""
    property color txt_bg_color:"#f9f8eb"//"grey"
    property color txt_bd_color:"#5c8d89"
    property int txt_fontsize:12

    //VirtualKeyboard
    property color vkb_bg_color:"#f9f8eb"//"green"//"#d6d7d7"
    property bool vkb_flag_hide:false
    onVkb_flag_hideChanged: {
        if(vkb_flag_hide)
        {
            vkb_flag_hide = false
            vkeys.visible = false
        }
    }


    TextField{
        //z:9
        id: root
        anchors.fill: parent



        //font.wordSpacing: 10      //设置单词之间的距离
        horizontalAlignment: Text.AlignRight //右对齐
        font.pointSize: txt_fontsize
        background: Rectangle{
            anchors.fill: parent
            color: txt_bg_color
            border.color: txt_bd_color
            //border.width: 2
            radius: 5
        }

        onPressed: {
            vkeys.visible = true; //当选择输入框的时候才显示键盘
        }
        onAccepted: {
            vkeys.visible = false;
        }

        onFocusChanged: {//失去焦点隐藏显示
            if(!focus)
            {
                //vkb_flag_hide = true
                //console.log("1 focus change to false")
            }
            else
            {
                //console.log("1 focus change to true")
            }
        }

        onActiveFocusChanged: {
            if(!activeFocus)
            {
                vkeys.visible = false;
                //vkb_flag_hide = true
                //console.log("1 activeFocus change to false")
            }
            else
            {
                //console.log("1 activeFocus change to true")
            }
        }





    }

    VirtualKeyboard {
        id: vkeys


        //z:10
        visible: false
        //active: true
        target: root
        color: vkb_bg_color
        //overlay: true //toggleOverlay.checked

        //x:target.x
        //y:target.y+100

        onVisibleChanged: {
            if(!visible)
            {
                if(txt_isNum)//数字处理
                {
                    console.log(qsTr("TextField value(before toFixed):")+root.text)
                    var real_data = Number(root.text)
                    console.log("real_data:"+real_data)
                    if(real_data.toLocaleString().toLowerCase() == "nan")
                        real_data = 0
                    if(real_data < 1000)
                    {
                        txt_value = real_data.toFixed(4)
                        root.text = txt_value.toLocaleString()
                        console.log(qsTr("TextField value(after toFixed):")+root.text)

                    }
                    else //小数直接去掉小数点4位后的数
                    {
                        var pos_dot = (root.text).indexOf(".")
                        if(pos_dot > 0)
                        {
                            var str_data = (root.text).substring(0,(pos_dot+1+4))
                            root.text = str_data
                        }
                    }


                }

                txt_value_str = root.text

            }
        }//


    }




}
