#ifndef WEATHERPARSER_H
#define WEATHERPARSER_H

#include <QByteArray>
#include <qjsonobject.h>
#include <county.h>
#include <ostream>
#include <qjsonarray.h>

class WeatherParserException : public std::runtime_error
{

public:
    enum WeatherParserErrorCode{
        InvalidJson,
        MissingField,
        InvalidFieldType,
        InvalidInteger,
        InvalidString,
        EmptyArray,
        ErrorCodeMax
    };
    WeatherParserException(const WeatherParserErrorCode _errorCode,
                           const std::string &__arg);
    static std::string errorCodeAsString(const WeatherParserErrorCode _errorCode)
    {
        std::string s;
        switch (_errorCode) {
        case InvalidJson:
            s="Invalid Json";
            break;
        case MissingField:
            s="Missing Field -> ";
            break;
        case InvalidFieldType:
            s="Invalid Field Type -> ";
                break;
        case InvalidInteger:
            s="Invalid Integer -> ";
            break;
        case EmptyArray:
            s="Empty Array -> ";
            break;
        case ErrorCodeMax:
            s="";
            break;
        default:
            s="";
            break;
        }
        return s;
    }
    WeatherParserErrorCode getErrorCode() const noexcept
    {
        return errorCode;
    }
private:
    WeatherParserErrorCode errorCode;
};

struct WeatherData{
    int humidity,feelLikeTemperature,temperature;
    WeatherData()=default;
    WeatherData(const int humidity_,const int feelsLikeTemperature_,
                const int temperature_):humidity{humidity_},
        feelLikeTemperature{feelsLikeTemperature_},temperature{temperature_}{};
    bool operator==(const WeatherData& other) const
    {
        return this->humidity==other.humidity &&
               this->feelLikeTemperature==other.feelLikeTemperature &&
               this->temperature==other.temperature;
    }
// GCOVR_EXCL_START
    friend std::ostream& operator<<(std::ostream& os, const WeatherData& data)
    {
        os << "\ntemperature: "<<data.temperature << " \n"
           << "humidity: "<<data.humidity << " \n"
           << "feelsLikeTemperature: "<<data.feelLikeTemperature<<" \n";

        return os;
    }
// GCOVR_EXCL_STOP
};

class WeatherParser
{
public:
    WeatherParser();
    static int readInt(QJsonObject &jsonObject,const QString& field);
    static WeatherData parseWeather(const QByteArray& weatherRawData);
    static QVector<County> parseCounties(const QJsonObject &jsonObj);
};

#endif // WEATHERPARSER_H
