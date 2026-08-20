# WeatherApp

Qt/QML weather application built with C++ and MVVM. Users can select a county and city and view current weather data including temperature, feels-like temperature, and humidity. The UI updates dynamically when the selected location changes. UI testing is implemented with Squish and UnitTests with Boost.Test.



\## Requirements



\- Qt + Qt Creator

\- CMake

\- MinGW 64-bit

\- Git

\- vcpkg



\## 1. Install vcpkg



```cmd

git clone https://github.com/microsoft/vcpkg.git D:\\vcpkg

cd /d D:\\vcpkg

bootstrap-vcpkg.bat

```



\## 2. Install Boost



The project uses the \*\*x64-mingw-dynamic\*\* triplet:



```cmd

D:\\vcpkg\\vcpkg.exe install boost-test:x64-mingw-dynamic

```



Check installation:



```cmd
D:\\vcpkg\\vcpkg.exe list
```



\## 3. Configure Qt Creator

Select a \*\*64-bit MinGW kit\*\* and add the following CMake parameters:



```

CMAKE\_TOOLCHAIN\_FILE:PATH=D:/vcpkg/scripts/buildsystems/vcpkg.cmake

VCPKG\_TARGET\_TRIPLET:STRING=x64-mingw-dynamic

```

The \*\*:PATH\*\* and \*\*:STRING\*\* types are required.

Then run \*\*Configure CMake\*\* and \*\*Build Project\*\*.



\## 4. Clean Build



If you need to recreate the CMake configuration:



\### CMD:

```cmd

rmdir /s /q build

```

\### PowerShell:

```cmd
Remove-Item -Recurse -Force .\\build

```

Then run \*\*Configure CMake\*\* again.



\## Toolchain

```

Qt → MinGW 64-bit → CMake → vcpkg → Boost

```

