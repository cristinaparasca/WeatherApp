echo.
echo Generating coverage report...

mkdir "D:\Exercitii\WeatherInfoMVVM\coverage" 2>nul

python -m gcovr -r "D:\Exercitii\WeatherInfoMVVM" --object-directory "D:\Exercitii\WeatherInfoMVVM\build\Desktop_Qt_6_11_1_MinGW_64_bit-Debug" --exclude "^tests/.*" --exclude ".*autogen.*" --exclude ".*moc_.*" --exclude ".*qrc_.*" --exclude ".*qmlcache.*" --html --html-details -o "D:\Exercitii\WeatherInfoMVVM\coverage\coverage.html"

pause