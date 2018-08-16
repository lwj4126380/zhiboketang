#include "windowcontroller.h"
#include <QCoreApplication>
#include <QQuickWindow>
#include <QQmlContext>
#include <QDebug>
#include "cconstants.h"
#include "../os/cnativeeventfilter.h"

WindowController::WindowController(QObject *parent) : QObject(parent)
{

}

WindowController::~WindowController()
{
    qDebug() << "WindowController destroyed";
}

void WindowController::openMainView()
{   
    QQmlApplicationEngine *engine = new QQmlApplicationEngine();
    engine->rootContext()->setContextProperty("g_controller", this);
    engine->rootContext()->setContextProperty("m_const", CSingleton<CConstants>::Instance());
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    QList<QObject*> obs = engine->rootObjects();
    if (!obs.isEmpty()) {
        QQuickWindow *window = qobject_cast<QQuickWindow *>(obs.first());
        auto nef = new CNativeEventFilter((HWND)window->winId(), window);
        qApp->installNativeEventFilter(nef);
        engines.insert(window, QPair<QQmlApplicationEngine*, void*>(engine, nef));
        connect(window, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onQuickWindowClosing()));
    }
}

void WindowController::onQuickWindowClosing()
{
    QObject *o = sender();
    o->deleteLater();
    if (engines.contains(o)) {
        engines.value(o).first->deleteLater();
        engines.remove(o);
        delete engines.value(o).second;
    }
}
