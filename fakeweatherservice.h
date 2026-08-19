#ifndef FAKEWEATHERSERVICE_H
#define FAKEWEATHERSERVICE_H

#include "iweatherservice.h"

class FakeWeatherService : public IWeatherService
{
    Q_OBJECT
public:
    explicit FakeWeatherService(QObject *parent = nullptr);

    void getWeatherForCity(const QString &city) override;
    QVector<County> getCountiesFromJsonFile(const QString &filename) override;

    int fakeTemperature=25;
    int fakeFeelsLikeTemperature=23;
    int fakeHumidity=40;
    QString lastCityRequested{""};
};

#endif // FAKEWEATHERSERVICE_H
