import QtQuick 2.11

MouseArea{
    id: ma

    property int wnd_offset
    property var wnd_move_target
    property var wnd_anchor

    property bool is_pressed: false
    property point origin_pos
    property int padding_test: 4
    property int direction
    property point last_pos
    property point cur_pos
    property bool scale_enable

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

        wnd_move_target.x = rx - m_const.shadow_len
        wnd_move_target.y = ry - m_const.shadow_len

        var d_x = 0, d_y = 0
        if (direction === 7 || direction === 5 || direction === 1 ) {
            d_x = last_pos.x - cur_pos.x
            d_y = last_pos.y - cur_pos.y
        } else if (direction === 3) {
            d_x = last_pos.x - cur_pos.x
            d_y = cur_pos.y - last_pos.y
        } else if (direction === 4) {
            d_x = cur_pos.x - last_pos.x
            d_y = last_pos.y - cur_pos.y
        } else {
            d_x = cur_pos.x - last_pos.x
            d_y = cur_pos.y - last_pos.y
        }


        if (rw !== wnd_anchor.width)
            wnd_move_target.width += d_x

        if (rh !== wnd_anchor.height)
            wnd_move_target.height += d_y

        last_pos = cur_pos
    }

    function getDirection(x, y, top_left, bottom_right) {
        var ret_dir = 0
        if(top_left.x + padding_test >= x
                && top_left.x <= x
                && top_left.y + padding_test >= y
                && top_left.y <= y) {
            // 左上角
//            ret_dir = 1;
//            ma.cursorShape = Qt.SizeFDiagCursor
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
//            ret_dir = 3;
//            ma.cursorShape = Qt.SizeBDiagCursor
        } else if(x <= bottom_right.x
                  && x >= bottom_right.x - padding_test
                  && y >= top_left.y
                  && y <= top_left.y + padding_test) {
            // 右上角
//            ret_dir = 4;
//            ma.cursorShape = Qt.SizeBDiagCursor
        } else if(x <= top_left.x + padding_test
                  && x >= top_left.x) {
            // 左边
//            ret_dir = 5;
//            ma.cursorShape = Qt.SizeHorCursor
        } else if( x <= bottom_right.x
                  && x >= bottom_right.x - padding_test) {
            // 右边
            ret_dir = 6;
            ma.cursorShape = Qt.SizeHorCursor
        }else if(y >= top_left.y
                 && y <= top_left.y + padding_test){
            // 上边
//            ret_dir = 7;
//            ma.cursorShape = Qt.SizeVerCursor
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
        if (!scale_enable)
            return
        last_pos = wnd_anchor.mapToGlobal(mouse.x, mouse.y)
        is_pressed = true
    }
    onPositionChanged: {
        if (!scale_enable)
            return
        var rect = Qt.rect(0, 0, wnd_anchor.width, wnd_anchor.height)

        cur_pos = wnd_anchor.mapToGlobal(mouse.x, mouse.y)
        var pt_tl = wnd_anchor.mapToGlobal(rect.x, rect.y)
        var pt_bl = wnd_anchor.mapToGlobal(rect.x, rect.y+rect.height)
        var pt_tr = wnd_anchor.mapToGlobal(rect.x+rect.width, rect.y)
        var pt_br = wnd_anchor.mapToGlobal(rect.x+rect.width, rect.y+rect.height)
        //上7 下8 左5 右6 左上1 右下2 左下3 右上4
        if (!ma.is_pressed){
            direction = getDirection(cur_pos.x, cur_pos.y, pt_tl, pt_br)
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
                if (cur_pos.x - pt_tl.x < m_const.wnd_min_width-2*m_const.shadow_len)
                    cur_pos.x = pt_tl.x + m_const.wnd_min_width-2*m_const.shadow_len

                if (cur_pos.y - pt_tl.y < m_const.wnd_min_height-2*m_const.shadow_len)
                    cur_pos.y = pt_tl.y + m_const.wnd_min_height-2*m_const.shadow_len

                switch(direction) {
                case 5:
                    onMouseChange(cur_pos.x, pt_bl.y)
                    break
                case 6:
                    onMouseChange(cur_pos.x, pt_br.y)
                    break
                case 7:
                    onMouseChange(pt_tl.x, cur_pos.y)
                    break
                case 8:
                    onMouseChange(pt_br.x, cur_pos.y)
                    break
                case 1:
                case 2:
                case 3:
                case 4:
                    onMouseChange(cur_pos.x, cur_pos.y)
                    break
                default:
                    break;
                }
            } else {
                var d_x = cur_pos.x - last_pos.x
                var d_y = cur_pos.y - last_pos.y
                wnd_move_target.x += d_x
                wnd_move_target.y += d_y

                last_pos = cur_pos
            }
        }
    }
    onReleased:{
        if (!scale_enable)
            return
        is_pressed = false
        cursorShape = Qt.ArrowCursor
    }
}
