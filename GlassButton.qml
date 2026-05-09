import QtQuick
import QtQuick.Controls

Button {
    id: control

    width: 64
    height: 64

    font.family: "Segoe UI Symbol"
    font.pixelSize: width * 0.38//24

    focusPolicy: Qt.NoFocus
    hoverEnabled: true

    scale: hovered ? 1.05 : 1.0

    Behavior on scale {
        NumberAnimation {
            duration: 200
            easing.type: Easing.OutQuad
        }
    }

    background: Rectangle {
        anchors.fill: parent

        radius: width / 2

        color: control.hovered
               ? "#9Affc9c9"
               : "#FA8072"

        // border.color: "#ffffff22"
        // border.width: 1

        Behavior on color {
            ColorAnimation {
                duration: 250
            }
        }
    }

    contentItem: Label {
        text: control.text
        color: "white"

        font.family: control.font.family
        font.pixelSize: control.font.pixelSize

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
