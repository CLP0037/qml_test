import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import DevDataTransfer_wr 1.0

Window {
    visible: true
    width: 800//640
    height: 600//480
    title: qsTr("DataTransfer")

    ColumnLayout{

        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("   TCP   ")
            }

            Label{
                text: qsTr("IP：")
            }
            TextField{
               id:txt_ip
               text:"192.168.4.30"  //"127.0.0.1" //
            }
            Label{
                text: qsTr("Port：")
            }
            TextField{
               id:txt_port
               text: "2404"
            }

            Button{
               text: qsTr("连接")
               onClicked: {
                   //"127.0.0.1"
                   //"192.168.4.30"
                   //dev_wr.clientConnect(txt_ip.text, Number(txt_port.text.toString()))
                   dev_wr.clientConnect_realtime(txt_ip.text, Number(txt_port.text.toString()))
               }
            }
            Button{
               text: qsTr("断开")
               onClicked: {
                   //dev_wr.clientDisConnect()
                   dev_wr.clientDisConnect_realtime()
               }
            }
        }

        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("   UDP   ")
            }

            Label{
                text: qsTr("IP：")
            }
            TextField{
               id:txt_ip_udp
               text:"127.0.0.1" //"192.168.4.30"  //
            }
            Label{
                text: qsTr("Port：")
            }
            TextField{
               id:txt_port_udp
               text: "4010"
            }

            Button{
               text: qsTr("连接")
               onClicked: {
                   //txt_ip_udp.text, Number(txt_port_udp.text.toString())

               }
            }
            Button{
               text: qsTr("断开")
               onClicked: {


               }
            }
        }



        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("可读可设命令：")
            }

            ComboBox{
                id:combo_01
                model: [qsTr("设置"),qsTr("读取")]
                currentIndex: 1
            }

            ComboBox{
                id:combo_02
                model: [
                    qsTr("通讯参数"),
                    qsTr("设备标识"),
                    qsTr("采集通道"),
                    qsTr("最高频率"),
                    qsTr("校时方式"),
                    qsTr("时间同步"),
                    qsTr("暂态录波"),
                    qsTr("稳态录波"),

                    qsTr("开关量触发"),
                    qsTr("模拟量触发"),
                    qsTr("分组/序分量"),
                    qsTr("电能检定输入脉冲参数"),
                    qsTr("电能输出脉冲参数"),
                    qsTr("校准参数"),
                    qsTr("校准命令")]
            }

            Button{
               text: qsTr("发送")
               onClicked: {
                switch(combo_02.currentIndex)
                {
                case 0:{
                    dev_wr.wr_sendParamCommunicate(combo_01.currentIndex+1)
                }break;
                case 1:{
                    dev_wr.wr_sendParamDevInfo(combo_01.currentIndex+1)
                }break;
                case 2:{
                    dev_wr.wr_sendParamChannelInfo(combo_01.currentIndex+1)
                }break;
                case 3:{
                    dev_wr.wr_sendMaxSampleRate(combo_01.currentIndex+1,40)
                }break;
                case 4:{
                    dev_wr.wr_sendTimeCalibrationType(combo_01.currentIndex+1,0)
                }break;
                case 5:{//"yy:MM:dd:hh:mm:ss:zzz:dddd"
                    dev_wr.wr_sendTimeOperate(combo_01.currentIndex+1,qsTr("19:10:10:10:10:10:100:星期四"))
                }break;
                case 6:{
                    dev_wr.wr_sendWRParamTransient(combo_01.currentIndex+1)
                }break;
                case 7:{
                    dev_wr.wr_sendWRParamSteady(combo_01.currentIndex+1)
                }break;

                case 8:{
                    dev_wr.wr_sendWRParamSwitch(combo_01.currentIndex+1)
                }break;
                case 9:{
                    dev_wr.wr_sendWRParamAnalog(combo_01.currentIndex+1)
                }break;
                case 10:{
                    dev_wr.wr_sendWRParamComponent(combo_01.currentIndex+1)
                }break;
                case 11:{
                    dev_wr.wr_sendPowerMeterParamPulseIn(combo_01.currentIndex+1)
                }break;
                case 12:{
                    dev_wr.wr_sendPowerMeterParamPulseOut(combo_01.currentIndex+1)
                }break;
                case 13:{
                    dev_wr.wr_sendCalibrationParam(combo_01.currentIndex+1)
                }break;
                case 14:{
                    dev_wr.wr_sendCalibrationOperate(combo_01.currentIndex+1)
                }break;
                }
               }
            }

        }

        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("只读数据召测：")
            }

            ComboBox{
                id:combo_11
                model: [
                    qsTr("波形数据"),
                    qsTr("标准表实时测量数据"),
                    qsTr("开关量实时状态数据")]
            }

            Button{
               text: qsTr("发送")
               onClicked: {

                   switch(combo_11.currentIndex)
                   {
                       case 0:{

                       }break;
                       case 1:{

                       }break;
                       case 2:{

                       }break;
                       case 3:{

                       }break;

                   }
               }
            }
        }

        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("动作执行命令：")
            }

            ComboBox{
                id:combo_21
                model: [
                    qsTr("手动录波"),
                    qsTr("电能表检定"),
                    qsTr("波形数据实时传输")]
            }

            ComboBox{
                id:combo_22
                model: [qsTr("启动"),qsTr("停止")]
            }

            Button{
               text: qsTr("发送")
               onClicked: {
                   switch(combo_21.currentIndex)
                   {
                       case 0:{

                       }break;
                       case 1:{

                       }break;
                       case 2:{

                       }break;
                       case 3:{

                       }break;

                   }
               }
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

        RowLayout{
            height: 50
            spacing: 10

            Label{
                text: qsTr("监听端口：")
            }
            TextField{
               id:listen_port
               text:"4002"
            }

            Button{
               text: qsTr("启动监听")
               onClicked: {
                   dev_wr.startServer(Number(listen_port.text.toString()))//4002
               }
            }
            Button{
               text: qsTr("停止监听")
               onClicked: {
                   dev_wr.stopServer()
               }
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
