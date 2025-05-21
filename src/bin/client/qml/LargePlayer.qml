import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Views
import Controllers
import QtMultimedia

RowLayout {
    anchors.fill: parent
    Item {
        Layout.preferredWidth: 100
        Layout.preferredHeight: 100
        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: ctrl.albumArt ? "image://album/%1".arg(ctrl.albumArt) : "qrc:/resources/icons/Album.svg"
            sourceSize.width: 100
            sourceSize.height: 100
            visible: !MainController.audioCtrl.hasVideo

            ImageDataViewer {
                image: ctrl.albumArt
                anchors.fill: parent
                visible: ctrl.hasImage
            }
        }
        VideoOutput {
            id: videoOutputImage
            anchors.fill: parent
            visible: MainController.audioCtrl.hasVideo
            fillMode: VideoOutput.PreserveAspectFit
        }
    }
    ColumnLayout {
        id: buttonLyt
        Layout.fillWidth: true
        TextField {
            Layout.fillWidth: true
            text: "%1 - %2 ".arg(MainController.artist).arg(MainController.title)
        }
        Slider {
            id: seekPos
            Layout.fillWidth: true
            value: MainController.position
            from: 0
            to: MainController.duration

            onMoved:{
                MainController.position = value
            }
          /*  Timer {
                running: true
                interval: 100
                repeat: true
                onTriggered: console.log("logs",MainController.position)
            }*/
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
                onClicked: ctrl.audioCtrl.playing ? ctrl.pause() : ctrl.play()
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
                checked:  ctrl.mode === MainController.Shuffle
                onClicked: ctrl.setPlayingMode(MainController.Shuffle)
                source: "qrc:/resources/icons/Shuffle.svg"
                Layout.preferredHeight: 32
                Layout.preferredWidth: 32
            }
            ImageButton {
                checkable: true
                checked:  ctrl.mode === MainController.Forward
                onClicked: ctrl.mode = MainController.Forward
                source: "qrc:/resources/icons/Queue.svg"
                Layout.preferredHeight: 32
                Layout.preferredWidth: 32
            }
            ImageButton {
                checkable: true
                checked:  ctrl.mode === MainController.Loop
                onClicked: ctrl.mode = MainController.Loop
                source: "qrc:/resources/icons/Repeat One.svg"
                Layout.preferredHeight: 32
                Layout.preferredWidth: 32
            }
            ImageButton {
                checkable: true
                checked:  ctrl.mode === MainController.Unique
                onClicked: ctrl.mode = MainController.Unique
                source: "qrc:/resources/icons/Download.svg"
                rotation: -90
                Layout.preferredHeight: 32
                Layout.preferredWidth: 32
            }
            ImageButton {
                onClicked: _root.settings()
                source: "qrc:/resources/icons/settings.svg"
                rotation: -90
                Layout.preferredHeight: 32
                Layout.preferredWidth: 32
                Layout.leftMargin: 32
            }
            Item {
                Layout.fillWidth: true
            }
            Switch {
                text: qsTr("Stream Music")
                enabled: MainController.clientCtrl.connected
                onCheckedChanged: {
                    ctrl.syncWithServer = checked;
                }
            }

            TextField {
                id: find
                placeholderText: qsTr("Find")
                onEditingFinished: ctrl.find(find.text)
                Layout.preferredWidth: 130
            }
        }
    }
}
