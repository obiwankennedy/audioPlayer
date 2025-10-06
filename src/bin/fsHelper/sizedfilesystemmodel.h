#ifndef SIZEDFILESYSTEMMODEL_H
#define SIZEDFILESYSTEMMODEL_H

#include <QFileSystemModel>

class SizedFileSystemModel : public QFileSystemModel
{
    Q_OBJECT

public:
    explicit SizedFileSystemModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // SIZEDFILESYSTEMMODEL_H
