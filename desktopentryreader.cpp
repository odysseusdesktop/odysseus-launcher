#include "desktopentryreader.h"
#include <QDebug>

DesktopEntryReader::DesktopEntryReader(QObject *parent)
    : QObject{parent}
{
    QList<QDir> searchDirs;
    QDir applicationsDir{this->searchDirectory};
    searchDirs.append(applicationsDir);
    QDir flatpakDir{this->flatpakSearchDirectory};

    for(QString flatpakAppName : flatpakDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QDir flatpakAppDir {flatpakDir.absolutePath() + "/" + flatpakAppName + "/current/active/files/share/applications/"};
        qDebug() << "Found flatpak: " << flatpakAppName;
        searchDirs.append(flatpakAppDir);
    }

    for(QDir dir : searchDirs) {
        bool isFlatpakDir = dir.absolutePath().contains("flatpak");
        qDebug() << dir.absolutePath();
        QStringList desktopFiles = dir.entryList(QStringList() << "*.desktop", QDir::Files);

        for(QString filename : desktopFiles) {
            qDebug() << "Reading: " << filename;
            qDebug() << dir.filePath(filename);
            KDesktopFile* desktopFile = new KDesktopFile(dir.filePath(filename));
            ApplicationModel* app = new ApplicationModel{desktopFile, isFlatpakDir};

            if(app->isGui()) {
                QIcon appIcon = QIcon::fromTheme(desktopFile->readIcon());
                QPixmap pixmap = appIcon.pixmap(QSize(64, 64));
                QImage* image = new QImage(pixmap.toImage());
                app->setIcon(image);
            }

            this->apps.append(app);
        }
    }
}

DesktopEntryReader::~DesktopEntryReader()
{
    qDeleteAll(apps);
}

QStringList DesktopEntryReader::getGuiAppNames()
{
    QStringList guiAppNames;
    /*for(KDesktopFile* desktopFile : this->desktopFiles) {
        if(isGui(*desktopFile)) {
            guiAppNames.append(desktopFile->readName());
        }
    }*/

    for(ApplicationModel* app : this->apps) {
        if(app->isGui())
            guiAppNames.append(app->getName());
    }

    return guiAppNames;
}

QImage DesktopEntryReader::getIconImage(int index)
{
    //return *this->iconImages[index];
    return *this->apps[index]->getIcon();
}

QString DesktopEntryReader::getExec(int index)
{
    QStringList execs;
    /*for(KDesktopFile* desktopFile : this->desktopFiles) {
        if(isGui(*desktopFile)) {
            execs.append((desktopFile->desktopGroup().readEntry("Exec", "") == "") ? desktopFile->desktopGroup().readEntry("TryExec", "") : desktopFile->desktopGroup().readEntry("Exec", ""));
        }
    }*/

    for(ApplicationModel* app : this->apps) {
        if(app->isGui())
            execs.append(app->getExec());
    }

    return execs[index];
}

QList<QImage*> DesktopEntryReader::getGuiAppIcons()
{
    QList<QImage*> icons;

    for(ApplicationModel* app : this->apps) {
        if(app->isGui())
            icons.append(app->getIcon());
    }

    return icons;
}
