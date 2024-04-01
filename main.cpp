#include <QGuiApplication>
#include <QQmlContext>
#include <QDBusConnection>
#include "launcherviewmanager.h"
#include "desktopentryreader.h"
#include "iconimageprovider.h"
#include "processhelper.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DesktopEntryReader* reader = new DesktopEntryReader;
    ProcessHelper* processHelper = new ProcessHelper;

    qmlRegisterSingletonInstance<DesktopEntryReader>("DesktopEntryReader", 1, 0, "DesktopEntryReader", reader);
    qmlRegisterSingletonInstance<ProcessHelper>("ProcessHelper", 1, 0, "ProcessHelper", processHelper);

    QQuickView* view = new QQuickView;
    IconImageProvider* imageProvider = new IconImageProvider(reader);
    view->engine()->addImageProvider(QLatin1String("icontheme"), imageProvider);
    view->setSource(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    view->setColor(Qt::transparent);

    LauncherViewManager viewManager{view};
    view->rootContext()->setContextProperty("viewManager", &viewManager);

    view->showFullScreen();

    if(!QDBusConnection::sessionBus().registerService("me.aren.OdysseusLauncher")) qWarning() << "Cannot register service to the D-Bus session bus.";
    if(!QDBusConnection::sessionBus().registerObject("/LauncherViewManager", &viewManager, QDBusConnection::ExportAllSlots)) qWarning() << "Cannot register object to the D-Bus session bus.";

    return app.exec();
}
