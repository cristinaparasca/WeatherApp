cmake_minimum_required(VERSION 3.16)

project(WeatherInfoMVVM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Test)
find_package(Boost CONFIG REQUIRED COMPONENTS unit_test_framework)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appWeatherInfoMVVM
    main.cpp
)

qt_add_qml_module(appWeatherInfoMVVM
    URI WeatherInfoMVVM
    QML_FILES
        Main.qml
        SOURCES weatherservice.h weatherservice.cpp
        SOURCES weatherviewmodel.h weatherviewmodel.cpp
        SOURCES countriesmodel.h countriesmodel.cpp
        RESOURCES icon/thermometer.png icon/weather.png
        RESOURCES icon/humidity.png
        RESOURCES icon/location-pin.png
        RESOURCES icon/location.png
        SOURCES county.h
        SOURCES weatherparser.h weatherparser.cpp
        SOURCES iweatherservice.h
        SOURCES fakeweatherservice.h fakeweatherservice.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWeatherInfoMVVM PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appWeatherInfoMVVM
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

enable_testing()

add_executable(appWeatherInfoMVVMTests
    tests/unit/test_weatherparser.cpp
    tests/unit/test_countiesparser.cpp
    tests/unit/test_weatherservice.cpp
    county.h
    weatherparser.h
    weatherparser.cpp
    tests/unit/test_countiesmodel.cpp
    countriesmodel.cpp
    tests/unit/test_main.cpp
    tests/unit/test_weatherviewmodel.cpp
    fakeweatherservice.h fakeweatherservice.cpp
    iweatherservice.h
    weatherviewmodel.h
    weatherviewmodel.cpp
    weatherservice.cpp
    weatherservice.h
)

target_include_directories(appWeatherInfoMVVMTests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(appWeatherInfoMVVMTests
    PRIVATE
    Boost::unit_test_framework
    Qt6::Qml
    Qt6::Core
    Qt6::Network
    Qt6::Test
)

target_compile_options(appWeatherInfoMVVMTests PRIVATE
    -O0
    -g
    --coverage
)

target_link_options(appWeatherInfoMVVMTests PRIVATE
    --coverage
)

target_link_libraries(appWeatherInfoMVVM
    PRIVATE Qt6::Quick
)

install(TARGETS appWeatherInfoMVVM
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
