import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    id: root

    property bool stretch: controller.stretch()

    function updateTime() {
        title.text = controller.time();
    }

    function next() {
        img.source = controller.next();
    }

    function prev() {
        img.source = controller.prev();
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
        next();
    }

    Image {
        id: background

        anchors.fill: parent
        source: img.source
        smooth: false
        fillMode: Image.Stretch
        visible: !stretch
    }

    FastBlur {
        id: blurBackground

        anchors.fill: background
        source: background
        radius: 32
        visible: !stretch
    }

    BrightnessContrast {
        anchors.fill: background
        source: blurBackground
        brightness: -0.6
    }

    Image {
        id: img

        smooth: true
        onSourceChanged: nextImageTimer.restart()
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
                next();

            if (event.key === Qt.Key_Back)
                prev();

            if (event.key === Qt.Key_Space)
                next();

            if (event.key === Qt.Key_Left)
                prev();

            if (event.key === Qt.Key_Right)
                next();

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

    BrightnessContrast {
        id: effect

        anchors.fill: img
        source: img
        brightness: (brightness.value * 2) - 1
        contrast: (contrast.value * 2) - 1
    }

    GammaAdjust {
        anchors.fill: background
        source: effect
        gamma: gamma.value
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

        interval: controller.timeout()
        running: true
        repeat: true
        onTriggered: next()
    }

}
