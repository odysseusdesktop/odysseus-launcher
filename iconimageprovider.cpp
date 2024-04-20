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

    // Check if the id is a valid integer (index)
    bool isIndex;
    int index = id.toInt(&isIndex);

    if (!isIndex) {
        // If id is not a valid integer, treat it as app name and find its index
        QStringList appNames = reader->getGuiAppNames();
        index = appNames.indexOf(id);
    }

    qDebug() << "IconImageProvider: " << index;

    if (index >= 0 && index < reader->getGuiAppIcons().size()) {
        return *reader->getGuiAppIcons()[index];
    } else {
        QIcon placeholderIcon = QIcon::fromTheme("unknown");
        return placeholderIcon.pixmap(64, 64).toImage();
    }
}
