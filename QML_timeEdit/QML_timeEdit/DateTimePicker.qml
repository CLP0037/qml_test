import QtQuick 2.6

Rectangle {
    id: pickerArea
    width: 100
    height: 200
    color: "#ecf0f1"
    opacity: 0.8
    clip: true

    property var modelPicker: 10
    property var currentTime: 0
    property var offsetTime: 0

    function isNumber(n) {
        return !isNaN(parseFloat(n)) && isFinite(n);
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.01
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 3 - height / 2
        color: "#1abc9c"
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.01
        anchors.horizontalCenter: parent.horizontalCenter
        y: 2 * parent.height / 3 - height / 2
        color: "#1abc9c"
    }

    PathView {
        id: dateScroll
        anchors.horizontalCenter: pickerArea.horizontalCenter
        anchors.verticalCenter: pickerArea.verticalCenter
        width: pickerArea.width
        height: pickerArea.height
        currentIndex: isNumber(modelPicker) ? currentTime - offsetTime - 3 : currentTime - 2

        model: isNumber(modelPicker) ? modelPicker - offsetTime : modelPicker

        delegate: Item {
            width: pickerArea.width
            height: pickerArea.height

            Text {
                id: textPicker
                anchors.centerIn: parent
                font.family: "Ubuntu"
                font.bold: true
                font.pixelSize: 18
                color: "#2c3e50"
                text: isNumber(modelPicker) ? modelData + 1 + offsetTime : modelData
            }
        }

        path: Path {
            startX: pickerArea.width / 2
            startY: - pickerArea.height / 6
            PathLine {
                x: pickerArea.width/2
                y: isNumber(modelPicker) ? (modelPicker - offsetTime) * pickerArea.height / 3 : modelPicker.length * pickerArea.height / 3
            }
        }
    }
}
