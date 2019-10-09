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
           text: qsTr("连接")
           onClicked: {
               dev_wr.clientConnect()
           }
        }
        Button{
           text: qsTr("断开")
           onClicked: {
               dev_wr.clientDisConnect()
           }
        }

        Button{
           text: qsTr("test")
           onClicked: {
               dev_wr.test()
           }
        }

        Button{
           text: qsTr("sendParamCommunicate")
           onClicked: {
               dev_wr.wr_sendParamCommunicate(2)/*,
                                              "COM1",9600,0,
                                              "COM2",9600,0)*/
           }
        }

        Button{
           text: qsTr("sendParamDevInfo")
           onClicked: {
               dev_wr.wr_sendParamDevInfo(2)
               //dev_wr.wr_sendParamDevInfo()
           }
        }



        RowLayout{
            height: 50
            spacing: 10

            Button{
                text: qsTr("通道参数(下设)")
                onClicked: {
                    dev_wr.wr_sendParamChannelInfo(1)
                }
            }
            Button{
                text: qsTr("通道参数(读取)")
                onClicked: {
                    dev_wr.wr_sendParamChannelInfo(2)
                }
             }

        }

        Button{
           text: qsTr("启动监听")
           onClicked: {
               dev_wr.startServer(4002)
           }
        }
        Button{
           text: qsTr("停止监听")
           onClicked: {
               dev_wr.stopServer()
           }
        }
        Button{
           text: qsTr("录波完成路径回复")//客户端1发送
           onClicked: {
               dev_wr.serverSendbuf_filepath(0,"C:/waveFile/test.cfg")
           }
        }
        Button{
           text: qsTr("标准表读取回复")
           onClicked: {
               //dev_wr.stopServer()
           }
        }

    }



    DevDataTransfer_wr{
        id:dev_wr
    }

    //命令发送====qml中集中在main.qml中，以便各个子页面调用
    function send_()
    {

    }










}
