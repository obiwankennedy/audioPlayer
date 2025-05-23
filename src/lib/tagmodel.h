#ifndef TAGMODEL_H
#define TAGMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class TagModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit TagModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList m_tags{"L5R","sexy","energy","caca","humour","japon","metal","guitarhero","jdr","film","classic","punk","sad","celte","fr","guitar","rap","us"};
};

#endif // TAGMODEL_H
