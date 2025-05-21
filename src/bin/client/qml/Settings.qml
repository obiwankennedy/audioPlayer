import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Views
import Controllers

GridLayout {
    id: root
    columns: 4
    required property QtObject ctrl


    Label {
        text: qsTr("Shuffle:")
    }
    ImageButton {
        checkable: true
        checked:  ctrl.mode === MainController.Shuffle
        onClicked: ctrl.setPlayingMode(MainController.Shuffle)
        source: "qrc:/resources/icons/Shuffle.svg"
        flat: true
        Layout.preferredHeight: 64
        Layout.preferredWidth: 64
    }
    Label {
        text: qsTr("Forword:")
    }
    ImageButton {
        checkable: true
        checked:  ctrl.mode === MainController.Forward
        onClicked: ctrl.mode = MainController.Forward
        source: "qrc:/resources/icons/Queue.svg"
        Layout.preferredHeight: 64
        Layout.preferredWidth: 64
        flat: true
    }
    Label {
        text: qsTr("Loop:")
    }
    ImageButton {
        checkable: true
        checked:  ctrl.mode === MainController.Loop
        onClicked: ctrl.mode = MainController.Loop
        source: "qrc:/resources/icons/Repeat One.svg"
        Layout.preferredHeight: 64
        Layout.preferredWidth: 64
        flat: true
    }
    Label {
        text: qsTr("Unique:")
    }
    ImageButton {
        checkable: true
        checked:  ctrl.mode === MainController.Unique
        onClicked: ctrl.mode = MainController.Unique
        source: "qrc:/resources/icons/Download.svg"
        rotation: -90
        Layout.preferredHeight: 64
        flat: true
        Layout.preferredWidth: 64
    }
    Label {
           text: qsTr("Stream")
    }
    Switch {
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
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }
    Item {
        Layout.columnSpan: 2
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
