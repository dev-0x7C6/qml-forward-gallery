import QtGraphicalEffects 1.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Item {
    id: root

    property string source
    property double brightness: 0
    property double contrast: 0
    property double gamma: 1
    property bool stretch: false
    property alias img: img

    Image {
        id: background

        anchors.fill: parent
        source: parent.source
        smooth: false
        fillMode: Image.Stretch
        visible: false
        cache: true
    }

    FastBlur {
        id: blurBackground

        anchors.fill: parent
        source: background
        radius: 64
        visible: false
        cached: true
    }

    BrightnessContrast {
        anchors.fill: parent
        source: blurBackground
        brightness: -0.6
        cached: true
    }

    Image {
        id: img

        smooth: true
        source: root.source
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
        visible: false
    }

    BrightnessContrast {
        id: brightnessOnImage

        anchors.fill: img
        source: img
        brightness: parent.brightness
        contrast: parent.contrast
        visible: false
    }

    GammaAdjust {
        anchors.fill: background
        source: brightnessOnImage
        gamma: parent.gamma
    }

}
