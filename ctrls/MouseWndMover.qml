import QtQuick 2.11

MouseArea{
    id: ma

    property int wnd_offset
    property var wnd_move_target
    property var wnd_anchor

    property real pressed_x
    property real pressed_y
    property bool is_pressed: false

    cursorShape: "ArrowCursor"
    anchors.fill: wnd_anchor
    onPressed: {
        ma.pressed_x = mouse.x
        ma.pressed_y = mouse.y
        ma.is_pressed = true
    }
    onPositionChanged: {
        if (ma.is_pressed){
            var p = wnd_anchor.mapToGlobal(0, 0)
            wnd_move_target.x = p.x + mouse.x - ma.pressed_x - wnd_offset
            wnd_move_target.y = p.y + mouse.y - ma.pressed_y - wnd_offset
            mouse.accept = true
        }
    }
    onReleased:{
        ma.is_pressed = false
    }
}
