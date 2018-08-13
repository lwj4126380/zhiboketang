import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Rectangle {
    property var parent_dlg

    anchors.fill: parent
    anchors.margins: parent_dlg.shadow_len
    radius: parent_dlg.radius
    color: Material.backgroundDimColor
    Behavior on opacity {
        NumberAnimation {
            duration: 150
        }
    }
}
