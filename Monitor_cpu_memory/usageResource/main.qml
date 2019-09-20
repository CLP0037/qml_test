import QtQuick 2.6
import QtQuick.Window 2.2
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
}
