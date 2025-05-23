import QtQuick
import QtQuick.Controls
import Views
import Controllers

Frame {
    id: _root
    property QtObject ctrl

    signal settings

    implicitHeight: player.implicitHeight

    /*onCtrlChanged: {
        _root.ctrl.audioCtrl.videoOutput = videoOutputImage
    }*/
    /*Component {
        id: small
        SmallPlayer {
            property QtObject ctrl: _root.ctrl
        }
    }

    Component {
        id: large
        LargePlayer {
            property QtObject ctrl: _root.ctrl
        }
    }*/

    SmallPlayer {
        id: player
        anchors.fill: parent
        property QtObject ctrl: _root.ctrl
    }

    ImageButton {
        id: menu
        anchors.top: parent.top
        anchors.right: parent.right
        source: "qrc:/resources/icons/settings.svg"
        onClicked: _root.settings()
    }

    /*Loader {
        anchors.fill: parent
        //source: MainController.smallUI ? "SmallPlayer.qml" : "LargePlayer.qml"
        sourceComponent: MainController.smallUI ? small : large
        //property QtObject ctrl: _root.ctrl
    }*/
}

