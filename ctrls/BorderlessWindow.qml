import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

ApplicationWindow {
    id: root

    width: 640
    height: 480

    visible: true
    title: "luweijia"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint

    Material.theme: Material.Light
    Material.accent: Material.Pink
    Material.background: Material.background
    font.family: "Microsoft YaHei"

    property var app_center_rect: center_rect

    WndContainer {
        id: main_box
        anchors.fill: root.contentItem
    }
    MouseWndMover {
        wnd_offset: main_box.shadow_len
        wnd_anchor: main_box
        wnd_move_target: root
    }

    Rectangle {
        id: center_rect
        anchors.fill: main_box
        radius: main_box.win_radius
    }

//    Button {
//        anchors.fill: main_box
//        text: "AAAAAAAAA"
//        onClicked: {
//            popDialog.open()
//        }
//    }

    Dialog {
        id: popDialog
        modal: true
        implicitWidth: 320
        implicitHeight: 240
        standardButtons: Dialog.Ok
        parent: Overlay.overlay
        Overlay.modal: OverlayCom {
            parent_dlg: main_box
        }
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        Text {
            id: name
            anchors.centerIn: parent
            text: qsTr("Hello World")
        }
    }
}
