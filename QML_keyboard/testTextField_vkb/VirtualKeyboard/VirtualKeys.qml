import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

import "Private"
import "."

//import "./Private/utils.js" as Utils

Item  {
	id: vkeys

    anchors.fill: parent
	property Item target: root
	property var targetHandler: null

	property alias color: controls.color
	property bool useOpenGL: false

    //property int modifiers

	property alias centerItem: controls.centerItem



	Rectangle {
		id: controls
        radius: 5
        height: 50*4+3*5//200
//		height: Units.dp * 16 + Math.max(centerItem.height,
//				Math.max(vkeys.padEnabled?virtualpad.height:0,
//						vkeys.gameButtonsEnabled?gameButtons.height:0)
//		)

        //anchors.left: parent.left
        //anchors.right: parent.right
        //anchors.bottom: parent.bottom

        //正下方左对齐
        //x:vkeys.target.x//vkeys.target.x+300
        //y:vkeys.target.y+vkeys.target.height+2
        //右边上对齐
        x:vkeys.target.x+vkeys.target.width+2
        y:vkeys.target.y //+vkeys.target.height+2
        //height: 300
        width: 50*4+3*5//350

		property alias target: vkeys.target
		property alias targetHandler: vkeys.targetHandler
        //property alias modifiers: vkeys.modifiers

		property Item centerItem: Item {}

        //opacity: 0.8//(vkeys.height-y)/height
        clip: false//opacity > 0 && color.a > 0
		color: Material.backgroundColor


	}


	function setCenterItemCenter() {
		if (!centerItem) return;
		var r = 0;
        //==if (padEnabled)
        //==	r += virtualpad.width;
        //==if (gameButtonsEnabled)
        //==	r -= gameButtons.width;
			centerItem.anchors.horizontalCenterOffset = r/2;
	}

	onCenterItemChanged: setCenterItemCenter()

	Component.onCompleted: {
		centerItem.parent = controls;

		console.log("VirtualKeys.targetHandler:", targetHandler);
	}
}
