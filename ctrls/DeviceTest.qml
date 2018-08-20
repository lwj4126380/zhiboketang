import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import com.fulaan.DeviceModel 1.0

Item {
    id: root
    anchors.fill: parent

    property var root_window

    RowLayout {
        anchors.fill: parent
        ComboBox {
            id: deviceCB
            textRole: "deviceName"
            enabled: count !== 0

            model: DeviceModel {
                id: deviceModel
                deviceType: DeviceModel.CameraDevice
            }

            onCountChanged: {
                if (count !== 0)
                    currentIndex = 0
            }
        }

        Button {
            text: "打开摄像头"
            onClicked: {
                deviceModel.addDevice("111111", "222222222")
            }
        }

        VideoOutput {
            id: videoOutput
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    Connections {
        target: root_window
        onRequestClose: {
            root_window.close()
        }
    }
}
