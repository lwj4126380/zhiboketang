import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4

Item {
    layer.enabled: true
    Rectangle {
        color: "white"
        radius: m_const.wnd_radius
        anchors.fill: parent
    }
    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.bottomMargin: m_const.wnd_radius
    }

    Button {
        anchors.centerIn: parent
        text: "AAAAA"
        Material.background: "red"
        Material.foreground: "white"
        onClicked: g_controller.openMainView()
    }

//    BusyIndicator {
//        anchors.fill: parent
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
