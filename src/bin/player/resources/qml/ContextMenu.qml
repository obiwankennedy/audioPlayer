import QtQuick
import QtQuick.Controls
import QtQml
import Views
import Controllers

Menu {
    id: root
    property int songIndex
    property list<string> tagsList
    onTagsListChanged: {
        instantiator.model= 0
        instantiator.model = audioCtrl.tags
    }

    property AudioController audioCtrl: AppController.audioCtrl

    MenuItem {
        text: "Insert content of Directory…"
        onTriggered: openDir.open()
    }

    MenuItem {
      text: qsTr("Mark song to be exported")
      onTriggered: AppController.addToExport(model.songIndex)
    }

    MenuItem {
        text: "Insert files…"
        onTriggered: addAudioFiles.open()
    }

    MenuItem {
        text: "Remove current selection…"
        onTriggered: AppController.removeSelection()
    }

    MenuItem {
        text: "Refresh metadata"
        onTriggered: AppController.audioCtrl.refreshMetaData()
    }
    MenuSeparator {

    }
    Instantiator {
        id: instantiator
        model: audioCtrl.tags
        delegate: MenuItem {
            text: tagName
            checkable: true
            checked: root.tagsList.indexOf(tagName) >= 0
            onTriggered: audioCtrl.addTag(tagName)
        }

        onObjectAdded: (index, object) => root.insertItem(index+5, object)
        onObjectRemoved: (index, object) => root.removeItem(object)
    }
}
