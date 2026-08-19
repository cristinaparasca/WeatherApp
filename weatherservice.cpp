#include "weatherservice.h"

WeatherService::WeatherService(QObject *parent)
    : IWeatherService{parent}
{
    netManager=new QNetworkAccessManager(this);
}

void WeatherService::getWeatherForCity(const QString& city)
{
    QNetworkRequest req{QUrl(QString("https://wttr.in/%1?format=j1").arg(city))};
    QNetworkReply *netReply=netManager->get(req);
    connect(netReply, &QNetworkReply::finished,this, [netReply,this](){
        QByteArray bts = netReply->readAll();
        WeatherData weatherData=WeatherParser::parseWeather(bts);
        emit weatherReady(weatherData);
        netReply->deleteLater();
    });
}

QVector<County> WeatherService::getCountiesFromJsonFile(const QString &filename)
{

    QFile file(filename);
    if(!file.open(QIODeviceBase::ReadOnly| QIODevice::Text))
    {
        throw(std::runtime_error(("WeatherService::getCountiesFromJsonFile -> File '"
                                  +filename+"'could not be opened").toStdString()));
    }
    QTextStream in(&file);
    QJsonDocument jsonDoc=QJsonDocument::fromJson(in.readAll().toUtf8());

    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("WeatherService::getCountiesFromJsonFile -> "
                                 "Empty json file."));
    }
    const QJsonObject jsonObj=jsonDoc.object();
    return WeatherParser::parseCounties(jsonObj);
}