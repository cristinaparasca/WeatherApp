# Squish Setup and Automated Testing for the Qt Application

## Initial Setup

I downloaded and installed the **Squish** version compatible with the **Qt** version used by the application.

After launching Squish:

- Created a new **Test Suite**.
- Configured the **AUT (Application Under Test)** by selecting the application's executable.
- Assigned the AUT to the test suite from **Suite Settings**.
- Configured the application to be launched automatically when running the tests.

## Preparing the Qt Quick Executable

In order for Squish to launch a Qt Quick application, the `windeployqt` utility must be executed first.

Open the Qt command prompt corresponding to the Qt version in use (for example from the Start Menu: `Qt\6.11.1\mingw_64`) and run the following command from the directory where the application executable is located:

```cmd
windeployqt appWeatherInfoMVVM.exe
```

After this step, the application can be launched both from Command Prompt and directly by Squish.

## Creating and Running Tests

To create a test:

1. Create a new **Test Case**.
2. Click **Record**.
3. Perform the desired actions in the application.
4. Squish automatically generates the test code.

When the test is executed, the recorded actions will be replayed automatically and the result will be **Success** or **Failure** depending on the application's behavior.

### Recommendations

- Add extra verifications using **Object Inspect** to validate object states and values.
- Define the `objectName` property in QML for elements that need to be identified in tests.
- Keep the **Object Map** organized and use meaningful names for mapped objects.

Example:

```text
weatherForecastSelectLocationButton_2
```

can be renamed to:

```text
SelectLocationBtn
```

---

## Challenges Encountered

### Identifying Objects by `objectName`

Initially, I tried identifying objects using only the `objectName` property, but this is not sufficient.

At minimum, both `objectName` and `type` should be used:

```javascript
var listView = waitForObject("{name='countiesListView' type='QQuickListView'}");
```

In some cases, the container must also be specified:

```javascript
var countyFoundObj = waitForObject({
    "container": names.weatherForecastOverlay,
    "objectName": "county_Alba",
    "type": "Button"
});
```

`names` is the object exported by Squish that contains the symbolic names defined in the **Object Map**.

### Inspecting Object Properties

To see all available properties of an object, the application can be run in **Debug Mode** from Squish.

After locating the object in the **Object Tree**:

1. Select the desired object.
2. Right-click on it.
3. Choose **Copy Real Name**.

The copied value contains all the properties Squish uses to identify the object and can be very useful when building `waitForObject()` expressions or troubleshooting object recognition issues.

### ListView Synchronization Issues

I experienced synchronization issues when interacting with a `ListView` whose items expand when clicked.

Initially, the only reliable solution was:

```javascript
snooze()
```

I also tried:

- checking the `visible` property
- checking the `expanded` property
- synchronizing against other UI elements

None of these approaches proved reliable enough.

The solution that worked consistently was implementing a **retry mechanism for the click that triggers the expansion**. In some situations, the list items are not fully rendered when the first click occurs, and repeating the action resolves the issue.

---

## Implemented Tests

The application was launched with the **fake-service** argument so that all tests ran against mock data with predictable results.

The following tests were successfully implemented:

- Verify that the county list (`countyList`) is populated correctly.
- Verify that weather information labels are updated after double-clicking a city.
- Verify that the city selection dialog closes after a city is selected.
- Verify the expand/collapse behavior of the `ListView`.
- Perform three consecutive updates and verify that the selected city label is updated correctly each time.