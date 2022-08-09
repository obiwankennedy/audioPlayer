import QtQuick
import QtCore
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Universal
import AudioPlayer
import Customization

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 400
    property real viewScale: 1
    property int idx: 0
    property bool darkMode: true

    onDarkModeChanged: Theme.nightMode = root.darkMode
    Universal.theme: root.darkMode ? Universal.Dark: Universal.Light

    menuBar: MenuBar {
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
    }

    header: AudioPlayer {
        id: audioPlayer
        ctrl: MainController.audioCtrl
        //height: 50
    }

    FileDialog {
        id: openDialog
        title: qsTr("Load playlist from File")
        currentFolder:  StandardPaths.writableLocation(StandardPaths.MusicLocation)
        fileMode: FileDialog.OpenFile
        nameFilters: ["Playlist (*.apl *.m3u)"]
        onAccepted: {
            MainController.setFilename(openDialog.fileUrl)
            MainController.loadFile();
            close()
        }
        onRejected: close()
    }

    FolderDialog {
        id: openDir
        title: qsTr("Add directory at selection")
        currentFolder: StandardPaths.writableLocation(StandardPaths.MusicLocation)
        onAccepted: {
            MainController.addDirectory(view.currentIndex,openDir.fileUrl);
            close()
        }
        onRejected: close()
    }

    FileDialog {
        id: addAudioFiles
        title: qsTr("Load playlist from File")
        currentFolder: StandardPaths.writableLocation(StandardPaths.MusicLocation)
        fileMode: FileDialog.OpenFiles
        nameFilters: ["Audiofiles (*.mp3 *.mpc *.flac *.ogg *.wma)"]
        onAccepted: {
            MainController.addFiles(addAudioFiles.fileUrls, view.currentIndex);
            close()
        }
        onRejected: close()
    }

    FileDialog {
        id: saveDialog
        title: qsTr("Save playlist into File")
        currentFolder: StandardPaths.writableLocation(StandardPaths.MusicLocation)
        fileMode: FileDialog.SaveFile
        defaultSuffix: "apl"
        nameFilters: ["Playlist (*.apl)"]
        onAccepted: {
            MainController.setFilename(saveDialog.fileUrl)
            MainController.saveFile();
            close()
        }
        onRejected: close()
    }



    ScrollView {
        anchors.fill: parent
        ListView {
            id: view
            anchors.fill: parent
            anchors.rightMargin: 20
            anchors.bottomMargin: 20

            Component.onCompleted: view.currentIndex = MainController.audioCtrl.songIndex

            highlightMoveDuration: 20

            highlight: Rectangle { color: Universal.accent; radius: 5 }

            Connections {
                target: MainController.audioCtrl
                function onSongIndexChanged() {
                    view.positionViewAtIndex(MainController.audioCtrl.songIndex, ListView.Center)//view.ensureVisible(ctrl.audioCtrl.songIndex)
                }
            }
            focus: true
            clip: true
            model: MainController.filteredModel
            delegate:  Item {
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
                            font.bold: MainController.audioCtrl.songIndex === model.songIndex
                        }
                        Label {//artist
                            text: artist
                            Layout.fillWidth: true
                            font.bold: MainController.audioCtrl.songIndex === model.songIndex
                        }
                        Label {//time
                            text: time
                            font.bold: MainController.audioCtrl.songIndex === model.songIndex
                        }
                    }

                    background: Rectangle {
                      color: model.isSelectedForExport ? "darkgreen" : "transparent"
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
                    to: MainController.audioCtrl.duration
                    value: MainController.audioCtrl.seek
                    visible: MainController.audioCtrl.songIndex === model.songIndex

                }
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onDoubleClicked:{
                        MainController.audioCtrl.songIndex = model.songIndex;
                        MainController.audioCtrl.play()
                    }
                    onClicked: (mouse)=>{
                        if (mouse.button === Qt.RightButton)
                             contextMenu.popup()
                        else if(mouse.button === Qt.LeftButton)
                            view.currentIndex = index
                    }

                    Menu {
                        id: contextMenu
                        MenuItem {
                            text: "Insert content of Directory…"
                            onTriggered: openDir.open()
                        }

                        MenuItem {
                          text: qsTr("Mark song to be exported")
                          onTriggered: MainController.addToExport(model.songIndex)
                        }

                        MenuItem {
                            text: "Insert files…"
                            onTriggered: addAudioFiles.open()
                        }

                        MenuItem {
                            text: "Remove current selection…"
                            onTriggered: MainController.removeSelection()
                        }
                    }
                }
            }
        }
    }



}
