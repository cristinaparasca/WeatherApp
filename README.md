# WeatherApp

Qt/QML weather application built with C++ and MVVM. Users can select a county and city and view current weather data including temperature, feels-like temperature, and humidity. The UI updates dynamically when the selected location changes. UI testing is implemented with Squish and UnitTests with Boost.Test.
<img width="930" height="486" alt="image" src="https://github.com/user-attachments/assets/d447d13f-7228-4b81-b741-b2cdd2318d61" />


## Requirements



- Qt + Qt Creator

- CMake

- MinGW 64-bit

- Git

- vcpkg



## 1. Install vcpkg



```cmd

git clone https://github.com/microsoft/vcpkg.git D:\\vcpkg

cd /d D:\\vcpkg

bootstrap-vcpkg.bat

```



## 2. Install Boost



The project uses the **x64-mingw-dynamic** triplet:



```cmd

D:\\vcpkg\\vcpkg.exe install boost-test:x64-mingw-dynamic

```



Check installation:



```cmd
D:\\vcpkg\\vcpkg.exe list
```



## 3. Configure Qt Creator

Select a **64-bit MinGW kit** and add the following CMake parameters:



```

CMAKE\_TOOLCHAIN\_FILE:PATH=D:/vcpkg/scripts/buildsystems/vcpkg.cmake

VCPKG\_TARGET\_TRIPLET:STRING=x64-mingw-dynamic

```

The **:PATH** and **:STRING** types are required.

Then run **Configure CMake** and **Build Project**.



## 4. Clean Build



If you need to recreate the CMake configuration:



### CMD:

```cmd

rmdir /s /q build

```

### PowerShell:

```cmd
Remove-Item -Recurse -Force .\\build

```

Then run **Configure CMake** again.

## 5. Code Coverage

The project uses **gcov** and **gcovr** for code coverage.

### Install gcovr

Check if `gcovr` is already installed:

```cmd
gcovr --version
```
If not, install it with:
```cmd
py -m pip install gcovr
```
Verify the installation:
```cmd
gcovr --version
```

### Generate Coverage Report
First, **build the test executable** from Qt Creator.
Then run the coverage script:
```cmd
tests\coverage\coverage.bat
```

The generated report can be found in:
```cmd
coverage-results\coverage.html
```

## Toolchain

```

Qt → MinGW 64-bit → CMake → vcpkg → Boost

```
