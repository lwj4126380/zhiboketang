import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtMultimedia 5.8

Item {
    id: root
    anchors.fill: parent

    RowLayout {
        anchors.fill: parent
        ComboBox {
            id: deviceCB
        }

        Button {
            text: "打开摄像头"
        }

        VideoOutput {
            id: videoOutput
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
