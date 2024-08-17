import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels

import game.of.life

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Game of life")

    GridLayout {
        anchors.fill: parent
        columns: 2
        rowSpacing: 5
        columnSpacing: 5

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: 'black'
            TableView {
                id: table
                anchors.fill: parent
                interactive: false // disable draging and flicking

                columnSpacing: 1
                rowSpacing: 1

                columnWidthProvider: function(column) {
                    return table.width / model.columnCount() - columnSpacing;
                }
                rowHeightProvider: function(column) {
                    return table.height / model.rowCount() - rowSpacing;
                }
                selectionMode: TableView.SelectionDisabled

                model: gameModel

                delegate: cellDelegate
            }
        }

        ColumnLayout {
            Button {
                text: !timer.running ? "Start game" : "Stop game"

                Layout.minimumHeight: 50
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100

                onClicked: !timer.running ? timer.start() : timer.stop()
            }

            Button {
                text: "Clear field"

                Layout.minimumHeight: 50
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100

                onClicked: gameModel.clear()
            }
        }


    }

    Timer {
        id: timer
        interval: 50
        repeat: true
        onTriggered: gameModel.step();
    }

    Component {
        id: cellDelegate
        Rectangle {
            required property var model

            id: rect
            color: model.color
            implicitHeight: 1
            implicitWidth: 1

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: function(event) {
                    if (event.button === Qt.LeftButton) {
                        model.color = "cyan"
                    } else if (event.button === Qt.RightButton) {
                        model.color = gameModel.deadColor
                    }
                    event.accepted = true
                }
            }
        }
    }

    GameModel {
        id: gameModel
    }




}
