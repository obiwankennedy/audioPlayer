import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import Views
import Controllers

ColumnLayout {
    id: root

    required property QtObject ctrl

    Item {
        id: panelImg
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.preferredHeight: 200

        ImageDataViewer {
            id: viewer
            image: MainController.image
            anchors.centerIn: parent
            width: height
            height: parent.height * 0.8
            visible: MainController.hasImage
        }
    }


    Label {
        Layout.alignment: Qt.AlignCenter
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
    }

    RowLayout {
        Layout.alignment: Qt.AlignCenter
        implicitHeight: 100
        spacing: 30
        ImageButton {
            onClicked: ctrl.previous()
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            source: "qrc:/resources/icons/Previous.svg"
            Layout.preferredHeight: 64
            Layout.preferredWidth: 64
            flat: true
        }
        ImageButton {
            onClicked: ctrl.audioCtrl.playing ? ctrl.pause() : ctrl.play()
            source: ctrl.playing ? "qrc:/resources/icons/Pause.svg" : "qrc:/resources/icons/Play.svg"
            Layout.preferredHeight: 100
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: 100
            flat: true
        }
        ImageButton {
            onClicked: ctrl.next()
            source: "qrc:/resources/icons/Next.svg"
            Layout.preferredHeight: 64
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
            Layout.preferredWidth: 64
            flat: true
        }
    }
    RowLayout {
        Layout.fillWidth: true
        Layout.preferredHeight: 60
        Label {
            text: "Volume:"
        }

        Slider {//volume
            from: 0
            to: 1.0
            value: ctrl.volume
            Layout.fillWidth: true
            onValueChanged: ctrl.volume = value
        }
    }
}
