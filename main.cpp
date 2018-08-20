#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickStyle>
#include <QDebug>
#include "utils/windowcontroller.h"
#include "utils/frameprovider.h"
#include "models/devicemodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickWindow::setDefaultAlphaBuffer(true);
    QQuickStyle::setStyle("Material");

    qmlRegisterType<FrameProvider>("com.fulaan.FrameProvider", 1, 0, "FrameProvider");
    qmlRegisterType<DeviceModel>("com.fulaan.DeviceModel", 1, 0, "DeviceModel");

    WindowController controller;

    controller.openSpecificView("qrc:/main.qml");
    return app.exec();
}
