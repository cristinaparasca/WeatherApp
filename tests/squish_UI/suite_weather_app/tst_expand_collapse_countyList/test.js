import * as names from 'names.js';
import {clickOnCountyAndCheckExpanded,delegateRealName,countyRealName,cityRealName,findACountyWithCities} from 'helper_methods.js';

function main() {
    var countyFound=findACountyWithCities();
    mouseClick(waitForObject(names.SelectLocationBtn));
    var delegate=waitForObject(delegateRealName(countyFound.countyName));
    var countyFoundObj=waitForObject(countyRealName(countyFound.countyName));
    var expandedOk = clickOnCountyAndCheckExpanded(countyFoundObj,countyFound.countyName);
    
    test.verify(expandedOk,
        "County(" + countyFound.countyName + ") is expanded.");
    mouseClick(countyFoundObj);
    test.verify(delegate.expanded === false,
        "County(" + countyFound.countyName + ") is collapsed.");  
    
}
