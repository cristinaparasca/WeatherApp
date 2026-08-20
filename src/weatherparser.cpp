#include "includes/weatherparser.h"

typedef WeatherParserException::WeatherParserErrorCode WeatherParserErrorCode;

WeatherParser::WeatherParser() {}

int WeatherParser::readInt(QJsonObject &jsonObject, const QString &field)
{
    if(!jsonObject.contains(field))
    {
        throw WeatherParserException(
            WeatherParserException::MissingField,field.toStdString()
            );
    }
    if(!jsonObject[field].isString())
    {
        throw WeatherParserException(WeatherParserException::InvalidFieldType,
            ("'" + field + "' is not a string").toStdString()
            );
    }
    auto fieldAsString=jsonObject[field].toString();
    bool isInt;
    int fieldAsInt=fieldAsString.toInt(&isInt);
    if(!isInt)
    {
        throw WeatherParserException(WeatherParserErrorCode::InvalidInteger,
            ("'" + field + "':"+ fieldAsString+" is not Int").toStdString()
            );
    }
    return fieldAsInt;
}
WeatherData WeatherParser::parseWeather(const QByteArray& weatherRawData)
{

    QString tmp(weatherRawData);
    QJsonDocument jsonResponse=QJsonDocument::fromJson(tmp.toUtf8());
    QJsonObject jsonObj=jsonResponse.object();

    if(jsonObj.empty())
    {
        throw WeatherParserException(WeatherParserErrorCode::InvalidJson,"");
    }

    QString currentConditionFieldName{"current_condition"};
    if(!jsonObj.contains(currentConditionFieldName))
    {
        throw WeatherParserException(WeatherParserErrorCode::MissingField,
                                     ("'"+currentConditionFieldName+"'").toStdString());
    }
    auto currentConditionJson=jsonObj[currentConditionFieldName];
    if(!currentConditionJson.isArray())
    {
        throw WeatherParserException(WeatherParserErrorCode::InvalidFieldType,(currentConditionFieldName+
                                     " value is not an array").toStdString());
    }
    auto currentConditionArray=currentConditionJson.toArray();
    if(currentConditionArray.isEmpty())
    {
        throw WeatherParserException(WeatherParserErrorCode::EmptyArray,
                                     ("'"+currentConditionFieldName+"'").toStdString());
    }
    auto currentConditionObject=currentConditionArray[0];
    if(!currentConditionObject.isObject())
    {
        throw WeatherParserException(WeatherParserErrorCode::InvalidFieldType,
                                 ("'"+currentConditionFieldName+"' value is not an object.")
                                         .toStdString());
    }
    QJsonObject jsonObj2=currentConditionObject.toObject();

    WeatherData weatherData;
    weatherData.temperature=readInt(jsonObj2,"temp_C");
    weatherData.feelLikeTemperature=readInt(jsonObj2,"FeelsLikeC");
    weatherData.humidity=readInt(jsonObj2,"humidity");
    return weatherData;
}

QVector<County> WeatherParser::parseCounties(const QJsonObject &jsonObj)
{
    QVector<County> m_data;
    if(jsonObj.empty())
    {
        throw WeatherParserException(WeatherParserErrorCode::InvalidJson,"Json object is empty");
    }
    for(auto it=jsonObj.constBegin();it!=jsonObj.constEnd();++it)
    {
        QJsonValue jsonValue=it.value();
        if(!jsonValue.isArray())
        {
            throw WeatherParserException(WeatherParserErrorCode::InvalidFieldType,
                                         "Json value should be an array");
        }

        County &county=m_data.emplace_back();
        county.name=it.key();
        if(county.name.isEmpty())
        {
            m_data.pop_back();
            throw WeatherParserException(WeatherParserErrorCode::InvalidString,
                                         "County should not be an empty string");
        }
        const QJsonArray jsonArray=jsonValue.toArray();
        QStringList &cities=county.cities;
        for(const auto &city:jsonArray)
        {
            if(!city.isString())
            {
                m_data.pop_back();
                throw WeatherParserException(WeatherParserErrorCode::InvalidFieldType,
                                             ("For key '"+county.name+ "' , json value should be an array of STRINGS")
                                                 .toStdString());
            }

            cities.emplace_back(city.toString());
        }

    }
    return m_data;
}
WeatherParserException::WeatherParserException(const WeatherParserErrorCode _errorCode,
                                               const std::string &__arg):
    std::runtime_error(errorCodeAsString(_errorCode)+__arg),errorCode{_errorCode}
{
}

