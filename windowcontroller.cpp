#include "windowcontroller.h"
#include <QQuickWindow>
#include <QQmlContext>
#include <QDebug>

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
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    QList<QObject*> obs = engine->rootObjects();
    if (!obs.isEmpty()) {
        QQuickWindow *window = qobject_cast<QQuickWindow *>(obs.first());
        engines.insert(window, engine);
        connect(window, SIGNAL(closing(QQuickCloseEvent*)), this, SLOT(onQuickWindowClosing()));
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
