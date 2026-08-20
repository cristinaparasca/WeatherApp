import QtQuick
import WeatherInfoMVVM
import QtQuick.Controls.Basic
import QtCharts 2.11

Window {
    id: root
    width: 940
    height: 500
    visible: true
    title: qsTr("Weather Forecast")

    Rectangle {
        anchors.fill: parent

        Image {
            anchors.fill: parent
            source: "https://wttr.in/" + weatherViewModel.city + ".png"
            z: 0
        }

        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: 70
            color: "#00000000"
            z: 1
            Column {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.rightMargin: 10
                spacing: 10
                Row {
                    spacing: 20
                    ToolButton {
                        objectName: "cityToolBtn"
                        text: "City: " + weatherViewModel.city
                        icon.source: "icon/location.png"
                        background: Rectangle {
                            color: "white"
                            radius: 5
                        }
                    }
                    ToolButton {
                        objectName: "realTemperatureToolBtn"
                        text: "Temperature: " + weatherViewModel.realTemperature + "°C"
                        icon.source: "icon/thermometer.png"
                        background: Rectangle {
                            color: "white"
                            radius: 5
                        }
                    }
                    ToolButton {
                        objectName: "feelsLikeTemperatureToolBtn"
                        text: "FeelsLike: " + weatherViewModel.feelsLikeTemperature + "°C"

                        icon.source: "icon/thermometer.png"
                        background: Rectangle {
                            color: "white"
                            radius: 5
                        }
                    }
                    ToolButton {
                        objectName: "humidityToolBtn"
                        text: "Humidity: " + weatherViewModel.humidity + "%"
                        icon.source: "icon/humidity.png"
                        icon.color: "cornflowerblue"
                        background: Rectangle {
                            color: "white"
                            radius: 5
                        }
                    }
                }
                Row {
                    anchors.rightMargin: 10
                    anchors.right: parent.right
                    Button {
                        objectName: "SelectLocationBtn"
                        text: "Select location"

                        contentItem: Text {
                            text: parent.text
                            font.pixelSize: 16
                            font.bold: true
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                        background: Rectangle {
                            color: "slategray"
                            radius: 10
                        }
                        onClicked: {
                            cityDialog.open();
                        }
                    }
                }
            }

            Dialog {
                id: cityDialog
                objectName: "selectLocationDialog"
                title: "Select location"
                modal: true

                standardButtons: Dialog.Cancel
                anchors.centerIn: Overlay.overlay
                width: 300
                height: 250
                ListView {
                    objectName: "countiesListView"
                    anchors.fill: parent
                    reuseItems: false
                    model: weatherViewModel.countiesModel
                    clip: true
                    spacing: 5
                    delegate: Column {
                        id: delegateRoot
                        objectName: "countyDelegate_" + name
                        width: parent ? parent.width : 280 // Ensure explicit width
                        property bool expanded: false
                        signal debugMessage(string message)
                        onExpandedChanged: {
                            debugMessage("EXPANDED CHANGED: " + name + " => " + delegateRoot.expanded);
                        }

                        Button {
                            id: countyButton
                            objectName: "county_" + name
                            text: delegateRoot.expanded ? "▼ " + name : "▶ " + name
                            height: 25
                            width: parent.width // Bind button width to delegate container

                            onClicked: {
                                debugMessage("CLICKED COUNTY: " + name + " BEFORE:  " + expanded);
                                delegateRoot.expanded = !delegateRoot.expanded;
                                debugMessage("CLICKED COUNTY: " + name + " AFTER: " + expanded);
                            }
                        }

                        Column {
                            objectName: "citiesColumn_" + name
                            width: parent.width
                            height: delegateRoot.expanded ? implicitHeight : 0
                            clip: true

                            Repeater {
                                model: cities

                                delegate: Button {
                                    objectName: "city_" + modelData
                                    text: modelData

                                    width: parent.width
                                    height: delegateRoot.expanded ? 25 : 0
                                    visible: delegateRoot.expanded

                                    onDoubleClicked: {
                                        delegateRoot.expanded = false;
                                        weatherViewModel.city = modelData;
                                        cityDialog.close();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
