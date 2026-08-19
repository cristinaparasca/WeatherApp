#include <boost/test/unit_test.hpp>
#include <weatherparser.h>

BOOST_AUTO_TEST_SUITE(parseCountiesTests)
BOOST_AUTO_TEST_CASE(sucessfullParse)
{
    const QString json = R"(
    {
        "Alba": [
            "Alba Iulia",
            "Blaj"
        ],
        "Arad": [
            "Ineu",
            "Lipova"
        ],
        "Argeș": [
            "Pitești",
            "Câmpulung",
            "Mioveni"
        ]
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();
    QVector<County> expectedResult={
        {"Alba",{"Alba Iulia","Blaj"}},
        {"Arad",{"Ineu","Lipova"}},
        {"Argeș",{"Pitești","Câmpulung","Mioveni"}}
    };
    QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(),expectedResult.end(),
                                  returnedResult.begin(),returnedResult.end());
}

BOOST_AUTO_TEST_CASE(sucessfullParseOneCounty)
{
    const QString json = R"(
    {
        "Arad": [
            "Ineu",
            "Lipova"
        ]
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();
    QVector<County> expectedResult={
        {"Arad",{"Ineu","Lipova"}}
    };
    QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(),expectedResult.end(),
                                  returnedResult.begin(),returnedResult.end());
}

BOOST_AUTO_TEST_CASE(sucessfullParseCountyWithNoCities)
{
    const QString json = R"(
    {
        "Arad": []
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();
    QVector<County> expectedResult={
        {"Arad",{}}
    };
    QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);

    BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(),expectedResult.end(),
                                  returnedResult.begin(),returnedResult.end());
}

BOOST_AUTO_TEST_CASE(invalidJson)
{
    const QString json = R"(
    {
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();

    try{
        QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);
        BOOST_FAIL("Expected exception here");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidJson);
    }
}

BOOST_AUTO_TEST_CASE(EmptyKey)
{
    const QString json = R"(
    {
        "": [
            "Alba Iulia",
            "Blaj"
        ],
        "Arad": [
            "Ineu",
            "Lipova"
        ],
        "Argeș": [
            "Pitești",
            "Câmpulung",
            "Mioveni"
        ]
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();

    try{
        QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);
        BOOST_FAIL("Expected exception here");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidString);
    }
}

BOOST_AUTO_TEST_CASE(InvalidValuesForCities)
{
    const QString json = R"(
    {
        "Alba": [
            1,
            "Blaj"
        ],
        "Arad": [
            "Ineu",
            "Lipova"
        ],
        "Argeș": [
            "Pitești",
            "Câmpulung",
            "Mioveni"
        ]
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();

    try{
        QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);
        BOOST_FAIL("Expected exception here");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_CASE(ValueIsNotArray)
{
    const QString json = R"(
    {
        "Alba": "Ineu",
        "Arad": [
            "Ineu",
            "Lipova"
        ],
        "Argeș": [
            "Pitești",
            "Câmpulung",
            "Mioveni"
        ]
    }
)";
    QJsonDocument jsonDoc=QJsonDocument::fromJson(json.toUtf8());
    if(jsonDoc.isEmpty())
    {
        throw(std::runtime_error("Invalid json."));
    }
    const QJsonObject jsonObj=jsonDoc.object();

    try{
        QVector<County> returnedResult=WeatherParser::parseCounties(jsonObj);
        BOOST_FAIL("Expected exception here");
    }
    catch(WeatherParserException &e)
    {
        BOOST_CHECK(e.getErrorCode() ==
                    WeatherParserException::WeatherParserErrorCode::InvalidFieldType);
    }
}

BOOST_AUTO_TEST_SUITE_END()