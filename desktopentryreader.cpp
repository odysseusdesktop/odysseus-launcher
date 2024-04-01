#include "desktopentryreader.h"
DesktopEntryReader::DesktopEntryReader(QObject *parent)
    : QObject{parent}
{
    QDir searchDir{this->searchDirectory};
    QStringList desktopFiles = searchDir.entryList(QStringList() << "*.desktop", QDir::Files);

    for(QString filename : desktopFiles) {
        KDesktopFile* desktopFile = new KDesktopFile(searchDir.filePath(filename));

        if(isGui(*desktopFile)) {
            QIcon appIcon = QIcon::fromTheme(desktopFile->readIcon());
            QPixmap pixmap = appIcon.pixmap(QSize(64, 64));
            QImage* image = new QImage(pixmap.toImage());
            this->iconImages.append(image);
        }

        this->desktopFiles.append(desktopFile);
    }
}

DesktopEntryReader::~DesktopEntryReader()
{
    qDeleteAll(desktopFiles);
    qDeleteAll(iconImages);
}

QStringList DesktopEntryReader::getGuiAppNames()
{
    QStringList guiAppNames;
    for(KDesktopFile* desktopFile : this->desktopFiles) {
        if(isGui(*desktopFile)) {
            guiAppNames.append(desktopFile->readName());
        }
    }

    return guiAppNames;
}

QImage DesktopEntryReader::getIconImage(int index)
{
    return *this->iconImages[index];
}

QString DesktopEntryReader::getExec(int index)
{
    QStringList execs;
    for(KDesktopFile* desktopFile : this->desktopFiles) {
        if(isGui(*desktopFile)) {
            execs.append((desktopFile->desktopGroup().readEntry("Exec", "") == "") ? desktopFile->desktopGroup().readEntry("TryExec", "") : desktopFile->desktopGroup().readEntry("Exec", ""));
        }
    }

    return execs[index];
}

bool DesktopEntryReader::isGui(KDesktopFile &file)
{
    //desktopFile->desktopGroup().readEntry("Terminal", true) == false
    return !file.desktopGroup().readEntry("Terminal", true) && file.desktopGroup().readEntry("Icon", "") != "";
}

QList<QImage*> DesktopEntryReader::getGuiAppIcons()
{
    return this->iconImages;
}
