import QtQuick
import QtQuick.Controls
import QtQml

Menu {
    id: menu
    property QtObject ctrl
    title: qsTr("File")
    MenuItem {
        text: qsTr("New")
        onTriggered: ctrl.resetData()
    }
    MenuItem {
        text: qsTr("Open File…")
        onTriggered: openDialog.open()
    }
    MenuItem {
        text: qsTr("Save")

        onTriggered: {
            if(ctrl.filename)
                ctrl.saveFile();
            else
                saveDialog.open()
        }
    }
    MenuItem {
        text: qsTr("Save As…")
        onTriggered: {
            saveDialog.open()
        }
    }
    MenuSeparator { }
    MenuItem {
      text: qsTr("Export SSH")
      onTriggered: ctrl.exportList()
    }

   /* MenuSeparator { }
    MenuItem {
        text: qsTr("Undo")
        //enabled: ctrl.canUndo
        onTriggered: {
            ctrl.undo()
        }
    }
    MenuItem {
        text: qsTr("Redo")
        //enabled: ctrl.canRedo
        onTriggered: {
            ctrl.redo()
        }
    }*/
    /*MenuSeparator { }
    Instantiator {
        model: ctrl.recentFiles
        MenuItem {
            text: modelData.match(/[-_\w]+[.][\w]+$/i)[0]
            onTriggered: {
                ctrl.filename = modelData
            }
        }
    }*/
    /*MenuItem {
        text: qsTr("Export File…")
        onTriggered: {
            //importDialog.open()
        }
    }*/
    MenuSeparator { }
    MenuItem {
        text: qsTr("Quit")
        checkable: true
        //checked: ctrl.spacing
        onTriggered: ctrl.spacing = checked
    }
}
