import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import AudioPlayer 1.0

Frame {
    id: _root
    property QtObject ctrl
    //height: buttonLyt.implicitHeight
    //height: 111

    RowLayout {
        anchors.fill: parent
        Image {
            Layout.preferredWidth: 100
            fillMode: Image.PreserveAspectFit
            source: ctrl.albumArt ? "image://album/%1".arg(ctrl.albumArt) : ""
            sourceSize.width: 100
            sourceSize.height: 100
        }
        ColumnLayout {
            id: buttonLyt
            Layout.fillWidth: true
            TextField {
                Layout.fillWidth: true
                text: ctrl.title
            }
            Slider {
                id: seekPos
                Layout.fillWidth: true
                value: ctrl.seek
                from: 0
                to: ctrl.duration

                onMoved:{
                        ctrl.seek = value
                }
            }

            RowLayout {
                Layout.fillWidth: true
                ImageButton {
                    onClicked: ctrl.previous()
                    source: "qrc:/resources/icons/Previous.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                ImageButton {
                    onClicked: ctrl.playing ? ctrl.pause() : ctrl.play()
                    source: ctrl.playing ? "qrc:/resources/icons/Pause.svg" : "qrc:/resources/icons/Play.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                ImageButton {
                    onClicked: ctrl.next()
                    source: "qrc:/resources/icons/Next.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                Slider {//volume
                    from: 0
                    to: 1.0
                    value: ctrl.volume
                    onValueChanged: ctrl.volume = value
                }
                ImageButton {
                    //shuffle
                    checkable: true
                    checked:  ctrl.mode === AudioController.SHUFFLE
                    onClicked: ctrl.mode = AudioController.SHUFFLE
                    source: "qrc:/resources/icons/Shuffle.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                ImageButton {
                    checkable: true
                    checked:  ctrl.mode === AudioController.NEXT
                    onClicked: ctrl.mode = AudioController.NEXT
                    source: "qrc:/resources/icons/Queue.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                ImageButton {
                    checkable: true
                    checked:  ctrl.mode === AudioController.LOOP
                    onClicked: ctrl.mode = AudioController.LOOP
                    source: "qrc:/resources/icons/Repeat One.svg"
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                ImageButton {
                    checkable: true
                    checked:  ctrl.mode === AudioController.UNIQUE
                    onClicked: ctrl.mode = AudioController.UNIQUE
                    source: "qrc:/resources/icons/Download.svg"
                    rotation: -90
                    Layout.preferredHeight: 32
                    Layout.preferredWidth: 32
                }
                Item {
                    Layout.fillWidth: true
                }
                TextField {
                    id: find
                    placeholderText: qsTr("Find")
                    onEditingFinished: ctrl.find(find.text)
                }
            }
        }
    }
}
