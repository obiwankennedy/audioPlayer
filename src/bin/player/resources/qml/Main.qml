import QtQuick
import QtCore
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import QtQuick.Controls.Universal
import Customization
import Views
import Controllers

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
            ctrl: AppController
        }
        EditMenu {
            ctrl:AppController
            darkMode: root.darkMode
            onDarkModeChanged: root.darkMode = darkMode
            onHidePlayer: audioPlayer.visible = !audioPlayer.visible
        }
    }

    header: AudioPlayer {
        id: audioPlayer
        ctrl: AppController.audioCtrl
        onSettings: settingDialog.open()
        //height: 50
    }

    FileDialog {
        id: openDialog
        title: qsTr("Load playlist from File")
        currentFolder:  StandardPaths.writableLocation(StandardPaths.MusicLocation)
        fileMode: FileDialog.OpenFile
        nameFilters: ["Playlist (*.apl *.m3u)"]
        onAccepted: {
            AppController.setFilename(openDialog.selectedFile)
            AppController.loadFile();
            close()
        }
        onRejected: close()
    }

    FolderDialog {
        id: openDir
        title: qsTr("Add directory at selection")
        currentFolder: StandardPaths.writableLocation(StandardPaths.MusicLocation)
        onAccepted: {
            AppController.addDirectory(playList.currentIndex,openDir.selectedFolder);
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
            AppController.addFiles(addAudioFiles.selectedFiles, playList.currentIndex);
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
            AppController.setFilename(saveDialog.selectedFile)
            AppController.saveFile();
            close()
        }
        onRejected: close()
    }


    ContextMenu {
        id: contextMenu
    }

    PlayList {
        id: playList
        anchors.fill: parent
        onClickOnItem: (index, tags, selected, mouse) => {
                           console.log("ClickOn item",tags," i:",index," s:",selected)
                           if (mouse.button === Qt.RightButton) {
                               contextMenu.tagsList = tags
                               contextMenu.songIndex = index
                               contextMenu.popup()
                           }
                           else if(mouse.button === Qt.LeftButton && mouse.modifiers === Qt.NoModifier){
                               AppController.model.clearSelection()
                               playList.currentIndex = index
                               AppController.model.select([index])
                           }
                           else if(mouse.button === Qt.LeftButton && mouse.modifiers === Qt.ShiftModifier) {
                               console.log("Select elements")
                               let ids = []
                               let max = Math.max(index, playList.currentIndex)
                               let min = Math.min(index, playList.currentIndex)
                               for(let i = min; i < max+1; ++i )
                                    ids.push(i)

                               console.log("Ids: ",ids.join(','))
                               AppController.model.select(ids)
                           }
                       }
    }



}
