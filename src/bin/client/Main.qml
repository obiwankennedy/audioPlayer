import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Views


ApplicationWindow
{
    width: 800
    height: 400
    visible: true

    ClientController {
        id: ctrl

        url: "ws://localhost:10999"
        Component.onCompleted: ctrl.connectTo();
    }

    Item {
        anchors.fill: parent
        RowLayout {
            anchors.centerIn: parent
            Button {
                text: "previous"
                onClicked: ctrl.previous()
            }
            Button {
                text: "play"
                onClicked: ctrl.play()
            }
            Button {
                text: "next"
                onClicked: ctrl.next()
            }
        }
    }

}
