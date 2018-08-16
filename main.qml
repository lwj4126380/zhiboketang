import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

import "ctrls"

BorderlessWindow {
    id: root

    app_title: m_const.app_name
    Component.onCompleted: app_content_rect.setSource("qrc:/ctrls/NormalButton.qml", {"root_window": root})
}
