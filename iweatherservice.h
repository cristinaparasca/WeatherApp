#ifndef IWEATHERSERVICE_H
#define IWEATHERSERVICE_H
#include <QObject>
#include <county.h>
#include <weatherparser.h>

class IWeatherService : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    explicit IWeatherService(QObject *parent = nullptr):QObject{parent}{};
    virtual void getWeatherForCity(const QString& city)=0;
    virtual QVector<County> getCountiesFromJsonFile(const QString &filename)=0;

signals:
    void weatherReady(WeatherData &weatherData);
};

#endif // IWEATHERSERVICE_H
