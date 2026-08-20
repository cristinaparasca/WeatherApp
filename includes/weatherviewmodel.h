#ifndef WEATHERVIEWMODEL_H
#define WEATHERVIEWMODEL_H

#include <QObject>
#include <includes/iweatherservice.h>
#include "includes/countriesmodel.h"
class WeatherViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int humidity MEMBER m_humidity NOTIFY humidityChanged FINAL);
    Q_PROPERTY(int realTemperature MEMBER m_realTemperature NOTIFY realTemperatureChanged FINAL);
    Q_PROPERTY(int feelsLikeTemperature MEMBER m_feelsLikeTemperature NOTIFY feelsLikeTemperatureChanged FINAL);
    Q_PROPERTY(CountiesModel* countiesModel READ countiesModel CONSTANT)
    Q_PROPERTY(QString city READ city WRITE setCity NOTIFY cityChanged FINAL)

public:
    explicit WeatherViewModel(const std::shared_ptr<IWeatherService> &ws_,QObject *parent = nullptr);
    void init(const QString& filePath);
    void setCity(const QString &city);
    CountiesModel* countiesModel();
    QString city() const;

signals:
    void humidityChanged();
    void realTemperatureChanged();
    void feelsLikeTemperatureChanged();
    void cityChanged();
    //void countiesChanged();
private:
    std::shared_ptr<IWeatherService> ws;
    QString m_city{""};

    CountiesModel* m_counties_model;
    int m_humidity{0},m_realTemperature{0},m_feelsLikeTemperature{0};
    void onWeatherReady(WeatherData &weatherData);
};

#endif // WEATHERVIEWMODEL_H
