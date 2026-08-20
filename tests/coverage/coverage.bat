@echo off
setlocal

echo.
echo ==============================
echo Running tests
echo ==============================

"..\..\build\Desktop_Qt_6_11_1_MinGW_64_bit-Debug\appWeatherInfoMVVMTests.exe"

if errorlevel 1 (
    echo.
    echo Tests FAILED!
    pause
    exit /b 1
)

echo.
echo ==============================
echo Generating coverage report
echo ==============================

mkdir "..\..\coverage-results" 2>nul

python -m gcovr ^
    -r "../.." ^
    --object-directory "../../build/Desktop_Qt_6_11_1_MinGW_64_bit-Debug" ^
    --filter "../../src/" ^
    --filter "../../includes/*" ^
    --exclude "../../tests/.*" ^
    --exclude "../../coverage-results/.*" ^
    --exclude ".*autogen.*" ^
    --exclude ".*moc_.*" ^
    --exclude ".*qrc_.*" ^
    --exclude ".*qmlcache.*" ^
    --html ^
    --html-details ^
    -o "../../coverage-results/coverage.html"

if errorlevel 1 (
    echo.
    echo Failed to generate coverage report!
    pause
    exit /b 1
)

echo.
echo ==============================
echo Coverage generated successfully
echo ==============================
echo.
echo Report:
echo ../../coverage-results/coverage.html
echo.

pause