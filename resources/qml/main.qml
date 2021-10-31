import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Universal 2.12
import AudioPlayer 1.0

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 400
    property real viewScale: 1
    property int idx: 0
    property bool darkMode: true

    MainController {
        id: ctrl
    }

   /* AudioController {
        id: audioCtrl
        model: ctrl.audioModel
    }*/

    onDarkModeChanged: _themeCtrl.nightMode = root.darkMode
    Universal.theme: root.darkMode ? Universal.Dark: Universal.Light

    menuBar: MenuBar {
        id: menu
        FileMenu {
            ctrl: ctrl
        }
        EditMenu {
            ctrl:ctrl
            darkMode: root.darkMode
            onDarkModeChanged: root.darkMode = darkMode
            onHidePlayer: audioPlayer.visible = !audioPlayer.visible
        }
    }

    header: AudioPlayer {
        id: audioPlayer
        ctrl: ctrl.audioCtrl
    }

    FileDialog {
        id: openDialog
        title: qsTr("Load playlist from File")
        folder: shortcuts.home
        selectMultiple: false
        nameFilters: ["Playlist (*.apl *.m3u)"]
        onAccepted: {
            ctrl.setFilename(openDialog.fileUrl)
            ctrl.loadFile();
            close()
        }
        onRejected: close()
    }

    FileDialog {
        id: openDir
        title: qsTr("Add directory at selection")
        folder: shortcuts.home
        selectFolder: true
        selectExisting: true
        onAccepted: {
            ctrl.addDirectory(view.currentIndex,openDir.fileUrl);
            close()
        }
        onRejected: close()
    }

    FileDialog {
        id: addAudioFiles
        title: qsTr("Load playlist from File")
        folder: shortcuts.home
        selectExisting: true
        selectMultiple: true
        nameFilters: ["Audiofiles (*.mp3 *.mpc *.flac *.ogg *.wma)"]
        onAccepted: {
            ctrl.addFiles(addAudioFiles.fileUrls, view.currentIndex);
            close()
        }
        onRejected: close()
    }

    FileDialog {
        id: saveDialog
        title: qsTr("Save playlist into File")
        folder: shortcuts.home
        selectExisting: false
        selectMultiple: false
        defaultSuffix: "apl"
        nameFilters: ["Playlist (*.apl)"]
        onAccepted: {
            ctrl.setFilename(saveDialog.fileUrl)
            ctrl.saveFile();
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

            Component.completed: view.currentIndex = ctrl.audioCtrl.songIndex

            highlightMoveDuration: 20
            function ensureVisible(index) {
                var hTotal = view.contentHeight
                var itemCount = view.count
                var hViewPort = view.height
                var visibleItems = hViewPort * itemCount/hTotal
                var marge = hViewPort/2
                var step = hTotal/itemCount
                var value = (step * index - marge)
                if(Math.abs(value - view.contentY) > marge)
                    view.contentY = value;
            }

            highlight: Rectangle { color: Universal.accent; radius: 5 }

            Connections {
                target: ctrl.audioCtrl
                function onSongIndexChanged() {
                    view.positionViewAtIndex(ctrl.audioCtrl.songIndex, ListView.Center)//view.ensureVisible(ctrl.audioCtrl.songIndex)
                }
            }
            focus: true
            clip: true
            model: ctrl.filteredModel
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
                            font.bold: ctrl.audioCtrl.songIndex === model.songIndex
                        }
                        Label {//artist
                            text: artist
                            Layout.fillWidth: true
                            font.bold: ctrl.audioCtrl.songIndex === model.songIndex
                        }
                        Label {//time
                            text: time
                            font.bold: ctrl.audioCtrl.songIndex === model.songIndex
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
                    to: ctrl.audioCtrl.duration
                    value: ctrl.audioCtrl.seek
                    visible: ctrl.audioCtrl.songIndex === model.songIndex

                }
                MouseArea {
                    anchors.fill: parent
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onDoubleClicked:{
                        ctrl.audioCtrl.songIndex = model.songIndex;
                        ctrl.audioCtrl.play()
                    }
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                             contextMenu.popup()
                        else (mouse.button === Qt.LeftButton)
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
                          onTriggered: ctrl.addToExport(model.songIndex)
                        }

                        MenuItem {
                            text: "Insert files…"
                            onTriggered: addAudioFiles.open()
                        }

                        MenuItem {
                            text: "Remove current selection…"
                            onTriggered: ctrl.removeSelection()
                        }
                    }
                }
            }
        }
    }



}
