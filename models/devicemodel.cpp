#include "devicemodel.h"
#include "iLive.h"

#include <QDebug>

using namespace ilive;

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent),
      mDeviceType(CameraDevice)
{
    GetILive()->setDeviceDetectCallback(OnDeviceDetect, this);
    OnDeviceDetect(this);
}

void DeviceModel::addDevice(const QString &id, const QString &name)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    mDevices.append(QPair<QString, QString>(id, name));
    endInsertRows();
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mDevices.count();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mDevices.count())
        return QVariant();

    if (role == IdRole)
        return mDevices[index.row()].first;
    else if (role == NameRole)
        return mDevices[index.row()].second;

    return QVariant();
}

void DeviceModel::clearData()
{
    auto data_t = mDevices.size();
    if (!data_t) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, data_t - 1);
    mDevices.clear();
    endRemoveRows();
}

void DeviceModel::OnDeviceDetect(void *data)
{
    DeviceModel *model = (DeviceModel *)data;
    Vector< Pair<String, String> > cameraList;
    switch (model->mDeviceType) {
    case CameraDevice:
    {
        int nRet = GetILive()->getCameraList(cameraList);
        if (nRet == NO_ERR)
        {
            model->clearData();
            for(int i=0; i<cameraList.size(); ++i)
            {
                model->addDevice(QString::fromLocal8Bit(cameraList[i].first.c_str()), QString::fromLocal8Bit(cameraList[i].second.c_str()));
            }
        }
    }
        break;
    case MicDevice:
        break;
    case PlayerDevice:
        break;
    default:
        break;
    }

}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "deviceId";
    roles[NameRole] = "deviceName";
    return roles;
}
