import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    id: root

    property int index: -1
    property bool stretch: database.stretch()

    function updateTime() {
        title.text = database.time();
    }

    function updateImage(delta = 1) {
        index += delta;
        if (index >= database.count())
            index = 0;

        if (index < 0)
            index = database.count() - 1;

        img.source = "file://" + database.path(index);
        nextImageTimer.restart();
    }

    function toggleFullscreen() {
        if (visibility === Window.FullScreen)
            showNormal();
        else
            showFullScreen();
    }

    width: 800
    height: 800 * (9 / 16)
    visible: true
    color: "black"
    title: qsTr("qml-forward-gallery")
    Component.onCompleted: {
        updateTime();
        updateImage();
    }

    Image {
        id: background

        anchors.fill: parent
        source: img.source
        fillMode: Image.Stretch
        visible: !stretch
    }

    FastBlur {
        anchors.fill: background
        source: background
        radius: 64
        visible: !stretch
    }

    Image {
        id: img

        anchors.fill: parent
        fillMode: stretch ? Image.Stretch : Image.PreserveAspectFit
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_F11)
                toggleFullscreen();

            if (event.key === Qt.Key_F)
                toggleFullscreen();

            if (event.key === Qt.Key_S)
                stretch = (!stretch);

            if (event.key === Qt.Key_Forward)
                updateImage();

            if (event.key === Qt.Key_Back)
                updateImage(-1);

            if (event.key === Qt.Key_Space)
                updateImage();

            if (event.key === Qt.Key_Left)
                updateImage(-1);

            if (event.key === Qt.Key_Right)
                updateImage();

        }
    }

    Drawer {
        id: bottomDrawer

        edge: Qt.BottomEdge
        dragMargin: 100
        width: parent.width
        height: parent.height * 0.5
        onAboutToHide: img.focus = true

        ColumnLayout {
            anchors.fill: parent

            Slider {
                id: brightness

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                value: 0
            }

            Slider {
                id: contrast

                Layout.fillWidth: true
                Layout.preferredHeight: 50
                value: 0
            }

        }

    }

    BrightnessContrast {
        id: effect

        anchors.fill: img
        source: img
        brightness: brightness.value
        contrast: contrast.value
    }

    Rectangle {
        id: bar

        anchors.top: img.top
        height: 50
        width: parent.width
        color: "black"
        opacity: 0.7
    }

    Label {
        id: title

        anchors.fill: bar
        font.pixelSize: bar.height / 2
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: updateTime()
    }

    Timer {
        id: nextImageTimer

        interval: database.timeout()
        running: true
        repeat: true
        onTriggered: updateImage()
    }

}
