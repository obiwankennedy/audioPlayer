import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import Views
import Controllers

Dialog {
    id: popup
    width: 400
    height: 40 * Math.min(root.count, 15)
    standardButtons: Dialog.Ok
    GridLayout {
        anchors.fill: parent
        columns: 2
        Label {
            text: qsTr("Audio output")
        }

        ComboBox {
            id: output
            Layout.preferredWidth: 200
            model: AppController.outputModel
            textRole: "display"
            onCurrentIndexChanged: AppController.deviceIndex = output.currentIndex
            Component.onCompleted: {
                console.log("deviceIndex:",AppController.deviceIndex)
                output.currentIndex= AppController.deviceIndex
            }
        }
        Label {
            text: qsTr("Refresh the list")
        }

        Button {
            id: refresh
            icon.name: "view-refresh"
            onClicked: AppController.audioCtrl.updateAudioDevices()
        }
    ListView {
        id: root
        property AudioController ctrl: AppController.audioCtrl
        model: root.ctrl.tags
        Layout.columnSpan: 2
        Layout.fillHeight: true
        Layout.fillWidth: true
        clip: true
        delegate: RowLayout {
            width: root.width
            height: 40
            Label {
                id: lbl
                text: tagName
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            ToolButton {
                id: allowBtn

                Layout.fillHeight: true
                Layout.preferredWidth: 30
                checkable: true

                background: Rectangle {
                    id: bg
                    radius: 10
                    opacity: 0.8
                    color: allowBtn.checked ? "green" : "grey"
                }

                onClicked:  {
                    root.ctrl.filteredTagModel.removeTag(tagName, true)
                    root.ctrl.filteredTagModel.removeTag(tagName, false)

                    if(allowBtn.checked)
                    {
                        if(forbiddenBtn.checked)
                        {
                            forbiddenBtn.checked = false
                        }

                        root.ctrl.filteredTagModel.addTag(tagName, false)
                    }
                }
            }

            ToolButton {
                id: forbiddenBtn

                Layout.fillHeight: true
                Layout.preferredWidth: 30
                checkable: true
                background: Rectangle {
                    radius: 10
                    opacity: 0.8
                    color: forbiddenBtn.checked ? "red" : "grey"
                }

                onClicked:  {
                    root.ctrl.filteredTagModel.removeTag(tagName, true)
                    root.ctrl.filteredTagModel.removeTag(tagName, false)
                    if(forbiddenBtn.checked)
                    {
                        if(forbiddenBtn.checked)
                        {
                            allowBtn.checked = false
                        }

                        root.ctrl.filteredTagModel.addTag(tagName, true)
                    }
                }
            }
        }
    }
}
}
