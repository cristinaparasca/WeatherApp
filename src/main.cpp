#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <includes/weatherviewmodel.h>
#include <includes/weatherservice.h>
#include <QQmlContext>
#include <includes/fakeweatherservice.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QStringList args = QCoreApplication::arguments();

    std::shared_ptr<IWeatherService> ws;

    if (args.contains("--fake-service"))
        ws = std::make_shared<FakeWeatherService>();
    else
        ws = std::make_shared<WeatherService>();

    WeatherViewModel *weatherViewModel=new WeatherViewModel(ws);
    weatherViewModel->init("data/cities.json");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("weatherViewModel",weatherViewModel);
    engine.loadFromModule("WeatherInfoMVVM", "Main");

    return QGuiApplication::exec();
}
