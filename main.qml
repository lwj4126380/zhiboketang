import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

import "ctrls"

BorderlessWindow {
    id: root

    app_content_rect.source: "qrc:/ctrls/NormalButton.qml"
//    app_content_rect.sourceComponent: Rectangle {
//        anchors.fill: parent
//        color: "red"
//    }

//    Button {
//        parent: root.app_content_rect
//        id: testbtn
//        anchors.centerIn: root.app_content_rect
//        text: "AAAAA"
//        font.pointSize: 32

//        onParentChanged: {
////            console.log(testbtn.parent)
//        }
//    }
}
