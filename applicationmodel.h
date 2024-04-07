#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QString>
#include <QImage>
#include <QFileInfo>
#include <KDesktopFile>
#include <KConfigGroup>

class ApplicationModel
{
public:
    ApplicationModel(KDesktopFile* desktopFile, bool flatpak);
    QString getName();
    QString getExec();
    QImage* getIcon();
    bool isGui();
    bool isFlatpak();
    void setIcon(QImage* icon);
private:
    bool flatpak;
    KDesktopFile* desktopFile;
    QImage* icon;
    QString name;
    QString exec;
};

#endif // APPLICATIONMODEL_H
