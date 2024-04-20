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
    property int launcherRows: 4
    property int itemsPerPage: launcherColumns * launcherRows
    property string searchFilter: ""
    property var originalAppsList: []

    function totalPageCount() {
        var startIndex = 0;
        var endIndex = DesktopEntryReader.getGuiAppNames().length;
        var allApps = DesktopEntryReader.getGuiAppNames();
        var filteredApps = [];

        for (var i = startIndex; i < endIndex; i++) {
            if (allApps[i].toLowerCase().includes(searchFilter.toLowerCase())) {
                filteredApps.push(allApps[i]);
                console.log(allApps[i]);
            }
        }

        console.log("Filtered apps length: " + filteredApps.length + " itemsPerPage: " + itemsPerPage);

        return Math.ceil(filteredApps.length / itemsPerPage);
    }


    Keys.onEscapePressed: {
        viewManager.hideView();
        //console.log(DesktopEntryReader.getGuiAppNames());
    }

    Image {
        anchors.fill: root
        id: rootImage
        source: "file://home/aren/Firefox_wallpaper.png"
        smooth: true
        visible: false
    }

    Rectangle {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: 800
        height: 64
        radius: 8
        anchors.margins: {
            top: 16
        }

        /*RadialGradient {
            anchors.fill: parent
            //start: Qt.point(0,parent.height/2)
            //end: Qt.point(parent.width,parent.height/2)
            source: parent
            horizontalRadius: 750
            verticalRadius: 60

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ababab" }
                GradientStop { position: 1.0; color: "#e6e6e6" }
            }
        }*/

        opacity: 0.5
        color: "gray"

        TextArea {
            id: searchInput
            anchors.fill: parent
            width: parent.width
            height: parent.height
            anchors.margins: 4
            wrapMode: TextEdit.Wrap
            font.pixelSize: 24
            color: "black"
            verticalAlignment: TextEdit.AlignVCenter
            placeholderText: "Search..."

            onTextChanged: {
                searchFilter = searchInput.text;
                console.log("Search filter changed:", searchInput.text);
                //updateGrid();
                // Trigger updateGrid on all AppItemDelegates
                for (var i = 0; i < repeaterTop.count; ++i) {
                    var delegateItem = repeaterTop.itemAt(i);
                    delegateItem.updateGrid();
                }
            }

        }

    }

    function updateGrid() {
        var startIndex = swipeView.currentIndex * root.itemsPerPage;
        var endIndex = Math.min(startIndex + root.itemsPerPage, DesktopEntryReader.getGuiAppNames().length);
        var allApps = DesktopEntryReader.getGuiAppNames();
        var filteredApps = [];

        for (var i = startIndex; i < endIndex; i++) {
            if (allApps[i].toLowerCase().includes(searchFilter.toLowerCase())) {
                filteredApps.push(allApps[i]);
            }
        }

        return filteredApps; // Return the filtered apps array
    }

    SwipeView {
        id: swipeView
        currentIndex: 0
        anchors.fill: parent
        anchors.topMargin: 128
        anchors.rightMargin: 64
        anchors.leftMargin: 64
        anchors.bottomMargin: 64
        clip: true

        Repeater {
            id: repeaterTop
            model: root.totalPageCount()
            delegate: Item {
                id: delegate
                width: swipeView.width
                height: swipeView.height

                function updateGrid() {
                    // Get all app names
                    var allApps = DesktopEntryReader.getGuiAppNames();

                    // Clear the originalAppsList
                    originalAppsList = [];

                    // Populate originalAppsList with app names and indexes
                    for (var i = 0; i < allApps.length; i++) {
                        originalAppsList[i] = allApps[i];
                    }

                    //console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " + originalAppsList[23]);

                    // Update the model with filtered apps
                    appRepeater.model = updateFilteredApps();

                }

                function updateFilteredApps() {
                    var startIndex = swipeView.currentIndex * root.itemsPerPage;
                    var endIndex = Math.min(startIndex + root.itemsPerPage, DesktopEntryReader.getGuiAppNames().length);
                    var allApps = DesktopEntryReader.getGuiAppNames();
                    var filteredApps = [];

                    for (var i = startIndex; i < endIndex; i++) {
                        if (allApps[i].toLowerCase().includes(searchFilter.toLowerCase())) {
                            filteredApps.push(allApps[i]);
                        }
                    }

                    return filteredApps;
                }

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
                            appName: searchFilter === "" ? DesktopEntryReader.getGuiAppNames()[realIndex] : modelData
                            //iconIndex: searchFilter === "" ? realIndex : originalAppsList.indexOf(modelData)
                            iconIndex: appName
                            Layout.fillWidth: true
                            Layout.fillHeight: true
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
        count: searchFilter === "" ? swipeView.count : root.totalPageCount()
        currentIndex: searchFilter === "" ? swipeView.currentIndex : 0
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
