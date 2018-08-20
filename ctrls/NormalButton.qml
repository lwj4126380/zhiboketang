import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11

Item {
    id: root
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

        SwipeView {
            id: loginSwipeView
            anchors.fill: parent

            currentIndex: 0

            Item {
                id: firstPage
                ColumnLayout {
                    anchors.fill: parent
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
                }

            }

            Item {
                id: secondPage
                BusyIndicator {
                    anchors.centerIn: parent
                }
            }


        }

        ToolTip {
            id: loginToolTip
            timeout: 3000
            y: parent.height-height
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

    Connections {
        target: m_iLiveHelper
        onShowTips: {
            loginToolTip.text = desc
            loginToolTip.visible = true
        }

        onLoginSuccess: loginSwipeView.currentIndex = 0
    }
}
