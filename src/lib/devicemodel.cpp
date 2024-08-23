#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_deviceList.size();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariant res;
    switch(role)
    {
    case Qt::DisplayRole:
        res = m_deviceList[index.row()];
        break;
    }
    return res;
}

QStringList DeviceModel::deviceList() const
{
    return m_deviceList;
}

void DeviceModel::setDeviceList(const QStringList &newDeviceList)
{
    if (m_deviceList == newDeviceList)
        return;
    beginResetModel();
    m_deviceList = newDeviceList;
    endResetModel();
    emit deviceListChanged();
}
