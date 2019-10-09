import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
//import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Dialog {
    //id:
    title: qsTr("通道")+(tableView_wr_analogchannel.currentRow+1)+qsTr("参数配置：")+modelChannelinfo.get(tableView_wr_analogchannel.currentRow).channel_name
    //visible: true
    standardButtons: StandardButton.Save | StandardButton.Cancel
    height: 300




    //cancel:do nothing

    //save:save the data to sql data
     onAccepted:{
        console.log("(dialog)double click table tableView_wr_analogchannel")

         //界面数据存储至数据库
         modelChannelinfo.refreshModel_ANA(Number((tableView_wr_analogchannel.currentRow+1)).toLocaleString(),
                                          checkBox_analog_uperlimitvalue.checked ? "1" : "0",
                                          textField_analog_uperlimitvalue.text,
                                          checkBox_analog_lowerlimitvalue.checked ? "1" : "0",
                                          textField_analog_lowerlimitvalue.text,
                                          checkBox_analog_mutationvalue.checked ? "1" : "0",
                                          textField_analog_mutationvalue.text,
                                          combo_analog_mutationpolarity.currentText,
                                          checkBox_analog_harmonicvalue_2.checked ? "1" : "0",
                                          textField_analog_harmonicvalue_2.text,
                                          checkBox_analog_harmonicvalue_3.checked ? "1" : "0",
                                          textField_analog_harmonicvalue_3.text,
                                          checkBox_analog_harmonicvalue_5.checked ? "1" : "0",
                                          textField_analog_harmonicvalue_5.text,
                                          checkBox_analog_harmonicvalue_7.checked ? "1" : "0",
                                          textField_analog_harmonicvalue_7.text);
        //并刷新界面
         //modelChannelinfo.updateModel_ANA();
         modelChannelinfo.updateModel();

    }

     ColumnLayout{
         spacing: 10

         //越上限定值触发
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_uperlimitvalue
                 text: qsTr("  越上限定值触发")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_uperlimitvalue.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text
                     text: checkBox_analog_uperlimitvalue.text
                     font: checkBox_analog_uperlimitvalue.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_uperlimitvalue.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_uperlimitvalue
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_uperlimitvalue).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }

         //越下限定值触发
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_lowerlimitvalue
                 text: qsTr("  越下限定值触发")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_lowerlimitvalue.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_lowerlimitvalue
                     text: checkBox_analog_lowerlimitvalue.text
                     font: checkBox_analog_lowerlimitvalue.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_lowerlimitvalue.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_lowerlimitvalue
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_lowerlimitvalue).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }


         //突变量定值触发
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_mutationvalue
                 text: qsTr("  突变量定值触发")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_mutationvalue.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_mutationvalue
                     text: checkBox_analog_mutationvalue.text
                     font: checkBox_analog_mutationvalue.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_mutationvalue.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_mutationvalue
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_mutationvalue).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }

         //突变量极性选择 analog_mutationpolarity
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("    突变量极性选择")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             ComboBox {
                 id:combo_analog_mutationpolarity


                 model: ListModel {
                     id: comboModel
                     ListElement {  text: "0-正常" }
                     ListElement {  text: "1-上升沿" }
                     ListElement {  text: "2-下降沿" }

                 }

                 Component.onCompleted: {

                 }
             }
         }

         //二次谐波定值 analog_harmonicvalue_2
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_harmonicvalue_2
                 text: qsTr("  二次谐波定值")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_harmonicvalue_2.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_harmonicvalue_2
                     text: checkBox_analog_harmonicvalue_2.text
                     font: checkBox_analog_harmonicvalue_2.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_harmonicvalue_2.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_harmonicvalue_2
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_harmonicvalue_2).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }

         //三次谐波定值
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_harmonicvalue_3
                 text: qsTr("  三次谐波定值")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_harmonicvalue_3.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_harmonicvalue_3
                     text: checkBox_analog_harmonicvalue_3.text
                     font: checkBox_analog_harmonicvalue_3.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_harmonicvalue_3.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_harmonicvalue_3
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_harmonicvalue_3).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }

         //五次谐波定值
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_harmonicvalue_5
                 text: qsTr("  五次谐波定值")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_harmonicvalue_5.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_harmonicvalue_5
                     text: checkBox_analog_harmonicvalue_5.text
                     font: checkBox_analog_harmonicvalue_5.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_harmonicvalue_5.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_harmonicvalue_5
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_harmonicvalue_5).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }

         //七次谐波定值
         RowLayout{
             spacing: 10

             CheckBox {
                 id: checkBox_analog_harmonicvalue_7
                 text: qsTr("  七次谐波定值")
                 checked: true
                 //anchors.centerIn: parent
                 //spacing: 0
                 enabled: true

                 indicator:Image {
                       //id: image
                       height: 16
                       width: 16
                       anchors.verticalCenter: parent.verticalCenter
                       source: checkBox_analog_harmonicvalue_7.checked ? "qrc:/components/checked.png" : "qrc:/components/unchecked.png"
                 }

                 contentItem: Text {
                     id: text_analog_harmonicvalue_7
                     text: checkBox_analog_harmonicvalue_7.text
                     font: checkBox_analog_harmonicvalue_7.font
                     opacity: enabled ? 1.0 : 0.3
                     color: checkBox_analog_harmonicvalue_7.down ? "#AA0000" : "#148014"
                     horizontalAlignment: Text.AlignHCenter
                     verticalAlignment: Text.AlignVCenter
                     //leftPadding: checkBox.indicator.width + checkBox.spacing
                 }
             }

             TextField {
                 id: textField_analog_harmonicvalue_7
                 text: Number(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_harmonicvalue_7).toLocaleString()//qsTr("")
                 width: 300
                 Layout.fillHeight: true
             }

         }





     }







     function combo_refresh()
     {
         //combo_analog_mutationpolarity
         var ttt = String(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_mutationpolarity)
         console.log(qsTr("当前行：")+tableView_wr_analogchannel.currentRow
                     +"，对应数据库中突变量极性："+String(modelChannelinfo.get(tableView_wr_analogchannel.currentRow).analog_mutationpolarity))

           combo_analog_mutationpolarity.currentIndex = combo_analog_mutationpolarity.find(ttt);
         if(combo_analog_mutationpolarity.currentIndex<0)
             combo_analog_mutationpolarity.currentIndex = 0
         else
           comboModel.get(combo_analog_mutationpolarity.currentIndex).text = ttt
     }



}
