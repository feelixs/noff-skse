@echo off
setlocal

set "PLUGINS=Data\SKSE\Plugins"

if not exist "build\noff.dll" (
    echo ERROR: build\noff.dll not found. Run build.bat first.
    pause
    exit /b 1
)

mkdir "%PLUGINS%" 2>nul
copy /y "build\noff.dll" "%PLUGINS%\noff.dll"
copy /y "noff.json" "%PLUGINS%\noff.json"

del /q "noff.zip" 2>nul
"C:\Program Files\7-Zip\7z.exe" a "noff.zip" "Data"

echo.
echo Done: noff.zip
pause
