import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Controls.Material.impl 2.4
import QtGraphicalEffects 1.0

Rectangle {
    id: root

    readonly property int shadow_len: 10
    readonly property int win_radius: 4

    radius: win_radius
    color: "white"
    anchors.margins: shadow_len

    //no shadow if set
    //clip: true
    layer.enabled: true
    layer.effect: ElevationEffect {
        elevation: 4 //Material.elevation
    }
}
