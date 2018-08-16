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
        engines.insert(window, engine);
        connect(window, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onQuickWindowClosing()));
        connect(window, &QQuickWindow::destroyed, [nef](){
            delete nef;
        });
        QObject::connect(window, SIGNAL(requestMinium()), this, SLOT(onRequestMinium()));
    }
}

void WindowController::onQuickWindowClosing()
{
    QObject *o = sender();
    o->deleteLater();
    if (engines.contains(o)) {
        engines.value(o)->deleteLater();
        engines.remove(o);
    }
}

void WindowController::onRequestMinium()
{
    QQuickWindow *window = (QQuickWindow *)sender();
    ShowWindow((HWND)window->winId(), SW_MINIMIZE);
}
