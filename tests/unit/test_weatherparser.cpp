#include <boost/test/unit_test.hpp>
#include <weatherparser.h>

BOOST_AUTO_TEST_SUITE(parseWeatherFromJsonTests)
BOOST_AUTO_TEST_CASE(validJson)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    WeatherData expectedWeatherData{76,25,22};
    WeatherData outputWeatherData=WeatherParser::parseWeather(input);
    BOOST_TEST(outputWeatherData==expectedWeatherData);
}
BOOST_AUTO_TEST_CASE(InvalidJson)
{
    const char* json = R"(
{
    "current_condition": [
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidJson);
    }
}
BOOST_AUTO_TEST_CASE(missingTempCField)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::MissingField);
    }
}
BOOST_AUTO_TEST_CASE(missingHumidityField)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::MissingField);
    }
}
BOOST_AUTO_TEST_CASE(missingFeelsLikeCField)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::MissingField);
    }
}

BOOST_AUTO_TEST_CASE(CurrentConditionIsNotArray)
{
    const char* json = R"(
{
    "current_condition":
        {
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_CASE(CurrentConditionEmptyArray)
{
    const char* json = R"(
{
    "current_condition": [
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::EmptyArray);
    }
}

BOOST_AUTO_TEST_CASE(invalidIntegerTempC)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "a",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidInteger);
    }
}

BOOST_AUTO_TEST_CASE(invalidIntegerFeelsLikeC)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidInteger);
    }
}

BOOST_AUTO_TEST_CASE(invalidIntegerHumidity)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "a",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidInteger);
    }
}

BOOST_AUTO_TEST_CASE(invalidStringTempC)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": 22,
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_CASE(invalidStringHumidity)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": "25",
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": 76,
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_CASE(invalidStringFeelsLikeC)
{
    const char* json = R"(
{
    "current_condition": [
        {
            "FeelsLikeC": 25,
            "FeelsLikeF": "76",
            "cloudcover": "100",
            "humidity": "76",
            "observation_time": "04:08 PM",
            "precipMM": "0.2",
            "pressure": "1019",
            "temp_C": "22",
            "temp_F": "72",
            "uvIndex": 5,
            "visibility": "16",
            "weatherCode": "122",
            "weatherDesc": [{"value": "Overcast"}],
            "winddir16Point": "NNE",
            "winddirDegree": "20",
            "windspeedKmph": "7",
            "windspeedMiles": "4"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_CASE(currentConditionFieldMissing)
{
    const char* json = R"(
{
    "another_field": [
        {
            "anotherValue": "25"
        }
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::MissingField);
    }
}

BOOST_AUTO_TEST_CASE(currentConditionNotObject)
{
    const char* json = R"(
{
    "current_condition": [
        23
    ]
}
)";
    QByteArray input{json};
    try{
        WeatherParser::parseWeather(input);
        BOOST_FAIL("Expected Weather Parser Exception");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_SUITE_END()

