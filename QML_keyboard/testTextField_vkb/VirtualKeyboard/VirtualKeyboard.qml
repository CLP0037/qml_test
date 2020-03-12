import QtQuick 2.7

import "."

VirtualKeys {
	id: control

    //==padEnabled: false
    //==gameButtonsEnabled: false

    property int keyWidth: 50//Units.gu// / 2
    property int keySpacing: 3//Units.dp * 3

    //modifiers: d.shiftModifier | d.otherModifiers

    /*QtObject {
		id: d

        property int otherModifiers:
            controlKey.checked?Qt.ControlModifier:Qt.NoModifier |
            alterKey.checked?Qt.AltModifier:Qt.NoModifier
    }*///

	centerItem: Column {
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		spacing: control.keySpacing

        //1 2 3 ←
		Row {
			id: row0
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: parent.spacing

            //1
			VirtualKey {
				target: control.target
				targetHandler: null
                text: "1"
                //modifiers: d.otherModifiers
				width: control.keyWidth
			}

            //2
			VirtualKey {
				target: control.target
				targetHandler: null
                text: "2"
                //modifiers: d.otherModifiers
				width: control.keyWidth
			}

            //3
			VirtualKey {
				target: control.target
				targetHandler: null
                text: "3"
                //modifiers: d.otherModifiers
				width: control.keyWidth
			}

            //←
            VirtualKey {
                target: control.target
                targetHandler: null
                text: " ← "//space make the text len more than 1
                key: Qt.Key_Left
                //modifiers: control.modifiers
                width: control.keyWidth
                padding: 0
            }



        }

        //4 5 6 →
		Row {
			id: row1
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: parent.spacing

            //4
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "4"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //5
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "5"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //6
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "6"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //→
            VirtualKey {
                target: control.target
                targetHandler: null
                text: " → "
                key: Qt.Key_Right
                //modifiers: control.modifiers
                width: control.keyWidth
                padding: 0
            }

        }

        //7 8 9 ×
		Row {
			id: row2
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: parent.spacing

            //7
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "7"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //8
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "8"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //9
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "9"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //×(删除一位)
            VirtualKey {
                target: control.target
                targetHandler: null
                text: " × "//" ⬅ "
                key: Qt.Key_Backspace
                //modifiers: control.modifiers
                width: control.keyWidth
            }


		}

        //0 . 确定
		Row {
			id: row3
			anchors.horizontalCenter: parent.horizontalCenter
			spacing: parent.spacing

            //0
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "0"
                //modifiers: d.otherModifiers
                width: control.keyWidth
            }

            //.
            VirtualKey {
                target: control.target
                targetHandler: null
                text: "."
                key: Qt.Key_Period
                //modifiers: control.modifiers
                //modifiers: d.otherModifiers
                width: control.keyWidth
                padding: 0
            }

            //确认
            VirtualKey {
                target: control.target
                targetHandler: null
                text: " ↵ "
                key: Qt.Key_Enter
                //modifiers: control.modifiers
                width: control.keyWidth * 2 + parent.spacing
                padding: 0
            }


        }
	}
}
