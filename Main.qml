import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQml
import QtQuick.Layouts

import Pomodoro 1.0

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 400
    height: 600
    font.family: "Arial Rounded MT Bold"
    flags: Qt.FramelessWindowHint
    title: "Pomodoro"

    CustomTitleBar {
        id: titleBar
        targetWindow: mainWindow
        width: parent.width
    }

    // Основная колонка с компонентами
    Column {
        anchors.centerIn: parent
        spacing: 30

        // Rectangle {
        //     anchors.top: titleBar.bottom
        //     anchors.left: parent.left
        //     anchors.right: parent.right
        //     anchors.bottom: parent.bottom
        //     color: "white"
        // }
        RowLayout {
            width: 250

            Item {
                Layout.fillWidth: true
            }

            GlassButton {
                id: settings
                text: "⛭"
                Layout.preferredWidth: 55
                Layout.preferredHeight: 55
            }
        }

        Pomodoro {
            id: pomodoro

            width: 250
            height: 250

            name: "clock"
            backgroundColor: "white"
            borderActiveColor: "#FA8072"
            borderNonActiveColor: "#fff3f0"

            Text {
                id: textTimer
                anchors.centerIn: parent

                font.family: "Calibri"
                font.bold: true
                font.pixelSize: 75

                text: "05:00"
            }

            onCircleTimeChanged: {
                textTimer.text = Qt.formatTime(circleTime, "mm:ss")
            }

            Canvas {
                id: dots
                anchors.fill: parent

                onPaint: {
                    const ctx = getContext("2d");
                    ctx.reset();

                    const cx = width / 2;
                    const cy = height / 2;

                    const ringRadius = Math.min(width, height) / 2 - 5;
                    const dotRadius = ringRadius;

                    const totalDots = 60;

                    for (let i = 0; i < totalDots; i++) {

                        const angle = (i / totalDots) * Math.PI * 2 - Math.PI / 2;

                        const x = cx + Math.cos(angle) * dotRadius;
                        const y = cy + Math.sin(angle) * dotRadius;

                        const isMajor = i % 5 === 0;

                        ctx.beginPath();
                        ctx.fillStyle = isMajor ? "#FA8072" : "#00000025";

                        const size = isMajor ? 4 : 2.5;

                        ctx.arc(x, y, size, 0, Math.PI * 2);
                        ctx.fill();
                    }
                }
            }
        }

        // Строка с кнопками
        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            GlassButton {
                id: clear
                text: "↺"
                onClicked: pomodoro.clear();
                Layout.preferredWidth: 42
                Layout.preferredHeight: 42
                Layout.alignment: Qt.AlignVCenter
            }

            GlassButton {
                id: start
                text: "▶︎"
                onClicked: pomodoro.start()
                Layout.preferredWidth: 62
                Layout.preferredHeight: 62
            }

            GlassButton {
                id: stop
                text: "❚❚"
                onClicked:  pomodoro.stop();
                Layout.preferredWidth: 42
                Layout.preferredHeight: 42
                Layout.alignment: Qt.AlignVCenter
            }
        }
    }
}
//}
