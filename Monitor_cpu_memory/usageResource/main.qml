import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.5
import SysInfoQML 1.0



Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    property int p_cpuUsage: 0
    property int p_memUsage: 0

    Text{
        x: 220
        y: 10
        text: {
            return "CPU Usage " + p_cpuUsage + "%"
        }
    }

    ProgressBarWidget {
        id:cpuUsageBar
        x: 10
        y: 10
        width: 200
        height: 30
    }

    Text{
        x: 220
        y: 50
        text: {
            return "MEM Usage " + p_memUsage +"%"
        }
    }

    ProgressBarWidget {
        id:memUsageBar
        x: 10
        y: 50
        width: 200
        height: 30
    }

    SysInfoQML {
        id: id_sysInfo
    }

    Timer{
        repeat: true
        interval: 1000
        running: true

        onTriggered: {
            id_sysInfo.update()
            p_cpuUsage = id_sysInfo.cpuUsage
            p_memUsage = id_sysInfo.memUsage * 100 / id_sysInfo.memTotal
            cpuUsageBar.p_usage = id_sysInfo.cpuUsage
            memUsageBar.p_usage = id_sysInfo.memUsage * 100 / id_sysInfo.memTotal
        }
    }

    Button {
        id: button
        x: 20
        y: 123
        width: 185
        height: 37
        text: qsTr("重启")

        onClicked: {
            id_sysInfo.reBoot()
        }
    }

    Button {
        id: button1
        x: 25
        y: 194
        width: 185
        height: 37
        text: qsTr("关机")

        onClicked: {
            dialog_shutdown.open()
            //id_sysInfo.shutDown()
        }
    }

    Dialog{
        id:dialog_shutdown
        width: parent.width*0.3
        height: parent.height*0.3
        x:(parent.width - width) / 2
        y:(parent.height - height) / 2
        closePolicy: "NoAutoClose"
        modal: true
        standardButtons: Dialog.Ok | Dialog.Cancel

        Text {
            text: qsTr("确定重启吗？")
            anchors.centerIn: parent
        }

        onAccepted: {
            id_sysInfo.shutDown()
            dialog_shutdown.close()
        }
        onClosed: {
            dialog_shutdown.close()
        }
    }

}
