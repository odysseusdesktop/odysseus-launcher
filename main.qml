import QtQuick 2.9
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.14
import DesktopEntryReader 1.0

Item {
    id: root
    width: 1920
    height: 1080
    visible: true
    focus: true

    property int launcherColumns: 8
    property int launcherRows: 5
    property int itemsPerPage: launcherColumns * launcherRows

    function totalPageCount() {
        return Math.ceil(DesktopEntryReader.getGuiAppNames().length / itemsPerPage);
    }

    Keys.onEscapePressed: {
        viewManager.hideView();
        console.log(DesktopEntryReader.getGuiAppNames());
    }

    Image {
        anchors.fill: root
        id: rootImage
        source: "file://home/aren/Firefox_wallpaper.png"
        smooth: true
        visible: false
    }

    SwipeView {
        id: swipeView
        currentIndex: 0
        anchors.fill: parent
        anchors.margins: 64
        clip: true

        Repeater {
            model: root.totalPageCount()
            delegate: Item {
                width: swipeView.width
                height: swipeView.height


                GridLayout {
                    id: grid
                    anchors.fill: parent
                    columns: launcherColumns
                    rows: launcherRows
                    columnSpacing: 64
                    rowSpacing: 128
                    anchors.margins: 64
                    z: 1

                    Repeater {
                        id: appRepeater
                        model: []
                        delegate: AppItemDelegate {
                            property int realIndex: index + swipeView.currentIndex * root.itemsPerPage
                            appName: DesktopEntryReader.getGuiAppNames()[realIndex]
                            iconIndex: realIndex
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                        }

                        function updateGrid() {
                            var startIndex = swipeView.currentIndex * root.itemsPerPage;
                            var endIndex = Math.min(startIndex + root.itemsPerPage, DesktopEntryReader.getGuiAppNames().length);
                            var visibleApps = DesktopEntryReader.getGuiAppNames().slice(startIndex, endIndex);
                            appRepeater.model = visibleApps;
                        }

                        Component.onCompleted: {
                            updateGrid();
                        }
                    }
                }
            }
        }
    }

    FastBlur {
        z: -999
        anchors.fill: rootImage
        source: rootImage
        radius: 64
    }

    PageIndicator {
        id: pageIndicator
        count: swipeView.count
        currentIndex: swipeView.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
