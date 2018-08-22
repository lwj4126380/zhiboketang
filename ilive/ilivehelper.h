#ifndef ILIVEHELPER_H
#define ILIVEHELPER_H

#include <QObject>
#include <QString>
#include "iLive.h"

using namespace ilive;

class iLiveHelper : public QObject
{
    Q_OBJECT
public:
    explicit iLiveHelper(QObject *parent = nullptr);
    ~iLiveHelper();

    Q_INVOKABLE void doLogin(QString id, QString pwd);
    Q_INVOKABLE void doDeviceTest();
    Q_INVOKABLE void doStopDeviceTest();
    Q_INVOKABLE void openCamera(QString cameraId);

    static void onForceOffline();
    static void OnMemStatusChange(E_EndpointEventId event_id, const Vector<String> &ids, void* data);
    static void OnRoomDisconnect(int reason, const char *errorinfo, void* data);
    static void OnDeviceDetect(void* data);
    static void OnMessage( const Message& msg, void* data );
    static void OnDeviceOperation(E_DeviceOperationType oper, int retCode, void* data);
    static void OnQualityParamCallback(const iLiveRoomStatParam& param, void* data);

    //业务侧服务器相关操作
    static void OnSxbLogin(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

    //iLiveSDK相关操作
    static void OniLiveLoginSuccess(void* data);
    static void OniLiveLoginError(int code, const char *desc, void* data);
    static void OnStartDeviceTestSuc(void* data);
    static void OnStartDeviceTestErr(int code, const char *desc, void* data);
signals:
    void showTips(int code, QString desc);
    void loginSuccess();

    void openDeviceTestPage();

public slots:

private:
    QString mUserId;
    QString mUserSig;
    QString mUserToken;
};

#endif // ILIVEHELPER_H
