import QtQuick 2.0

CustomItem {
    id: id_root

    property int p_usage: 0

    Rectangle {
        id: id_rec1
        border.color: "black"
        border.width: 1

        anchors {
            left: id_root.left
            right: id_root.right
            verticalCenter: id_root.verticalCenter
            leftMargin: id_root.width * 0.01
            rightMargin: id_root.width * 0.01
        }
        height: id_root.height

        color: "white"
    }

    Rectangle {
        id: id_rec2

        anchors {
            left: id_rec1.left
            top: id_rec1.top
            bottom: id_rec1.bottom
            margins: id_rec1.height * 0.1
        }
        width: p_usage * id_rec1.width / id_root.p_max

        color: "black"
    }
}
