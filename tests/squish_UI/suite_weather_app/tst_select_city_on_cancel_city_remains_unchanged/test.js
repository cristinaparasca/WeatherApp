import * as names from 'names.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,findACountyWithCities} from 'helper_methods.js';

function main() {
    var cityTextBeforeCancel=findObject(names.CityToolBtn_Label).text;
    
    var countyFound=findACountyWithCities();
    mouseClick(waitForObject(names.SelectLocationBtn));
    var countyFoundObj=waitForObject(countyRealName(countyFound.countyName));
    
    clickOnCountyAndCheckExpanded(countyFoundObj,countyFound.countyName);
    
    mouseClick(waitForObject(names.cancelButton));

    var cityTextAfterCancel=findObject(names.CityToolBtn_Label).text;
    test.verify(cityTextBeforeCancel==cityTextAfterCancel,"City text remained unchanged after Dialog Cancel.");
    closeWindow(names.weatherForecastQQuickWindowQmlImpl);
}
