#include "includes/weatherviewmodel.h"

#include <QCoreApplication>

WeatherViewModel::WeatherViewModel(const std::shared_ptr<IWeatherService> &ws_,QObject *parent)
    :QObject{parent},ws{ws_}, m_counties_model(new CountiesModel(this))
{
    if(ws.use_count()==0)
    {
        throw std::invalid_argument("std::shared_ptr<IWeatherService> reference counter is 0.");
    }
    connect(ws.get(),&IWeatherService::weatherReady,this,&WeatherViewModel::onWeatherReady);
}

void WeatherViewModel::init(const QString &filePath)
{
    auto counties=ws->getCountiesFromJsonFile(filePath);
    setCity(counties.first().name);
    m_counties_model->update(std::move(counties));
}

void WeatherViewModel::setCity(const QString &city)
{
    if(city==m_city)
    {
        return;
    }
    m_city=city;
    emit cityChanged();
    ws->getWeatherForCity(city);
}

CountiesModel *WeatherViewModel::countiesModel()
{
    return m_counties_model;
}

QString WeatherViewModel::city() const
{
    return m_city;
}

void WeatherViewModel::onWeatherReady(WeatherData &weatherData)
{
    m_humidity=weatherData.humidity;
    m_realTemperature=weatherData.temperature;
    m_feelsLikeTemperature=weatherData.feelLikeTemperature;
    emit humidityChanged();
    emit realTemperatureChanged();
    emit feelsLikeTemperatureChanged();
}
