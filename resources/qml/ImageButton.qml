import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    property alias source: img.source
    width: 32
    height: 32

    contentItem: Image {
        id: img
        sourceSize.height: 32
        sourceSize.width: 32
        fillMode: Image.PreserveAspectFit
    }

}
