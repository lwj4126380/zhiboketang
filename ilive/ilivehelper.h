#ifndef ILIVEHELPER_H
#define ILIVEHELPER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include "iLive.h"

using namespace ilive;

struct Room
{
    QString szId;

    struct taglnfo
    {
        taglnfo():roomnum(0),thumbup(0),memsize(0){}
        int roomnum;
        QString title;
        QString type;
        QString groupid;
        QString cover;
        int thumbup;//点赞数
        int memsize;//房间人员数
    }info;
};

enum E_RoomUserType
{
    E_RoomUserInvalid = -1,
    E_RoomUserWatcher, //观众
    E_RoomUserCreator, //主播
    E_RoomUserJoiner,  //连麦者
};

struct RoomMember
{
    QString szID;
    E_RoomUserType userType;
};

class iLiveHelper : public QObject
{
    Q_OBJECT
public:
    enum DeviceOperationType {
        O_Camera,
        O_Mic,
        O_Player
    };
    Q_ENUMS(DeviceOperationType)
    explicit iLiveHelper(QObject *parent = nullptr);
    ~iLiveHelper();

    Q_INVOKABLE bool getDeviceState(DeviceOperationType type);

    Q_INVOKABLE void doLogin(QString id, QString pwd);
    Q_INVOKABLE void doDeviceTest();
    Q_INVOKABLE void doStopDeviceTest();
    Q_INVOKABLE void openCamera(QString cameraId);
    Q_INVOKABLE void closeCamera();
    Q_INVOKABLE void doBeginLive();

    void startHeartBeatTimer();

    static void onForceOffline();
    static void OnMemStatusChange(E_EndpointEventId event_id, const Vector<String> &ids, void* data);
    static void OnRoomDisconnect(int reason, const char *errorinfo, void* data);
    static void OnDeviceDetect(void* data);
    static void OnMessage( const Message& msg, void* data );
    static void OnDeviceOperation(E_DeviceOperationType oper, int retCode, void* data);
    static void OnQualityParamCallback(const iLiveRoomStatParam& param, void* data);

    //业务侧服务器相关操作
    void sxbCreateRoom();
    void sxbReportroom();
    void sxbCreatorJoinRoom();//主播加入房间
    void sxbHeartBeat();
    void sxbRoomIdList();
    static void OnSxbLogin(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
    static void OnSxbCreateRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
    static void OnSxbReportroom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
    static void OnSxbCreatorJoinRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
    static void OnSxbHeartBeat(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
    static void OnSxbRoomIdList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

    //iLiveSDK相关操作
    void iLiveCreateRoom();

    static void OniLiveLoginSuccess(void* data);
    static void OniLiveLoginError(int code, const char *desc, void* data);
    static void OnStartDeviceTestSuc(void* data);
    static void OnStartDeviceTestErr(int code, const char *desc, void* data);    
    static void OniLiveCreateRoomSuc(void* data);
    static void OniLiveCreateRoomErr(int code, const char *desc, void* data);
signals:
    void showTips(int code, QString desc);
    void loginSuccess();

    void openDeviceTestPage();
    void openLiveWindow();
    void deviceOperation(DeviceOperationType type, bool bOpen, int vol=0);

public slots:

private:
    QTimer mSxbHeartBeatTimer;
    QString mUserId;
    QString mUserSig;
    QString mUserToken;
    Room mCurRoom;
    int mRoomId;
    E_RoomUserType mUserType;
};

#endif // ILIVEHELPER_H
