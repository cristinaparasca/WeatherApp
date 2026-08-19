import * as names from 'names.js';
import {mockCountyList,mockTemperatureData} from 'expected_fake_data.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,findACountyWithCities} from 'helper_methods.js';


function cityObj(city) {
    var cityRealName={"container": names.weatherForecastOverlay, "objectName": "city_"+city , "type": "Button"};

    return waitForObject(cityRealName);
}

function main() {
    mouseClick(waitForObject(names.SelectLocationBtn));
    
    var countyFound=findACountyWithCities();
    
    var countyObj=waitForObject(countyRealName(countyFound.countyName))
    
    clickOnCountyAndCheckExpanded(countyObj,countyFound.countyName);
    
    doubleClick(waitForObject(cityRealName(countyFound.firstCity)));
        
    test.verify(
    waitForObjectExists(names.CityToolBtn_Label).text.indexOf(countyFound.firstCity)!==-1,
    "City(" + countyFound.firstCity+ ") is populated in CityToolBtn.");
    
    test.verify(
    waitForObjectExists(names.TemperatureToolBtn_Label).text.indexOf(mockTemperatureData.temperature.toString())!==-1,
    "Temperature("+ mockTemperatureData.temperature+ ") is updated in TemperatureToolBtn");
    
    test.verify(
    waitForObjectExists(names.FeelsLikeToolBtn_Label).text.indexOf(mockTemperatureData.feelsLikeTemperature.toString())!==-1,
    "FeelsLikeTemperature(" +mockTemperatureData.feelsLikeTemperature+ ") is updated in FeelsLikeToolBtn");
    test.verify(
    waitForObjectExists(names.HumidityToolBtn_Label).text.indexOf(mockTemperatureData.humidity.toString())!==-1,
    "Humidity(" + mockTemperatureData.humidity +") is updated in HumidityToolBtn");

}
