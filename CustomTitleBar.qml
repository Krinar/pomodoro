// CustomTitleBar.qml
import QtQuick
import QtQuick.Controls


Rectangle {
    id: titleBar
    height: 50
    color: "#ff4747"

    property var targetWindow: null

    MouseArea {
        anchors.fill: parent

        property point clickPos: Qt.point(0, 0)

        onPressed: function(mouse) {
            clickPos = Qt.point(mouse.x, mouse.y)
        }

        onPositionChanged: function(mouse) {
            if (pressed) {
                var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
                mainWindow.x += delta.x
                mainWindow.y += delta.y
            }
        }
    }

    // Иконка слева
    // Image {
    //     id: appIcon
    //     anchors.left: parent.left
    //     anchors.verticalCenter: parent.verticalCenter
    //     anchors.leftMargin: 15
    //     width: 32
    //     height: 32
    //     source: "icons/tomatoes_2_32x32.png"
    //     fillMode: Image.PreserveAspectFit
    // }

    Text {
        anchors.centerIn: parent
        text: mainWindow.title
        font.pixelSize: 18
        font.bold: true
        color: "white"
    }

    MouseArea {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 15
        width: 30
        height: 30

        Rectangle {
            anchors.fill: parent
            color: parent.pressed ? "#cc0000" : "transparent"
            radius: 4
            }

        Text {
            anchors.centerIn: parent
            text: "✕"
            font.pixelSize: 20
            color: parent.containsMouse ? "red" : "white"
        }

        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor

        onClicked: Qt.quit()
    }
}

