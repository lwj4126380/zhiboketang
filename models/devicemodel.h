#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(DeviceType deviceType READ deviceType WRITE setDeviceType)

    enum DeviceRoles {
        IdRole = Qt::UserRole + 1,
        NameRole
    };
    Q_ENUMS(DeviceRoles)

    enum DeviceType {
        CameraDevice,
        MicDevice,
        PlayerDevice
    };
    Q_ENUMS(DeviceType)

    DeviceModel(QObject *parent = 0);
    ~DeviceModel();

    Q_INVOKABLE void addDevice(const QString &id, const QString &name);
    Q_INVOKABLE void clearData();
    Q_INVOKABLE QString getIndexValue(const QModelIndex &index);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void setDeviceType(DeviceType type) { mDeviceType = type;}
    DeviceType deviceType() { return mDeviceType; }

    static void OnDeviceDetect(void* data);

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<QPair<QString, QString>> mDevices;
    DeviceType mDeviceType;
};

#endif // DEVICEMODEL_H
