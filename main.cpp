#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickStyle>
#include <QDebug>
#include "windowcontroller.h"
#include "frameprovider.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickWindow::setDefaultAlphaBuffer(true);
    QQuickStyle::setStyle("Material");

    qmlRegisterType<FameProvider>("com.fulaan.FrameProvider", 1, 0, "FrameProvider");

    WindowController controller;

    controller.openMainView();
    return app.exec();
}
