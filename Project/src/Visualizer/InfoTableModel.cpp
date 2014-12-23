#include "InfoTableModel.h"
#include <tuple>

InfoTableModel::InfoTableModel(QObject *parent):
    QAbstractTableModel(parent)
{
    pDataStorage = new QMap<int, QPair<QString, QString>>();
}

InfoTableModel::~InfoTableModel()
{
    delete pDataStorage;
}

int InfoTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return pDataStorage->size();
}

int InfoTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant InfoTableModel::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{
    if (index.row() > (pDataStorage->begin() + (pDataStorage->size() - 1)).key())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        QPair<QString, QString> pair = pDataStorage->values().at(index.row());
        if (index.column() == 0)
            return pair.first;
        if (index.column() == 1)
            return pair.second;
    }
    return QVariant();
}

void InfoTableModel::updateData(std::tuple<int, QString, QString> incomingData)
{
    int row;
    QString data0, data1;
    std::tie(row, data0, data1) = incomingData;
    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
    beginInsertRows(QModelIndex(), row, row);
    pDataStorage->insert(row,StrPair(data0,data1));
    endInsertRows();
}

