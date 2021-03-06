import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11


SwipeView {
    id: loginSwipeView
    objectName: "swipeview"
    anchors.fill: parent
    currentIndex: 0
    interactive: false

    property var root_window

    Item {
        id: firstPage
        ColumnLayout {
            anchors.fill: parent
            TextField {
                id: className
                Layout.alignment: Qt.AlignHCenter
            }

            Button {
                id: loginBtn
                Layout.alignment: Qt.AlignHCenter
                text: "登录"
                Material.background: "red"
                Material.foreground: "white"
                onClicked: {
                    loginSwipeView.currentIndex = 1
                    m_iLiveHelper.doLogin("luweijia", "11111111")
                }
            }

            Button {
                id: deviceTestBtn
                Layout.alignment: Qt.AlignHCenter
                text: "设备测试"
                onClicked: {
                    m_iLiveHelper.doDeviceTest()
                }
            }

            Button {
                id: startClass
                Layout.alignment: Qt.AlignHCenter
                text: "开始上课"
                onClicked: {
                    m_iLiveHelper.doBeginLive()
                }
            }
        }

    }

    Item {
        id: secondPage
        BusyIndicator {
            anchors.centerIn: parent
        }
    }
    ToolTip {
        id: loginToolTip
        timeout: 3000
        y: parent.height - height
    }


    Connections {
        target: m_iLiveHelper
        onShowTips: {
            loginToolTip.text = desc
            loginToolTip.visible = true
        }

        onLoginSuccess: loginSwipeView.currentIndex = 0
    }

    Connections {
        target: root_window
        onRequestClose: {
            root_window.close()
        }
    }
}



//    Dialog {
//        id: popDialog
//        modal: true
//        implicitWidth: 320
//        implicitHeight: 240
//        standardButtons: Dialog.Ok
//        parent: Overlay.overlay
//        Overlay.modal: OverlayCom {
//            parent_dlg: main_box
//        }
//        x: (parent.width - width) / 2
//        y: (parent.height - height) / 2
//        Text {
//            id: name
//            anchors.centerIn: parent
//            text: qsTr("Hello World")
//        }
//    }
