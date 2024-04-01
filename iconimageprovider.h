#ifndef ICONIMAGEPROVIDER_H
#define ICONIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QString>
#include <QSize>
#include "desktopentryreader.h"

class IconImageProvider : public QQuickImageProvider
{
public:
    IconImageProvider(DesktopEntryReader* reader);
    QImage requestImage(const QString &id, QSize* size, const QSize& requestedSize) override;
private:
    DesktopEntryReader* reader;
};

#endif // ICONIMAGEPROVIDER_H
