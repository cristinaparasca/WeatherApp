import * as names from 'names.js';
import {mockCountyList} from 'expected_fake_data.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,findACountyWithCities} from 'helper_methods.js';

function verifyCounty(county)
{
    var countyObj = waitForObject(countyRealName(county.countyName), 5000);

    test.verify(countyObj !== null,
                "County " + county.countyName + " exists");

    var expandedOk=clickOnCountyAndCheckExpanded(countyObj,county.countyName);

    test.verify(expandedOk,
                "County " + county.countyName + " is expanded");

    for (var i = 0; i < county.cities.length; i++)
    {
        var cityObj = findObject(cityRealName( county.cities[i]));

        test.verify(cityObj !== null,
                    " - City " + county.cities[i] + " exists");
    }
}
function main() {

    mouseClick(waitForObject(names.SelectLocationBtn));
    
    for (var i = 0; i < mockCountyList.length; ++i)
    {
        verifyCounty(mockCountyList[i]);
    }
}
