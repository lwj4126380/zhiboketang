import "ctrls"

BorderlessWindow {
    id: root

    app_title: m_const.app_name
    Component.onCompleted: app_content_rect.setSource("qrc:/ctrls/NormalButton.qml", {"root_window": root})
}
