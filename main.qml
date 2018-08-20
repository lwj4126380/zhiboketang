import "ctrls"
import QtQuick 2.9

BorderlessWindow {
    id: root

    app_title: m_const.app_name
    Component.onCompleted: app_content_rect.setSource("qrc:/ctrls/Login.qml", {"root_window": root})
}
