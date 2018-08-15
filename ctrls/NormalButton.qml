import QtQuick 2.11
import QtQuick.Controls 2.4

Item {
    layer.enabled: true

    Rectangle {
        color: "white"
        radius: 4
        anchors.fill: parent
    }
    Rectangle {
        color: "white"
        anchors.fill: parent
        anchors.bottomMargin: 4
    }

    Button {
        anchors.centerIn: parent
        text: "AAAAA"
        onClicked: popDialog.open()
    }

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
