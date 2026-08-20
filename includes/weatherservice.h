#ifndef WEATHERSERVICE_H
#define WEATHERSERVICE_H

#include <includes/iweatherservice.h>
#include <QQmlEngine>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QDir>

class WeatherService : public IWeatherService
{
    Q_OBJECT
public:
    explicit WeatherService(QObject *parent = nullptr);

    void getWeatherForCity(const QString& city) override;
    QVector<County> getCountiesFromJsonFile(const QString &filename) override;

private:
    QNetworkAccessManager *netManager;
};

#endif // WEATHERSERVICE_H
