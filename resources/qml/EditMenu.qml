import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

Menu {
    id: menu
    property QtObject ctrl
    property bool darkMode: false
    title: qsTr("Edit")

    signal hidePlayer()

    MenuItem {
        text: qsTr("Undo")
        //onTriggered:
    }
    MenuSeparator  {

    }
    MenuItem {
        text: qsTr("Hide Player")
        onTriggered: menu.hidePlayer()
    }
    MenuItem {
        text: menu.darkmode ? qsTr("Light Mode") : qsTr("Dark Mode")
        onTriggered: menu.darkMode = !menu.darkMode
    }
}
