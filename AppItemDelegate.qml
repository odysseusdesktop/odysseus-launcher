import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import ProcessHelper 1.0
import DesktopEntryReader 1.0

Item {
    width: 64
    height: 64

    property int iconIndex
    property string appName


    Image {
        anchors.top: parent.top
        id: icon
        source: "image://icontheme/" + iconIndex

        MouseArea {
            anchors.fill: parent

            onClicked: {
                ProcessHelper.start(DesktopEntryReader.getExec(iconIndex));
                viewManager.hideView();
            }
        }
    }

    Text {
        anchors.horizontalCenter: icon.horizontalCenter
        anchors.top: icon.bottom
        anchors.topMargin: 8
        text: appName
        color: "white"
        wrapMode: Text.Wrap
    }
}
