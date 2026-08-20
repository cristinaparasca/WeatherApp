#ifndef COUNTRIESMODEL_H
#define COUNTRIESMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <includes/county.h>

class CountiesModel : public QAbstractListModel
{
    QML_ELEMENT
public:
    explicit CountiesModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void update(QVector<County> &&data);
    enum roles{
        NameRole = Qt::UserRole + 1,
        CitiesRole
    };

private:

    QVector<County> m_data;

};

#endif // COUNTRIESMODEL_H
