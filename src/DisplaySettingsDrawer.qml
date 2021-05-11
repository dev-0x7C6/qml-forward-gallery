import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    property alias brightness: brightness.value
    property alias contrast: contrast.value
    property alias gamma: gamma.value

    Drawer {
        // onAboutToHide: scene.img.focus = true

        id: bottomDrawer

        edge: Qt.BottomEdge
        dragMargin: 100
        width: parent.width
        height: parent.height * 0.5

        ColumnLayout {
            anchors.fill: parent

            Slider {
                id: brightness

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                value: 0.5
            }

            Slider {
                id: contrast

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                value: 0.5
            }

            Slider {
                id: gamma

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                value: 1
            }

        }

    }

}
