#include "fakeweatherservice.h"

FakeWeatherService::FakeWeatherService(QObject *parent)
    : IWeatherService{parent}
{}

void FakeWeatherService::getWeatherForCity(const QString &city)
{
    WeatherData wdata{fakeHumidity,fakeFeelsLikeTemperature,fakeTemperature};
    lastCityRequested=city;
    emit weatherReady(wdata);
}

QVector<County> FakeWeatherService::getCountiesFromJsonFile(const QString &filename)
{
    return {
               {"Alba",{"Alba Iulia","Blaj"}},
               {"Arad",{"Ineu","Lipova"}},
               {"Argeș",{"Pitești","Câmpulung","Mioveni"}},
               {"Bacău", {"Onești","Moinești", "Comănești", "Bacău"}},
               {"Bihor", {"Oradea","Salonta","Marghita","Beiuș"}},
            {"Brașov", {"Făgăraș","Săcele","Râșnov","Brașov"}}
           };
}
