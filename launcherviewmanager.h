#ifndef LAUNCHERVIEWMANAGER_H
#define LAUNCHERVIEWMANAGER_H

#include <QObject>
#include <QQuickView>

class LauncherViewManager : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Odysseus Launcher View Manager", "me.aren.OdysseusLauncher.LauncherViewManager")
public:
    explicit LauncherViewManager(QQuickView* view);
public slots:
    void hideView();
    void showView();
private:
    QQuickView* view;
};

#endif // LAUNCHERVIEWMANAGER_H
