#ifndef DESKTOPENTRYREADER_H
#define DESKTOPENTRYREADER_H

#include <QObject>
#include <QList>
#include <QString>
#include <QDir>
#include <QIcon>
#include <QImage>
#include <QPixmap>
#include <KDesktopFile>
#include <KConfigGroup>
#include "applicationmodel.h"

class DesktopEntryReader : public QObject
{
    Q_OBJECT
public:
    explicit DesktopEntryReader(QObject *parent = nullptr);
    virtual ~DesktopEntryReader();
    QList<QImage*> getGuiAppIcons();
public slots:
    QStringList getGuiAppNames();
    QImage getIconImage(int index);
    QString getExec(int index);
    QString getExecByName(QString appName);

private:
    QString searchDirectory{"/usr/share/applications/"};
    QString flatpakSearchDirectory{"/var/lib/flatpak/app/"};
    QList<ApplicationModel*> apps;
};

#endif // DESKTOPENTRYREADER_H
