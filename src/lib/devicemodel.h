#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>

class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QStringList deviceList READ deviceList WRITE setDeviceList NOTIFY deviceListChanged FINAL)
public:
    explicit DeviceModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    QStringList deviceList() const;
    void setDeviceList(const QStringList &newDeviceList);

signals:
    void deviceListChanged();

private:
    QStringList m_deviceList;
};

#endif // DEVICEMODEL_H
