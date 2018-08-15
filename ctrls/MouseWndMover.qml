import QtQuick 2.11

MouseArea{
    id: ma

    property int wnd_offset
    property var wnd_move_target
    property var wnd_anchor

    property real pressed_x
    property real pressed_y
    property bool is_pressed: false
    property point origin_pos
    property int padding_test: 4
    property int direction

    cursorShape: "ArrowCursor"
    anchors.fill: wnd_anchor
    hoverEnabled: true

    function onMouseChange(x, y) {
        if (x < 0 || y < 0) {
            return;
        }
        var rx = (x >= origin_pos.x) ? origin_pos.x : x
        var ry = (y >= origin_pos.y) ? origin_pos.y : y
        var rw = Math.abs(x - origin_pos.x)
        var rh = Math.abs(y - origin_pos.y)

        wnd_move_target.x = rx
        wnd_move_target.y = ry
//        if (direction != 7 && direction !=8)
            wnd_move_target.width = rw
//        if (direction != 5 && direction != 6)
            wnd_move_target.height = rh
    }

    function getDirection(x, y, top_left, bottom_right) {
        top_left.x -= m_const.shadow_len
        top_left.y -= m_const.shadow_len
        bottom_right.x -= m_const.shadow_len;
        bottom_right.y -= m_const.shadow_len
        var ret_dir
        if(top_left.x + padding_test >= x
                && top_left.x <= x
                && top_left.y + padding_test >= y
                && top_left.y <= y) {
            // 左上角
            ret_dir = 1;
            ma.cursorShape = Qt.SizeFDiagCursor
        } else if(x >= bottom_right.x - padding_test
                  && x <= bottom_right.x
                  && y >= bottom_right.y - padding_test
                  && y <= bottom_right.y) {
            // 右下角
            ret_dir = 2;
            ma.cursorShape = Qt.SizeFDiagCursor
        } else if(x <= top_left.x + padding_test
                  && x >= top_left.x
                  && y >= bottom_right.y - padding_test
                  && y <= bottom_right.y) {
            // 左下角
            ret_dir = 3;
            ma.cursorShape = Qt.SizeBDiagCursor
        } else if(x <= bottom_right.x
                  && x >= bottom_right.x - padding_test
                  && y >= top_left.y
                  && y <= top_left.y + padding_test) {
            // 右上角
            ret_dir = 4;
            ma.cursorShape = Qt.SizeBDiagCursor
        } else if(x <= top_left.x + padding_test
                  && x >= top_left.x) {
            // 左边
            ret_dir = 5;
            ma.cursorShape = Qt.SizeHorCursor
        } else if( x <= bottom_right.x
                  && x >= bottom_right.x - padding_test) {
            // 右边
            ret_dir = 6;
            ma.cursorShape = Qt.SizeHorCursor
        }else if(y >= top_left.y
                 && y <= top_left.y + padding_test){
            // 上边
            ret_dir = 7;
            ma.cursorShape = Qt.SizeVerCursor
        } else if(y <= bottom_right.y
                  && y >= bottom_right.y - padding_test) {
            // 下边
            ret_dir = 8;
            ma.cursorShape = Qt.SizeVerCursor
        }else {
            // 默认
            ret_dir = 0;
            ma.cursorShape = Qt.ArrowCursor
        }
        return ret_dir;
    }

    onPressed: {
        ma.pressed_x = mouse.x
        ma.pressed_y = mouse.y
        ma.is_pressed = true
    }
    onPositionChanged: {
        var rect = Qt.rect(wnd_anchor.x, wnd_anchor.y, wnd_anchor.width, wnd_anchor.height)

        var g_pos = wnd_anchor.mapToGlobal(mouse.x, mouse.y)
        var pt_tl = wnd_anchor.mapToGlobal(rect.x, rect.y)
        var pt_bl = wnd_anchor.mapToGlobal(rect.x, rect.y+rect.height)
        var pt_tr = wnd_anchor.mapToGlobal(rect.x+rect.width, rect.y)
        var pt_br = wnd_anchor.mapToGlobal(rect.x+rect.width, rect.y+rect.height)
        //上7 下8 左5 右6 左上1 右下2 左下3 右上4
        if (!ma.is_pressed){
            direction = getDirection(g_pos.x, g_pos.y, pt_tl, pt_br)
            switch(direction) {
            case 6:
            case 2:
            case 0:
                origin_pos = pt_tl
                break
            case 4:
                origin_pos = pt_bl
                break
            case 5:
            case 3:
                origin_pos = pt_tr
                break
            case 1:
            case 7:
                origin_pos = pt_br
                break
            case 8:
                origin_pos = pt_tl
                break
            }

            mouse.accept = true
        } else {
            if (direction != 0) {
                switch(direction) {
                case 5:
                    onMouseChange(g_pos.x, pt_bl.y)
                    break
                case 6:
                    onMouseChange(g_pos.x, pt_br.y)
                    break
                case 7:
                    onMouseChange(pt_tl.x, g_pos.y)
                    break
                case 8:
                    onMouseChange(pt_br.x, g_pos.y)
                    break
                case 1:
                case 2:
                case 3:
                case 4:
                    onMouseChange(g_pos.x, g_pos.y)
                    break
                default:
                    break;
                }
            }
        }
    }
    onReleased:{
        ma.is_pressed = false
    }
}
