#include "includes/countriesmodel.h"
#include <qjsonobject.h>

CountiesModel::CountiesModel(QObject *parent)
    : QAbstractListModel{parent}
{}

int CountiesModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant CountiesModel::data(const QModelIndex &index, int role) const
{
    if(m_data.empty()||!index.isValid())
    {
        return {};
    }

    const County &county=m_data[index.row()];
    switch (role)
    {
        case NameRole:
            return county.name;
        case CitiesRole:
            return county.cities;
        default:
            return {};
    }
}

QHash<int, QByteArray> CountiesModel::roleNames() const
{
    return
    {
        {NameRole,"name"},
        {CitiesRole,"cities"}
    };
}

void CountiesModel::update(QVector<County> &&data)
{
    beginResetModel();
    m_data=std::move(data);
    endResetModel();
}
