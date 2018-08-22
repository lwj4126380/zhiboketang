import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtMultimedia 5.8

import com.fulaan.DeviceModel 1.0
import com.fulaan.FrameProvider 1.0

Item {
    id: root
    anchors.fill: parent

    property var root_window

    function getComboboxCurrentValue(combobox) {
        var mi = combobox.model.index(combobox.currentIndex, 0)
        return combobox.model.getIndexValue(mi)
    }

    RowLayout {
        anchors.fill: parent
        ComboBox {
            id: deviceCB
            textRole: "deviceName"
            enabled: count !== 0

            model: DeviceModel {
                deviceType: DeviceModel.CameraDevice
            }

            onCountChanged: {
                if (count !== 0)
                    currentIndex = 0
            }
        }

        Button {
            id: cameraBtn
            text: "打开摄像头"
            onClicked: {
                if (deviceCB.count === 0) {
                    deviceToolTip.text = "无可用设备"
                    deviceToolTip.visible = true
                } else {
                    var deviceId = getComboboxCurrentValue(deviceCB)
                    if (m_iLiveHelper.getDeviceState(0))
                        m_iLiveHelper.closeCamera()
                    else
                        m_iLiveHelper.openCamera(deviceId)
                    cameraBtn.enabled =false
                }
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "black"
            VideoOutput {
                id: videoOutput
                anchors.fill: parent
                source: camera
            }
        }

        FrameProvider {
            id: camera
        }
    }

    ToolTip {
        id: deviceToolTip
        timeout: 3000
        y: parent.height - height
    }

    Connections {
        target: root_window
        onRequestClose: {
            root_window.close()
        }

        onClosing: m_iLiveHelper.doStopDeviceTest()
    }

    Connections {
        target: m_iLiveHelper
        onShowTips: {
            deviceToolTip.text = desc
            deviceToolTip.visible = true
        }

        onDeviceOperation: {
            switch (type) {
            case 0:
                cameraBtn.enabled = true
                if (m_iLiveHelper.getDeviceState(type))
                    cameraBtn.text = "关闭摄像头"
                else {
                    camera.getEmptyFrame()
                    cameraBtn.text = "打开摄像头"
                }
                break
            default:
                break
            }
        }
    }
}
