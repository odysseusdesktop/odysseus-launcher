#include "iconimageprovider.h"

IconImageProvider::IconImageProvider(DesktopEntryReader *reader)
    : QQuickImageProvider(QQuickImageProvider::Image),
      reader(reader)
{

}

QImage IconImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)

    bool ok;
    int index = id.toInt(&ok);
    if (ok && index >= 0 && index < this->reader->getGuiAppIcons().size()) {
        return *this->reader->getGuiAppIcons()[index];
    } else {
        QIcon placeholderIcon = QIcon::fromTheme("unknown");
        return placeholderIcon.pixmap(64, 64).toImage();
    }
}
