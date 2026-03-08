@echo off
setlocal

set "PLUGINS=Data\SKSE\Plugins"

if not exist "build\noff.dll" (
    echo ERROR: build\noff.dll not found. Run build.bat first.
    pause
    exit /b 1
)

for /f "tokens=2" %%V in ('findstr /c:"    VERSION " CMakeLists.txt') do (
    set "VERSION=%%V"
    goto :found_version
)
:found_version

set "ZIPNAME=NOFF-v%VERSION%.zip"

mkdir "%PLUGINS%" 2>nul
copy /y "build\noff.dll" "%PLUGINS%\noff.dll"
copy /y "noff.json" "%PLUGINS%\noff.json"

del /q "%ZIPNAME%" 2>nul
"C:\Program Files\7-Zip\7z.exe" a "%ZIPNAME%" "Data"

echo.
echo Done: %ZIPNAME%
pause
