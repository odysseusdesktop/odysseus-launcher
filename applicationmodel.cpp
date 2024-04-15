#include "applicationmodel.h"
#include <QDebug>

ApplicationModel::ApplicationModel(KDesktopFile* desktopFile, bool flatpak)
    : desktopFile(desktopFile),
      icon(nullptr)
{
    this->flatpak = flatpak;
    this->name = desktopFile->readName();
    this->exec = desktopFile->desktopGroup().readEntry("Exec", "");

    if (flatpak) {
        // Get the directory of the desktop file
        QString desktopFilePath = desktopFile->name();
        QFileInfo desktopFileInfo(desktopFilePath);
        QString desktopFileDir = desktopFileInfo.absolutePath();
        QString flatpakAppName = desktopFileDir.split("/")[5];


        this->exec = "flatpak run " + flatpakAppName;
    }
}

QString ApplicationModel::getName() {
    return this->name;
}

QString ApplicationModel::getExec() {
    return this->exec;
}

QImage *ApplicationModel::getIcon() {
    return this->icon;
}

bool ApplicationModel::isGui() {
    if (desktopFile == nullptr) {
        return false;
    }

    QString terminal = desktopFile->desktopGroup().readEntry("Terminal", "");
    QString icon = desktopFile->desktopGroup().readEntry("Icon", "");
    QString startupWMClass = desktopFile->desktopGroup().readEntry("StartupWMClass", "");
    QString genericName = desktopFile->readGenericName();

    bool isGui = (!terminal.toLower().trimmed().compare("false") && !icon.isEmpty()) || !startupWMClass.isEmpty() || !genericName.isEmpty();

    return isGui;
}


bool ApplicationModel::isFlatpak() {
    return this->flatpak;
}

void ApplicationModel::setIcon(QImage* icon) {
    this->icon = icon;
}

