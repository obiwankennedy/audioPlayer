import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Customization
import Views
import Controllers

ScrollView {
    id: root

    signal clickOnItem(int index, var tags, var selected, var mouse)
    property alias currentIndex: view.currentIndex
    ListView {
        id: view
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.bottomMargin: 20

        Component.onCompleted: view.currentIndex = AppController.audioCtrl.songIndex

        highlightMoveDuration: 20

        highlight: Rectangle { color: Universal.accent; radius: 5 }

        Connections {
            target: AppController.audioCtrl
            function onSongIndexChanged() {
                view.positionViewAtIndex(AppController.audioCtrl.songIndex, ListView.Center)//view.ensureVisible(ctrl.audioCtrl.songIndex)
            }
        }
        focus: true
        clip: true
        model: AppController.filteredModel
        delegate:  Item {
            width: view.width
            height: 40
            clip: true
            Frame {
                id: control
                width: view.width
                height: 40

                ToolTip.text: tags

                RowLayout {
                    id: lyt
                    anchors.fill: parent
                    Label {//title
                        text: title
                        Layout.preferredWidth: lyt.width/2
                        font.bold: AppController.audioCtrl.songIndex === model.songIndex
                        clip: true
                    }
                    Label {//artist
                        text: artist
                        Layout.fillWidth: true
                        font.bold: AppController.audioCtrl.songIndex === model.songIndex
                    }
                    Label {//time
                        text: time
                        font.bold: AppController.audioCtrl.songIndex === model.songIndex
                    }
                }

                background: Rectangle {
                  color: model.selected ? "#0b3d8c" : model.isSelectedForExport ? "darkgreen" : "transparent"
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
                to: AppController.audioCtrl.duration
                value: AppController.audioCtrl.seek
                visible: AppController.audioCtrl.songIndex === model.songIndex

            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onDoubleClicked:{
                    AppController.audioCtrl.songIndex = model.songIndex;
                    AppController.audioCtrl.play()
                }
                onClicked: (mouse)=>{
                       root.clickOnItem(model.songIndex, tags,model.selected, mouse)
                }
            }
        }
    }
}
