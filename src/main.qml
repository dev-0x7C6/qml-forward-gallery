import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    id: root

    property bool stretch: controller.stretch()

    function next() {
        scene.source = controller.next();
    }

    function prev() {
        scene.source = controller.prev();
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
    }

    Scene {
        id: scene

        anchors.fill: parent
        img.onSourceChanged: next_image_timer.restart()
        brightness: display_settings.brightness * 2 - 1
        contrast: display_settings.contrast * 2 - 1
        gamma: display_settings.gamma
        Component.onCompleted: next()

        Timer {
            id: next_image_timer

            interval: controller.timeout()
            running: true
            repeat: true
            onTriggered: next()
        }

    }

    ClockBar {
        anchors.top: parent.top
        width: parent.width
        height: parent.height * 0.1
    }

    DisplaySettingsDrawer {
        id: display_settings

        brightness: controller.display_brightness
        contrast: controller.display_contrast
        gamma: controller.display_gamma
        onBrightnessChanged: controller.display_brightness = brightness
        onContrastChanged: contrast.display_contrast = contrast
        onGammaChanged: contrast.display_gamma = gamma
        anchors.fill: parent
    }

}
