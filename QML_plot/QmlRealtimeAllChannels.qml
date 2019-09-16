import QtQuick 2.0
import CustomPlot 1.0

import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id:realtime_show
    anchors.fill: parent
    property int channel_nums: 4 //可见页面显示的通道个数
    property int channel_height_one:realtime_show.height/channel_nums
    property int channel_height_all:get_channelheight_all()
    //property list model_channelflag :


    property int channel_totalnum:18//18个通道

    Flickable{
        anchors.fill: parent
        contentHeight: channel_height_all
        contentWidth: parent.width
        //clip:true
        flickableDirection: Flickable.VerticalFlick

    Column {
        anchors.fill: parent
        spacing: 0



        Repeater {
            model: 18

            Rectangle{
                id: rect
                width: parent.width > 1500 ? parent.width : 1500//1500
                height: channel_height_one
                color: "#778899"

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


    function get_channelheight_all()
    {

        return channel_height_one*18
    }

//    function fresh_model_channelflag()
//    {
//        var list_channelflag;
//        list_channelflag.clear();
//        for(var i=0;i<channel_totalnum;i++)
//        {
//            list_channelflag.append(1);
//            console.log("list_channelflag"+i+":"+list_channelflag[i])
//        }
//    }

Component.onCompleted: {
    //fresh_model_channelflag()
//          console.log("Name of first state:", states[0].name)
//          for (var i = 0; i < states.length; i++)
//              console.log("state", i, states[i].name)
      }
}
