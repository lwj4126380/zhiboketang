#include "ilivehelper.h"
#include "../utils/cconstants.h"
#include "SxbServerHelper.h"
#include <QDebug>

iLiveHelper::iLiveHelper(QObject *parent) : QObject(parent)
{
    GetILive()->setMessageCallBack(iLiveHelper::OnMessage, this);
    GetILive()->setForceOfflineCallback(iLiveHelper::onForceOffline);
    GetILive()->setRemoteVideoCallBack(iLiveHelper::OnRemoteVideo, this);
    GetILive()->setChannelMode(E_ChannelIMSDK);

    iLiveRootView* pView = iLiveCreateRootView();
    E_ColorFormat fmt = (pView->getRootViewType() ==ROOT_VIEW_TYPE_D3D) ? COLOR_FORMAT_I420 : COLOR_FORMAT_RGB24;
    GetILive()->setVideoColorFormat(fmt);//iLiveSDK目前的渲染模块，D3D只支持I420格式，GDI只支持RGB24格式;
    pView->destroy();

    int nRet = GetILive()->init(SuixinboAppid, SuixinboAccountType);
    if (nRet != NO_ERR)
    {
        qFatal("init sdk failed.");
        exit(0);
    }
}

iLiveHelper::~iLiveHelper()
{
    GetILive()->release();
    qDebug() << "iLiveHelper destroyed...";
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

void iLiveHelper::OnLocalVideo(const LiveVideoFrame *video_frame, void *custom_data)
{

}

void iLiveHelper::OnRemoteVideo(const LiveVideoFrame *video_frame, void *custom_data)
{

}

void iLiveHelper::OnMessage(const Message &msg, void *data)
{

}

void iLiveHelper::OnDeviceOperation(E_DeviceOperationType oper, int retCode, void *data)
{

}

void iLiveHelper::OnQualityParamCallback(const iLiveRoomStatParam &param, void *data)
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
