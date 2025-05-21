import QtQuick
import QtQuick.Controls

Button {
    id: root

    property string source
    width: 32
    height: 32
    flat: true

    icon.source: root.source
    icon.color: checked ? "white" : "transparent"
    icon.width: 32
    icon.height: 32

    /*contentItem: Image {
        id: img
        sourceSize.height: 32
        sourceSize.width: 32
        fillMode: Image.PreserveAspectFit
    }*/

}

