#include "ilivehelper.h"
#include "../utils/cconstants.h"
#include "SxbServerHelper.h"
#include <QDebug>
#include <QGuiApplication>

iLiveHelper::iLiveHelper(QObject *parent) : QObject(parent)
{
    GetILive()->setMessageCallBack(OnMessage, this);
    GetILive()->setForceOfflineCallback(onForceOffline);
    GetILive()->setDeviceOperationCallback(OnDeviceOperation, this);
    GetILive()->setLocalVideoCallBack(OnLocalVideo, this);
    GetILive()->setChannelMode(E_ChannelIMSDK);

    iLiveRootView* pView = iLiveCreateRootView();
    E_ColorFormat fmt = (pView->getRootViewType() ==ROOT_VIEW_TYPE_D3D) ? COLOR_FORMAT_I420 : COLOR_FORMAT_RGB24;
//    E_ColorFormat fmt =  COLOR_FORMAT_RGB24;
    GetILive()->setVideoColorFormat(fmt);//iLiveSDK目前的渲染模块，D3D只支持I420格式，GDI只支持RGB24格式;
    pView->destroy();

    int nRet = GetILive()->init(SuixinboAppid, SuixinboAccountType);
    if (nRet != NO_ERR)
    {
        qFatal("init sdk failed.");
        exit(0);
    }

    connect(&mSxbHeartBeatTimer, &QTimer::timeout, [&](){
        sxbHeartBeat();
        sxbRoomIdList();
    });
}

iLiveHelper::~iLiveHelper()
{
    qDebug() << "iLiveHelper destroyed...";
    GetILive()->setMessageCallBack(nullptr, nullptr);
    GetILive()->setForceOfflineCallback(nullptr);
    GetILive()->release();
}

bool iLiveHelper::getDeviceState(iLiveHelper::DeviceOperationType type)
{
    if (type == O_Camera)
        return GetILive()->getCurCameraState();
    else if (type == O_Mic)
        return GetILive()->getCurMicState();
    else
        return GetILive()->getCurPlayerState();
}

void iLiveHelper::doLogin(QString id, QString pwd)
{
    mUserId = id;
    QVariantMap varmap;
    varmap.insert("id", id);
    varmap.insert("pwd", pwd);
    varmap.insert("appid", QString::number(SuixinboAppid));
    SxbServerHelper::request(varmap, "account", "login", OnSxbLogin, this);
}

void iLiveHelper::doDeviceTest()
{
    GetILive()->startDeviceTest(OnStartDeviceTestSuc, OnStartDeviceTestErr, this);
    //    GetILive()->startDeviceTest(NULL, NULL, NULL);
}

void iLiveHelper::doStopDeviceTest()
{
    GetILive()->stopDeviceTest(NULL, NULL, NULL);
}

void iLiveHelper::openCamera(QString cameraId)
{
    GetILive()->openCamera(cameraId.toStdString().c_str());
}

void iLiveHelper::closeCamera()
{
    GetILive()->closeCamera();
}

void iLiveHelper::doBeginLive()
{
    sxbCreateRoom();
}

void iLiveHelper::startHeartBeatTimer()
{
    sxbRoomIdList();
    mSxbHeartBeatTimer.start(10000); //随心播后台要求10秒上报一次心跳
}

void iLiveHelper::onForceOffline()
{

}

void iLiveHelper::OnMemStatusChange(E_EndpointEventId event_id, const Vector<String> &ids, void *data)
{

}

void iLiveHelper::OnRoomDisconnect(int reason, const char *errorinfo, void *data)
{

}

void iLiveHelper::OnDeviceDetect(void *data)
{

}

void iLiveHelper::OnMessage(const Message &msg, void *data)
{

}

void iLiveHelper::OnDeviceOperation(E_DeviceOperationType oper, int retCode, void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    switch(oper)
    {
        case E_OpenCamera:
        {
            if(retCode != NO_ERR)
                emit ilive->showTips(retCode, "Open camera test failed.");
            emit ilive->deviceOperation(O_Camera, true);
            break;
        }
        case E_CloseCamera:
        {
            if (retCode != NO_ERR)
                emit ilive->showTips(retCode, "Close camera test failed.");
            emit ilive->deviceOperation(O_Camera, false);
            break;
        }
        case E_OpenMic:
        {
            if(retCode != NO_ERR)
                emit ilive->showTips(retCode, "Open mic test failed.");
            emit ilive->deviceOperation(O_Mic, true);
            break;
        }
        case E_CloseMic:
        {
            if (retCode != NO_ERR)
                emit ilive->showTips(retCode, "Close mic test failed.");
            emit ilive->deviceOperation(O_Mic, false);
            break;
        }
        case E_OpenPlayer:
        {
            if(retCode != NO_ERR)
                emit ilive->showTips(retCode, "Open player test failed.");
            emit ilive->deviceOperation(O_Player, true);
            break;
        }
        case E_ClosePlayer:
        {
            if (retCode != NO_ERR)
                emit ilive->showTips(retCode, "Close player test failed.");
            emit ilive->deviceOperation(O_Player, false);
            break;
        }
    }
}

void iLiveHelper::OnQualityParamCallback(const iLiveRoomStatParam &param, void *data)
{

}

void iLiveHelper::sxbCreateRoom()
{
    QVariantMap varmap;
    varmap.insert("token",mUserToken);
    varmap.insert("type","live");
    SxbServerHelper::request(varmap, "live", "create", OnSxbCreateRoom, this);
}

void iLiveHelper::sxbReportroom()
{
    QVariantMap varmap;

    varmap.insert("token", mUserToken);

    QVariantMap roommap;
    roommap.insert( "title", mCurRoom.info.title );//选填
    roommap.insert( "roomnum", mCurRoom.info.roomnum );
    roommap.insert( "type", "live");
    roommap.insert( "groupid", QString::number(mCurRoom.info.roomnum) );
    roommap.insert( "cover", "");//选填
    roommap.insert( "appid", QString::number(SuixinboAppid));
    roommap.insert( "device", 2);//0 IOS 1 Android 2 PC
    roommap.insert( "videotype", 0);//0 摄像头 1 屏幕分享
    varmap.insert("room", roommap);

    SxbServerHelper::request(varmap, "live", "reportroom", OnSxbReportroom, this);
}

void iLiveHelper::sxbCreatorJoinRoom()
{
    QVariantMap varmap;
    varmap.insert( "token", mUserToken);
    varmap.insert( "id", mUserId);
    varmap.insert( "roomnum", mCurRoom.info.roomnum);
    varmap.insert( "role", 1);//主播 1 成员 0 上麦成员 2
    varmap.insert( "operate", 0);//进入房间0  退出房间1
    SxbServerHelper::request(varmap, "live", "reportmemid", OnSxbCreatorJoinRoom, this);
}

void iLiveHelper::sxbHeartBeat()
{
    QVariantMap varmap;
    varmap.insert("token", mUserToken);
    varmap.insert("roomnum", mCurRoom.info.roomnum);
    varmap.insert("role", (int)mUserType); //0 观众 1 主播 2 上麦观众
    if(mUserType==E_RoomUserCreator)
    {
        varmap.insert("thumbup", mCurRoom.info.thumbup);
    }
    SxbServerHelper::request(varmap, "live", "heartbeat", OnSxbHeartBeat, this);
}

void iLiveHelper::sxbRoomIdList()
{

}

void iLiveHelper::OnSxbLogin(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(pCusData);

    if (datamap.contains("userSig"))
        ilive->mUserSig = datamap.value("userSig").toString();

    if (datamap.contains("token"))
        ilive->mUserToken = datamap.value("token").toString();

    if (errorCode==E_SxbOK)
        GetILive()->login(ilive->mUserId.toStdString().c_str(), ilive->mUserSig.toStdString().c_str(), OniLiveLoginSuccess, OniLiveLoginError, ilive);
    else
        emit ilive->showTips(errorCode, errorInfo);
}

void iLiveHelper::OnSxbCreateRoom(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(pCusData);

    if (datamap.contains("roomnum"))
        ilive->mCurRoom.info.roomnum = datamap.value("roomnum").toUInt();

    if (datamap.contains("groupid")) {
        QString szRoomId = datamap.value("groupid").toString();
        assert(QString::number(ilive->mCurRoom.info.roomnum) == szRoomId);
    }

    if (errorCode==E_SxbOK)
        ilive->iLiveCreateRoom();
    else
        emit ilive->showTips(errorCode, errorInfo);
}

void iLiveHelper::OnSxbReportroom(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(pCusData);

    if (errorCode==E_SxbOK)
        ilive->sxbCreatorJoinRoom();//随心播服务器要求，创建房间、上报房间信息、主播还需要上报一次自己进入房间;
    else
        emit ilive->showTips(errorCode, errorInfo);
}

void iLiveHelper::OnSxbCreatorJoinRoom(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(pCusData);

    if (errorCode==E_SxbOK) {
        emit ilive->openLiveWindow();
        ilive->startHeartBeatTimer();
    } else
        emit ilive->showTips(errorCode, errorInfo);
}

void iLiveHelper::OnSxbHeartBeat(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(pCusData);

    if (errorCode!=E_SxbOK)
    {
        //iLiveLog_e( "suixinbo", "Sui xin bo heartbeat failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
    }
}

void iLiveHelper::OnSxbRoomIdList(int errorCode, QString errorInfo, QVariantMap datamap, void *pCusData)
{

}

void iLiveHelper::OnLocalVideo(const LiveVideoFrame *video_frame, void *custom_data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(custom_data);
    if (video_frame->desc.colorFormat == COLOR_FORMAT_I420) {
        QVideoFrame frame(video_frame->dataSize, QSize(video_frame->desc.width, video_frame->desc.height),video_frame->desc.width, QVideoFrame::Format_YUV420P);
        frame.map(QAbstractVideoBuffer::ReadWrite);
        memcpy(frame.bits(), video_frame->data, video_frame->dataSize);
        frame.unmap();
        emit ilive->localVideoReceived(frame);
    } else if (video_frame->desc.colorFormat == COLOR_FORMAT_RGB24){
        QImage image(video_frame->data, video_frame->desc.width, video_frame->desc.height, QImage::Format_RGB888);
        QVideoFrame frame(image.convertToFormat(QImage::Format_RGB32));
        emit ilive->localVideoReceived(frame);
    }
}

void iLiveHelper::iLiveCreateRoom()
{
    iLiveRoomOption roomOption;
    roomOption.audioCategory = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//互动直播场景
    roomOption.roomId = mCurRoom.info.roomnum;
    roomOption.authBits = AUTH_BITS_DEFAULT;
    roomOption.controlRole = LiveMaster;
    roomOption.roomDisconnectListener = OnRoomDisconnect;
    roomOption.memberStatusListener = OnMemStatusChange;
    //roomOption.qualityParamCallback = Live::OnQualityParamCallback;
    roomOption.data = this;
    GetILive()->createRoom(roomOption, OniLiveCreateRoomSuc, OniLiveCreateRoomErr, this );
}

void iLiveHelper::OniLiveLoginSuccess(void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    emit ilive->loginSuccess();
}

void iLiveHelper::OniLiveLoginError(int code, const char *desc, void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    emit ilive->showTips(code, QString(desc));
}

void iLiveHelper::OnStartDeviceTestSuc(void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    emit ilive->openDeviceTestPage();
}

void iLiveHelper::OnStartDeviceTestErr(int code, const char *desc, void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    emit ilive->showTips(code, QString(desc));
}

void iLiveHelper::OniLiveCreateRoomSuc(void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    ilive->mRoomId = ilive->mCurRoom.info.roomnum;
    ilive->mUserType = E_RoomUserCreator;
    ilive->mCurRoom.szId = ilive->mUserId;
    ilive->mCurRoom.info.thumbup = 0;
    ilive->sxbReportroom();//上报房间信息给随心播业务侧服务器
}

void iLiveHelper::OniLiveCreateRoomErr(int code, const char *desc, void *data)
{
    iLiveHelper* ilive = reinterpret_cast<iLiveHelper*>(data);
    emit ilive->showTips(code, desc);
}
