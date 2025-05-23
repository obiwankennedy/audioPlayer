import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Universal
import Views
import Customization

ApplicationWindow
{
    id: root

    property bool darkMode: true

    width: 1220/2
    height: 2712/2
    visible: true

    onDarkModeChanged: Theme.nightMode = root.darkMode
    Universal.theme: root.darkMode ? Universal.Dark: Universal.Light

    /*menuBar: MenuBar {
        id: menu
        FileMenu {
            ctrl: MainController
        }
        EditMenu {
            ctrl:MainController
            darkMode: root.darkMode
            onDarkModeChanged: root.darkMode = darkMode
            onHidePlayer: audioPlayer.visible = !audioPlayer.visible
        }
    }*/

    onClosing: {
        MainController.stop()
    }

    header: AudioPlayer {
        id: audioPlayer
        ctrl: MainController
        onSettings: settings.open()
    }

    /*Dialog {
        id: settingDialog
        title: qsTr("Settings")
        parent: Overlay.overlay
        x: Math.round((parent.width - width) / 2)
        y: Math.round((parent.height - height) / 2)
        GridLayout {

            columns: 2
            Label {
                text: qsTr("Audio output")
            }

            ComboBox {
                id: output
                Layout.preferredWidth: 200
                model: MainController.audioCtrl.outputModel
                textRole: "display"
                onCurrentIndexChanged: MainController.deviceIndex = output.currentIndex
                Component.onCompleted: {
                    console.log("deviceIndex:",MainController.deviceIndex)

                    //output.currentIndex= MainController.deviceIndex
                }
            }
            Label {
                text: qsTr("Refresh the list")
            }

            Button {
                id: refresh
                icon.name: "view-refresh"
                onClicked: MainController.audioCtrl.updateAudioDevices()
            }
        }
        standardButtons: Dialog.Ok
    }*/

    Drawer {
        id: settings
        width: 0.80 * root.width
        height: root.height
        edge: Qt.RightEdge
        Settings {
            anchors.fill: parent
            anchors.margins: 20
        }
    }

    ScrollView {
        id: scrollView
        anchors.fill: parent
        ScrollBar.vertical.policy: MainController.smallUI ? ScrollBar.AlwaysOn : ScrollBar.AsNeeded
        ScrollBar.vertical.width: 30
        ScrollBar.vertical.interactive: true
        ListView {
            id: view
            anchors.fill: parent
            anchors.rightMargin: 30
            anchors.bottomMargin: 20
            interactive: true

            Component.onCompleted: view.currentIndex = MainController.audioCtrl.songIndex

            highlightMoveDuration: 20

            highlight: Rectangle { color: Universal.accent; radius: 5 }

            Connections {
                target: MainController
                function onIndexChanged() {
                    view.positionViewAtIndex(MainController.index, ListView.Center)//view.ensureVisible(ctrl.audioCtrl.songIndex)
                }
            }
            focus: true
            clip: true
            model: MainController.audioCtrl.filteredModel //filteredModel  filteredTagModel
            delegate:  Item {
            //    color: "red"
                width: view.width
                height: 40
                clip: true
                Frame {
                    id: control
                    width: view.width
                    height: 40

                    RowLayout {
                        id: lyt
                        anchors.fill: parent
                        Label {//title
                            text: title
                            Layout.preferredWidth: lyt.width/2
                            font.bold: MainController.index === model.songIndex
                            clip: true
                        }
                        Label {//artist
                            text: artist
                            Layout.fillWidth: true
                            font.bold: MainController.index === model.songIndex
                        }
                        Label {//time
                            text: time
                            font.bold: MainController.index === model.songIndex
                        }
                    }

                    background: Rectangle {
                      color: model.selected ? "#0b3d8c" : model.isSelectedForExport ? "darkgreen" : "transparent"
                      //border.width: 1
                      border.color: control.Universal.chromeDisabledLowColor
                    }
                }
                ProgressBar {
                    height: 1
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    from: 0
                    to: MainController.duration
                    value: MainController.position
                    visible: MainController.index === model.songIndex

                }
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onDoubleClicked:{
                        MainController.play(model.songIndex)
                    }
                    onClicked: (mouse)=>{
                        if(mouse.button === Qt.LeftButton)
                            view.currentIndex = index
                    }
                }
            }
        }
    }


}
