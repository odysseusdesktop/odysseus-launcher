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

private:
    bool isGui(KDesktopFile& file);
    QString searchDirectory {"/usr/share/applications/"};
    QList<QImage*> iconImages;
    QList<KDesktopFile*> desktopFiles;
};

#endif // DESKTOPENTRYREADER_H
