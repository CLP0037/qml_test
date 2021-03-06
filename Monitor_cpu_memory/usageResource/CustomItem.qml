import QtQuick 2.0

Item {
    property int p_min: 0
    property int p_max: 100
    property int p_cur: 0
    property int p_interval: 20

    signal fps(int target, int actual)

    Timer {
        id: id_timer
        repeat: true
        interval: p_interval
        running: true

        onTriggered: {
            if(p_cur == p_max){
                p_cur = p_min
            }
            p_cur++
        }
    }
}
