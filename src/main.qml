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
            id: list

            anchors.fill: parent
            model: tokeiModel
            delegate: option
            highlight: highlightBar
            highlightFollowsCurrentItem: true
            Component.onCompleted: {
                currentIndex = 0;
            }

            Component {
                id: option

                Item {
                    width: list.width
                    height: 32

                    Text {
                        anchors.fill: parent
                        text: name
                        topPadding: 8
                        bottomPadding: 8
                        leftPadding: 8
                        font.bold: true
                        font.pixelSize: 16
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            list.currentIndex = index;
                            tokeiModel.setCurrentIndex(index);
                        }
                    }

                }

            }

            Component {
                id: highlightBar

                Rectangle {
                    anchors.fill: list.currentItem
                    color: "#FFFF88"
                }

            }

        }

    }

    Image {
        id: img

        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
    }

    Connections {
        function onImageReady(path) {
            img.source = "file://" + path;
        }

        target: tokeiModel
    }

}
