import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Qt.labs.qmlmodels
import Qt.labs.platform

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
        rows: 2
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

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: function(event) {
                    let point = table.cellAtPosition(event.x, event.y, true)
                    let ind = table.model.index(point.y, point.x)
                    if (event.button === Qt.LeftButton) {
                        let res = table.model.setData(ind, colorPicker.currentColor, GameModel.ColorRole)
                    } else if (event.button === Qt.RightButton) {
                        table.model.setData(ind, table.model.deadColor, GameModel.ColorRole)
                    }

                    event.accepted = true
                }

                onPositionChanged: function(event) {
                    let point = table.cellAtPosition(event.x, event.y, true)
                    let ind = table.model.index(point.y, point.x)
                    if (event.buttons & Qt.LeftButton) {
                        let res = table.model.setData(ind, colorPicker.currentColor, GameModel.ColorRole)
                    } else if (event.buttons & Qt.RightButton) {
                        table.model.setData(ind, table.model.deadColor, GameModel.ColorRole)
                    }

                    event.accepted = true
                }
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

                onClicked: function() {
                    gameModel.clear()
                    fieldHeight.value = gameModel.rowCount()
                    fieldWidth.value = gameModel.columnCount();
                }
            }

            Rectangle {
                color: colorPicker.currentColor
                Layout.minimumHeight: 50
                Layout.preferredHeight: 100
                Layout.preferredWidth: 100

                MouseArea {
                    anchors.fill: parent
                    onDoubleClicked: colorPicker.open()
                }
            }

            SpinBox {
                id: fieldHeight

                font.pointSize: 20
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.preferredWidth: 100

                editable: true
                from: 10
                value: gameModel.rowCount()
                to: 200
                wheelEnabled: true

                onValueChanged: function() {
                    if (gameModel.rowCount() > value) { // remove
                        let toRemove = gameModel.rowCount() - value
                        gameModel.removeRows(gameModel.rowCount() - toRemove - 1, toRemove)
                    } else { // insert
                        let toInsert = value - gameModel.rowCount()
                        gameModel.insertRows(gameModel.rowCount(), toInsert)
                    }
                }
            }

            SpinBox {
                id: fieldWidth

                font.pointSize: 20
                Layout.minimumHeight: 50
                Layout.preferredHeight: 50
                Layout.preferredWidth: 100

                editable: true
                from: 10
                value: gameModel.columnCount()
                to: 200
                wheelEnabled: true

                onValueChanged: function() {
                    if (gameModel.columnCount() > value) { // remove
                        let toRemove = gameModel.columnCount() - value
                        gameModel.removeColumns(gameModel.columnCount() - toRemove - 1, toRemove)
                    } else { // insert
                        let toInsert = value - gameModel.columnCount()
                        gameModel.insertColumns(gameModel.columnCount(), toInsert)
                    }
                }
            }
        }

        Slider {
            id: timeSlider
            Layout.fillWidth: true
            from: 1
            value: (to - from) / 2
            to: 490
        }
    }

    ColorDialog {
        id: colorPicker
        options: ColorDialog.NoButtons
        modality: Qt.NonModal
        flags: Qt.Widget
    }

    Timer {
        id: timer
        interval: timeSlider.from + timeSlider.to - timeSlider.to * timeSlider.visualPosition
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
        }
    }

    GameModel {
        id: gameModel
    }
}
