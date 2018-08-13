import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

import "ctrls"

BorderlessWindow {
    id: root

    Button {
        anchors.centerIn: root.app_center_rect
        text: "AAAAA"
        font.pointSize: 32
    }
}
