import * as names from 'names.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,find3CountiesWithCities} from 'helper_methods.js';

function main()
{
    var counties = find3CountiesWithCities();

    for (var i = 0; i < counties.length; i++)
    {
        var countyName = counties[i].countyName;
        var cityName = counties[i].firstCity;

        test.log("START COUNTY: " + countyName);

        mouseClick(waitForObject(names.SelectLocationBtn));

        var countyObj = waitForObject(countyRealName(countyName), 5000);
        
        var expandedOk=clickOnCountyAndCheckExpanded(countyObj,countyName);

        test.verify(expandedOk, "County " + countyName + " expanded.");

        var cityObj = waitForObject(cityRealName(cityName), 5000);

        doubleClick(cityObj);

        var dialogClosed = waitFor(function() {
            return !object.exists(names.weatherForecastOverlay);
        }, 10000);

        test.verify(dialogClosed,
            "Location dialog is closed after selecting " + cityName);

        test.verify(waitForObjectExists(names.CityToolBtn_Label).text.indexOf(cityName)!==-1,
            "City (" + cityName + ") is updated in CityToolBtn.");

        test.log("CITY TOOL BTN: " +
            waitForObject(names.CityToolBtn_Label, 5000).text);

        test.log("END COUNTY: " + countyName);
    }
}