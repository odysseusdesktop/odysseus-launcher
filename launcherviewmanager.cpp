#include "launcherviewmanager.h"

LauncherViewManager::LauncherViewManager(QQuickView* view)
    : view(view)
{

}

void LauncherViewManager::hideView()
{
    view->hide();
}

void LauncherViewManager::showView()
{
    view->showFullScreen();
}
