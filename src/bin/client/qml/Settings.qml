import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Views
import Controllers

GridLayout {
    id: root
    columns: 4
    property AudioController ctrl: MainController.audioCtrl

    Label {
        text: qsTr("Shuffle:")
    }
    ImageButton {
        checkable: true
        checked:  MainController.mode === MainController.Shuffle
        onClicked: MainController.setPlayingMode(MainController.Shuffle)
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
        checked:  MainController.mode === MainController.Forward
        onClicked: MainController.mode = MainController.Forward
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
        checked:  MainController.mode === MainController.Loop
        onClicked: MainController.mode = MainController.Loop
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
        checked:  MainController.mode === MainController.Unique
        onClicked: MainController.mode = MainController.Unique
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
            MainController.syncWithServer = checked;
        }
    }
    TextField {
        id: find
        placeholderText: qsTr("Find")
        onEditingFinished: MainController.find(find.text)
        Layout.preferredWidth: 130
        Layout.columnSpan: 2
        Layout.fillWidth: true
    }

    ListView {
        id: tag
        model: root.ctrl.tags
         Layout.columnSpan: 4
        Layout.fillWidth: true
        Layout.fillHeight: true
        clip: true
        delegate: RowLayout {
            width: tag.width
            height: 40
            Label {
                id: lbl
                text: tagName
                Layout.fillHeight: true
                Layout.preferredWidth: 100
            }

                ToolButton {
                    id: allowBtn

                    Layout.fillHeight: true
                    Layout.preferredWidth: 30
                    checkable: true
                    background: Rectangle {
                        id: bg
                        radius: height/2
                        opacity: 0.8
                        color: allowBtn.checked ? "green" : "grey"
                    }

                    onClicked:  {
                        root.ctrl.filteredTagModel.removeTag(tagName, true)
                        MainController.removeFilterTag(tagName, true)
                        root.ctrl.filteredTagModel.removeTag(tagName, false)
                        MainController.removeFilterTag(tagName, false)
                        if(allowBtn.checked && forbiddenBtn.checked)
                        {
                            forbiddenBtn.checked = false
                        }

                        root.ctrl.filteredTagModel.addTag(tagName, false)
                        MainController.filterTag(tagName, false)
                    }
                }

                ToolButton {
                    id: forbiddenBtn

                    Layout.fillHeight: true
                    Layout.preferredWidth: 30
                    checkable: true

                    background: Rectangle {
                        radius: height/2
                        opacity: 0.8
                         color: forbiddenBtn.checked ? "red" : "grey"
                    }

                    onClicked:  {
                        root.ctrl.filteredTagModel.removeTag(tagName, true)
                        MainController.removeFilterTag(tagName, true)
                        root.ctrl.filteredTagModel.removeTag(tagName, false)
                        MainController.removeFilterTag(tagName, false)
                        if(allowBtn.checked && forbiddenBtn.checked)
                        {
                            allowBtn.checked = false
                        }

                        root.ctrl.filteredTagModel.addTag(tagName, true)
                        MainController.filterTag(tagName, true)
                    }
                }
            }
    }
}
