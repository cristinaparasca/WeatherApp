#include <boost/test/unit_test.hpp>
#include <weatherviewmodel.h>
#include <fakeweatherservice.h>
#include <QSignalSpy>

BOOST_AUTO_TEST_SUITE(WeatherViewModelTests)

BOOST_AUTO_TEST_CASE(setCity_checkCity)
{
    std::shared_ptr<IWeatherService> ws=std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(ws);
    weatherViewModel.setCity("Timisoara");
    BOOST_TEST(weatherViewModel.city().toStdString()=="Timisoara");
}

BOOST_AUTO_TEST_CASE(constructor_nullptrService)
{
    std::shared_ptr<IWeatherService> ws;
    BOOST_CHECK_THROW(WeatherViewModel weatherViewModel(ws), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(constructor_initialState)
{
    std::shared_ptr<IWeatherService> ws=std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(ws);

    int humidity=weatherViewModel.property("humidity").toInt();
    int feelsLikeTemperature=weatherViewModel.property("feelsLikeTemperature").toInt();
    int realTemperature=weatherViewModel.property("realTemperature").toInt();

    BOOST_TEST(realTemperature==0);
    BOOST_TEST(feelsLikeTemperature==0);
    BOOST_TEST(humidity==0);
    BOOST_TEST(weatherViewModel.city().isEmpty());
}

BOOST_AUTO_TEST_CASE(init_loadsDeafaultCity_updatesCountiesModel)
{
    auto fakeService=std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    weatherViewModel.init("/some_file_path");
    BOOST_TEST(weatherViewModel.city().toStdString()=="Alba");
    BOOST_TEST(weatherViewModel.countiesModel()->rowCount(QModelIndex())==6);

}
BOOST_AUTO_TEST_CASE(setCity_checkWeatherValuesAreUpdated)
{
    std::shared_ptr<FakeWeatherService> fakeService=
        std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    weatherViewModel.setCity("Timisoara");

    int humidity=weatherViewModel.property("humidity").toInt();
    int feelsLikeTemperature=weatherViewModel.property("feelsLikeTemperature").toInt();
    int realTemperature=weatherViewModel.property("realTemperature").toInt();

    BOOST_CHECK_EQUAL(realTemperature,fakeService->fakeTemperature);
    BOOST_CHECK_EQUAL(feelsLikeTemperature,fakeService->fakeFeelsLikeTemperature);
    BOOST_CHECK_EQUAL(humidity,fakeService->fakeHumidity);
}
BOOST_AUTO_TEST_CASE(setCity_sameCityIsSetTwice_signalIsEmmitedOnce)
{
    std::shared_ptr<FakeWeatherService> fakeService=
        std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    QSignalSpy spy(&weatherViewModel,&WeatherViewModel::cityChanged);
    weatherViewModel.setCity("Timisoara");
    weatherViewModel.setCity("Timisoara");
    BOOST_TEST(spy.count()==1);
}
BOOST_AUTO_TEST_CASE(setCity_alsoEmitsHumidityChangedSignal)
{
    std::shared_ptr<FakeWeatherService> fakeService=
        std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    QSignalSpy spy(&weatherViewModel,&WeatherViewModel::humidityChanged);
    weatherViewModel.setCity("Timisoara");
    BOOST_TEST(spy.count()==1);
}
BOOST_AUTO_TEST_CASE(setCity_alsoEmitsRealTemperatureChangedSignal)
{
    std::shared_ptr<FakeWeatherService> fakeService=
        std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    QSignalSpy spy(&weatherViewModel,&WeatherViewModel::realTemperatureChanged);
    weatherViewModel.setCity("Timisoara");
    BOOST_TEST(spy.count()==1);
}
BOOST_AUTO_TEST_CASE(setCity_alsoEmitsFeelsLikeTemperatureChangedSignal)
{
    std::shared_ptr<FakeWeatherService> fakeService=
        std::make_shared<FakeWeatherService>();
    WeatherViewModel weatherViewModel(fakeService);
    QSignalSpy spy(&weatherViewModel,&WeatherViewModel::feelsLikeTemperatureChanged);
    weatherViewModel.setCity("Timisoara");
    BOOST_TEST(spy.count()==1);
}
BOOST_AUTO_TEST_SUITE_END()
