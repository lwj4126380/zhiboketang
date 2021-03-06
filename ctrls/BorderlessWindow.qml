import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.11
import QtQuick.Window 2.11

ApplicationWindow {
    id: root

    signal requestMinium()
    signal requestClose()

    width: m_const.wnd_min_width
    height: m_const.wnd_min_height

    minimumWidth: m_const.wnd_min_width
    minimumHeight: m_const.wnd_min_height

    visible: true
    title: "luweijia"
    color: "transparent"
    flags: Qt.FramelessWindowHint | Qt.Window | Qt.WindowMinimizeButtonHint

    Material.theme: Material.Light
    Material.accent: Material.Pink
    Material.background: Material.background
    font.family: "Microsoft YaHei"

    property alias app_content_rect: center_rect.r_p_c_rect
    property var app_title

    function setWindowMaxi() {
        if (root.visibility !== Window.Maximized) {
            main_box.shadow_len = 0
            root.showMaximized()
        } else {
            main_box.shadow_len = m_const.shadow_len
            root.showNormal()
        }
    }

    function setWindowMini() {
        requestMinium()
    }

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
        property alias r_p_c_rect: cl.p_c_rect

        ColumnLayout {
            id: cl
            anchors.fill: parent
            property alias p_c_rect: content_rect
            Item {
                id: title_rect
                implicitWidth: cl.width
                implicitHeight: 60

                Rectangle {
                    color: "white"
                    radius: main_box.win_radius
                    anchors.fill: parent
                }
                Rectangle {
                    color: "white"
                    anchors.fill: parent
                    anchors.topMargin: main_box.win_radius
                }

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 5
                    anchors.rightMargin: 5
                    Layout.alignment: Qt.AlignVCenter
                    Text {
                        id: title_text
                        Layout.fillWidth: true
                        height: title_rect.height
                        text: qsTr(app_title)
                    }

                    Button {
                        text: qsTr("mini")
                        onClicked: setWindowMini()
                    }
                    Button {
                        text: qsTr("max")
                        onClicked: setWindowMaxi()
                    }
                    Button {
                        text: qsTr("close")
                        onClicked: requestClose()
                    }
                }


            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
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

                Loader {
                    id: content_rect
                    anchors.fill: parent
                    anchors.leftMargin: m_const.wnd_radius
                    anchors.rightMargin: m_const.wnd_radius
                    anchors.bottomMargin: m_const.wnd_radius
                    anchors.topMargin: 0
                }
            }
        }

    }
}
