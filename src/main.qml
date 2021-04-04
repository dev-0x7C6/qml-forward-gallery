import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
	width: 640
	height: 480
	visible: true
	title: qsTr("Hello World")

	Drawer {
		id: drawer
		width: parent.width * 0.4
		height: parent.height

		ListView {
			anchors.fill: parent

			model: tokeiModel

			delegate: Text {
				required property string name
				text: name
				topPadding: 8
				bottomPadding: 8
				leftPadding: 8
				font.bold: true
				font.pixelSize: 16
			}
		}
	}

	Image {
		anchors.fill: parent
	}
}
