import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
//import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3

Dialog {
    //id:
    title: qsTr("通道")+(tableView_sys_channelinfo.currentRow+1)+qsTr("参数配置：")+modelChannelinfo.get(tableView_sys_channelinfo.currentRow).channel_name
    //visible: true
    standardButtons: StandardButton.Save | StandardButton.Cancel
    height: 300




    //cancel:do nothing

    //save:save the data to sql data
     onAccepted:{
        console.log("(dialog)double click table tableView_sys_channelinfo")
         //界面数据存储至数据库
         modelChannelinfo.refreshModel_SYS(Number((tableView_sys_channelinfo.currentRow+1)).toLocaleString(),
                                           textField_channel_name.text,
                                           combo_sys_cproperty.currentText,
                                           combo_sys_cphase.currentText,
                                           combo_sys_clinenum.currentText,
                                           combo_sys_cratedvalue.currentText,
                                           textField_sys_cratio.text,
                                           textField_sys_crange.text);
         //并刷新界面
          //modelChannelinfo.updateModel_ANA();
          modelChannelinfo.updateModel();

     }

     ColumnLayout{
         spacing: 10


         //通道名称
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("  通道名称")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             TextField {
                 id: textField_channel_name
                 text: String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).channel_name)
                 width: 300
                 Layout.fillHeight: true
             }
         }

         //通道属性
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("  通道属性")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             ComboBox {
                 id:combo_sys_cproperty


                 model: ListModel {
                     id: comboModel_sys_cproperty
                     ListElement {  text: "U" }//0-U(电压)
                     ListElement {  text: "I" }//1-I(电流)
                     ListElement {  text: "DC" }//2-DC(直流量)

                 }

                 Component.onCompleted: {

                 }
             }
         }

         //通道相别
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("  通道相别")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             ComboBox {
                 id:combo_sys_cphase


                 model: ListModel {
                     id: comboModel_sys_cphase
                     ListElement {  text: "A" }//0-
                     ListElement {  text: "B" }//1-()
                     ListElement {  text: "C" }//2-()
                     ListElement {  text: "0" }
                     ListElement {  text: "-" }

                 }

                 Component.onCompleted: {

                 }
             }
         }

         //通道所属线路号
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("所属线路号")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             ComboBox {
                 id:combo_sys_clinenum


                 model: ListModel {
                     id: comboModel_sys_clinenum
                     ListElement {  text: "1" }//0-
                     ListElement {  text: "2" }//1-()
                     ListElement {  text: "3" }//2-()
                     ListElement {  text: "4" }


                 }

                 Component.onCompleted: {

                 }
             }
         }

         //通道额定值   ======若下拉选择，选择范围待确定
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("通道额定值")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             ComboBox {
                 id:combo_sys_cratedvalue


                 model: ListModel {
                     id: comboModel_sys_cratedvalue
                     ListElement {  text: "111" }//0-
                     ListElement {  text: "222" }//1-()
                     ListElement {  text: "333" }//2-()
                     ListElement {  text: "444" }


                 }

                 Component.onCompleted: {

                 }
             }
         }

         //通道变比
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("  通道变比")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             TextField {
                 id: textField_sys_cratio
                 text: String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).sys_cratio)
                 width: 300
                 Layout.fillHeight: true
             }
         }

         //通道量程
         RowLayout{
             spacing: 10

             Label{

                text: qsTr("  通道量程")
                color:  "#148014"//"#AA0000" //
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

             }

             TextField {
                 id: textField_sys_crange
                 text: String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).sys_crange)
                 width: 300
                 Layout.fillHeight: true
             }
         }

     }





     function combo_refresh()
     {
         //combo_sys_cproperty
         //combo_sys_cphase
         //combo_sys_clinenum
         //combo_sys_cratedvalue
         var ttt1 = String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).sys_cproperty)
         var ttt2 = String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).combo_sys_cphase)
         var ttt3 = String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).combo_sys_clinenum)
         var ttt4 = String(modelChannelinfo.get(tableView_sys_channelinfo.currentRow).combo_sys_cratedvalue)
         console.log(qsTr("当前行：")+tableView_sys_channelinfo.currentRow
                     +"，对应数据库中通道属性："+String(ttt1)
                     +"，对应数据库中通道相别："+String(ttt2)
                     +"，对应数据库中通道线路号："+String(ttt3)
                     +"，对应数据库中通道量程："+String(ttt4))

         combo_sys_cproperty.currentIndex = combo_sys_cproperty.find(ttt1);
         if(combo_sys_cproperty.currentIndex<0)
             combo_sys_cproperty.currentIndex = 0
         else
           comboModel_sys_cproperty.get(combo_sys_cproperty.currentIndex).text = ttt1

         combo_sys_cphase.currentIndex = combo_sys_cproperty.find(ttt2);
         if(combo_sys_cphase.currentIndex<0)
             combo_sys_cphase.currentIndex = 0
         else
           comboModel_sys_cphase.get(combo_sys_cphase.currentIndex).text = ttt2

         combo_sys_clinenum.currentIndex = combo_sys_clinenum.find(ttt3);
         if(combo_sys_clinenum.currentIndex<0)
             combo_sys_clinenum.currentIndex = 0
         else
           comboModel_sys_clinenum.get(combo_sys_clinenum.currentIndex).text = ttt3

         combo_sys_cratedvalue.currentIndex = combo_sys_cratedvalue.find(ttt4);
         if(combo_sys_cratedvalue.currentIndex<0)
             combo_sys_cratedvalue.currentIndex = 0
         else
           comboModel_sys_cratedvalue.get(combo_sys_cratedvalue.currentIndex).text = ttt4

     }


}
