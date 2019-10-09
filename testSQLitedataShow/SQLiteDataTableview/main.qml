import QtQuick 2.9
import QtQuick.Window 2.2

import QtQuick.Controls 1.4 as QC14

//import QtQuick.Controls.tyles 1.1
import QtQuick.Layouts 1.1

import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import QtQml 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    TabBar {
        id:tabbar
        width: parent.width
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        height: 40
        font.pointSize: 10
        //color:"#778899"
        background: Rectangle {
                //color: "#778899"//"#7A8B8B"
            gradient: Gradient {
                  GradientStop { position: 0.0; color: "lightsteelblue" }
                  GradientStop { position: 1.0; color: "steelblue" }
        }
            }

        TabButton {
            //id:

            text: qsTr("录波历史文件信息")
            width: 120
            height: 40
        }
        TabButton {
            //id:

            text: qsTr("系统设置_通道配置")
            width: 120
            height: 40
        }
        TabButton {
            //id:

            text: qsTr("测试")
            width: 120
            height: 40
        }

        TabButton {
            //id:

            text: qsTr("录波模拟通道配置")
            width: 120
            height: 40
        }


    }

    StackLayout {
        currentIndex: tabbar.currentIndex
        anchors.bottom:  tabbar.top
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0


        QC14.TableView {
            id: tableView_wr_comtradehistory

            //horizontalScrollBarPolicy: 1
            anchors.fill: parent
            model: modelComtradefile


            QC14.TableViewColumn {
                id: seqnum
                role: "seqnum"
                title: qsTr("序号")
                width: 90
            }

            QC14.TableViewColumn {
                id: fname
                role: "fname"
                title: qsTr("文件名")
                width: 90
            }

            QC14.TableViewColumn {
                id: ftime
                role: "ftime"
                title: qsTr("故障时间")
                width: 90
            }

            QC14.TableViewColumn {
                id: ftype
                role: "ftype"
                title: qsTr("故障类型")
                width: 90
            }

            QC14.TableViewColumn {
                id: fcause
                role: "fcause"
                title: qsTr("录波原因")
                width: 90
            }

            QC14.TableViewColumn {
                id: fsize
                role: "fsize_dat"
                title: qsTr("文件大小")
                width: 90
            }

            rowDelegate: Rectangle {
                height: 40
                color: styleData.selected ? 'lightsteelblue' : 'white';
                MouseArea{//鼠标事件
                    //anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        tableView_wr_comtradehistory.selection.clear()
                        tableView_wr_comtradehistory.selection.select(styleData.row)
                        tableView_wr_comtradehistory.currentRow = styleData.row ? styleData.row : 0
                        tableView_wr_comtradehistory.focus = true
                        switch(mouse.button) {
                        case Qt.RightButton:
                            //contextTaskMenu.popup()
                            break
                        default:
                            break
                        }
                    }
                    onDoubleClicked: {
                        //切换到波形分析界面进行显示

                    }
                }
            }




        }

        QC14.TableView {//系统设置 通道基本参数
            id: tableView_sys_channelinfo

            //horizontalScrollBarPolicy: 1
            anchors.fill: parent
            model: modelChannelinfo


            QC14.TableViewColumn {
                id: table_sysci_column01
                role: "channel_name"
                title: qsTr("模拟通道名称")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_sysci_column02
                role: "sys_cproperty"
                title: qsTr("通道属性")
                width: 90


            }

            QC14.TableViewColumn {
                id: table_sysci_column03
                role: "sys_cphase"
                title: qsTr("通道相别")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_sysci_column04
                role: "sys_clinenum"
                title: qsTr("线路号")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_sysci_column05
                role: "sys_cratedvalue"
                title: qsTr("额定值")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_sysci_column06
                role: "sys_cratio"
                title: qsTr("变比")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_sysci_column07
                role: "sys_crange"
                title: qsTr("量程")
                width: 90
            }



            rowDelegate: Rectangle {
                height: 40
                width: parent.width
                color: styleData.selected ? 'lightsteelblue' : 'white';
                MouseArea{//鼠标事件
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        tableView_sys_channelinfo.selection.clear()
                        tableView_sys_channelinfo.selection.select(styleData.row)
                        tableView_sys_channelinfo.currentRow = styleData.row ? styleData.row : 0
                        tableView_sys_channelinfo.focus = true
                        switch(mouse.button) {
                        case Qt.RightButton:
                            //contextTaskMenu.popup()
                            break
                        default:
                            break
                        }
                    }
                    onDoubleClicked: {
                        dialog_syschannelinfo.combo_refresh()
                        dialog_syschannelinfo.open()
                    }
                }
            }




        }

        QC14.TableView {
            id: tableView03

            anchors.fill: parent
            model: modelComtradefile


            QC14.TableViewColumn {
                id: table03_column01
                role: "fexistflag"
                title: qsTr("文件是否存在")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            //state: (styleData.value === 1)?Qt.Checked:Qt.Unchecked
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            //text: qsTr("状态")+styleData.value
                            text: String(modelComtradefile.get(styleData.row).fname)
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table03_column02
                role: "fpath"
                title: qsTr("文件路径")
                width: 90

            }

            QC14.TableViewColumn {
                id: table03_column03
                role: "ftype"
                title: qsTr("故障类型")
                width: 90
                delegate: Rectangle {
                    //anchors.fill: parent
                    //anchors.verticalCenter: parent.verticalCenter
                    ComboBox {
                        anchors.fill: parent
                        anchors.margins: 2
                        //currentIndex :find("333",Qt.MatchContains)
                        model: ListModel {
                            id: comboModel
                            ListElement {  text: "111" }
                            ListElement {  text: "222" }
                            ListElement {  text: "333" }
                            ListElement {  text: "444" }
                        }

                        Component.onCompleted: {
                            var ttt = "123"
                            switch(styleData.row)
                            {
                             case 0:ttt = "111";break;
                             case 1:ttt = "222";break;
                             case 2:ttt = "333";break;
                             case 3:ttt = "444";break;
                             case 4:ttt = "555";break;
                             case 5:ttt = "666";break;
                            }
                              currentIndex = find(ttt);
                            if(currentIndex<0)
                                currentIndex = 0
                            else
                              comboModel.get(currentIndex).text = ttt

                        }
                    }
                }
            }



            rowDelegate: Rectangle {
                height: 40
                color: styleData.selected ? 'lightsteelblue' : 'white';
                MouseArea{//鼠标事件
                    //anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        tableView03.selection.clear()
                        tableView03.selection.select(styleData.row)
                        tableView03.currentRow = styleData.row ? styleData.row : 0
                        tableView03.focus = true
                        switch(mouse.button) {
                        case Qt.RightButton:
                            //contextTaskMenu.popup()
                            break
                        default:
                            break
                        }
                    }
                    onDoubleClicked: {
                        //dialogTaskView.defval()
                        //dialogTaskView.open()
                    }
                }
            }




        }

        QC14.TableView {//录波设置  模拟通道参数
            id: tableView_wr_analogchannel

            //horizontalScrollBarPolicy: 1
            anchors.fill: parent
            model: modelChannelinfo


            QC14.TableViewColumn {
                id: table_wrac_column01
                role: "channel_name"
                title: qsTr("模拟通道名称")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_wrac_column02
                role: "analog_uperlimitflag"
                title: qsTr("越上限触发")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false

                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_uperlimitvalue).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column03
                role: "analog_lowerlimitflag"
                title: qsTr("越下限触发")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false

                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_lowerlimitvalue).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column04
                role: "analog_mutationflag"
                title: qsTr("突变定值触发")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_mutationvalue).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column05
                role: "analog_mutationpolarity"
                title: qsTr("突变极性")
                width: 90
            }

            QC14.TableViewColumn {
                id: table_wrac_column06
                role: "analog_harmonicflag_2"
                title: qsTr("二次谐波")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_harmonicvalue_2).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column07
                role: "analog_harmonicflag_3"
                title: qsTr("三次谐波")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_harmonicvalue_3).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column08
                role: "analog_harmonicflag_5"
                title: qsTr("五次谐波")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_harmonicvalue_5).toLocaleString()
                        }
                    }

                }
            }

            QC14.TableViewColumn {
                id: table_wrac_column09
                role: "analog_harmonicflag_7"
                title: qsTr("七次谐波")
                width: 90

                delegate: Rectangle {
                     Component.onCompleted: {
                         //console.log("styleData.row:"+styleData.row+",styleData.value:"+styleData.value)
                     }

                    RowLayout{
                        spacing: 0

                        CheckBox{
                            checked:(styleData.value === 1)?true:false
                        }
                        Label{
                            text: Number(modelChannelinfo.get(styleData.row).analog_harmonicvalue_7).toLocaleString()
                        }
                    }

                }
            }



            rowDelegate: Rectangle {
                width: parent.width
                height: 40
                color: styleData.selected ? 'lightsteelblue' : 'white';
                MouseArea{//鼠标事件
                    anchors.fill: parent
                    acceptedButtons: Qt.RightButton | Qt.LeftButton
                    onClicked: {
                        //console.log("single click table tableView_wr_analogchannel")
                        tableView_wr_analogchannel.selection.clear()
                        tableView_wr_analogchannel.selection.select(styleData.row)
                        tableView_wr_analogchannel.currentRow = styleData.row ? styleData.row : 0
                        tableView_wr_analogchannel.focus = true
                        switch(mouse.button) {
                        case Qt.RightButton:
                            //contextTaskMenu.popup()
                            break
                        default:
                            break
                        }
                    }
                    onDoubleClicked: {
                        //dialogTaskView.defval()
                        console.log("double click table tableView_wr_analogchannel")
                        dialog_wranalogchannel.combo_refresh();
                        dialog_wranalogchannel.open()
                    }
                }
            }




        }


        Dialog_WR_AnalogChannel{
            id:dialog_wranalogchannel
        }

        Dialog_SYS_ChannelInfo{
            id:dialog_syschannelinfo
        }


        }



}
