import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    function updateTime() {
        title.text = controller.time();
    }

    Rectangle {
        anchors.fill: parent
        width: parent.width
        color: "black"
        opacity: 0.7
    }

    Label {
        id: title

        anchors.fill: parent
        font.pixelSize: parent.height / 2
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: updateTime()
        Component.onCompleted: updateTime()
    }

}
