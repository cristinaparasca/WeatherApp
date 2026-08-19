import * as names from 'names.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,findACountyWithCities} from 'helper_methods.js';
function debugMessageHandler(object, message) {
    test.log("[QML] " + message);
}
function main()
{
        var countyFound=findACountyWithCities();
        mouseClick(waitForObject(names.SelectLocationBtn));
        var dialogObj=waitForObject({"container": names.weatherForecastOverlay, 
            "objectName": "Dialog", "type": "PopupItem"});
        
       
        var countyFoundObj=waitForObject(countyRealName(countyFound.countyName));
        clickOnCountyAndCheckExpanded(countyFoundObj,countyFound.countyName)
        
        doubleClick(waitForObject(cityRealName(countyFound.firstCity)));
        
        test.verify(dialogObj.visible===false,"Dialog is closed.");
        

}
