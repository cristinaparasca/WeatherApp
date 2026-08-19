import {mockCountyList} from 'expected_fake_data.js';
export function cityRealName(cityName)
{
   return {"container": names.weatherForecastOverlay, "objectName": "city_"+cityName , "type": "Button"}
}

export function delegateRealName(countyName)
{
    return {"container": names.weatherForecastOverlay, 
        "objectName": "countyDelegate_"+countyName, "type": "Column"}
}

export function countyRealName(countyName)
{
    return {"container": names.weatherForecastOverlay, 
        "objectName": "county_"+countyName, "type": "Button"};
}
export function debugMessageHandler(object, message) {
//this is for seeing QML logs
//use installSignalHandler(delegate,"debugMessage(QString)","debugMessageHandler");
    test.log("[QML] " + message);
}
export function clickOnCountyAndCheckExpanded(countyObj,countyName)
{
    var delegate=waitForObject(delegateRealName(countyName),2000);
    
    mouseClick(countyObj);
    var expandedOk = waitFor(function() {
        return delegate.expanded === true;
    }, 100);

    if (!expandedOk)
    {
        test.log("First click did not expand " + countyName + ", retrying...");
        mouseClick(countyObj);
        expandedOk = waitFor(function() {
            return delegate.expanded === true;
        }, 100);
    }
    return expandedOk;
}
export function findACountyWithCities(){
    if(mockCountyList.length===0)
    {
        test.fatal("Empty mockCountyList.");
    }
    for(var i=0;i<mockCountyList.length;i++)
    {
        if(mockCountyList[i].cities.length!=0)
        {
            return{
                countyName:mockCountyList[i].countyName,
                firstCity:mockCountyList[i].cities[0]
            };
        }
    }
    test.fatal("Cannot find a valid county containing at list one city.");
}
export function find3CountiesWithCities(){
    var list=[];
    if(mockCountyList.length===0)
    {
        test.fatal("Empty mockCountyList.");
    }
    for(var i=0;i<mockCountyList.length;i++)
    {
        if(list.length==3)
        {
            break;
        }
        if(mockCountyList[i].cities.length!=0)
        {
            list.push({
                countyName:mockCountyList[i].countyName,
                firstCity:mockCountyList[i].cities[0]
        });
        }
    }
    if(list.length==3)
    {
        return list;
    }
    else
    {
        test.fatal("Cannot find a valid county containing at list one city.");
    } 
}
