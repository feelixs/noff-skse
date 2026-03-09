@echo off
setlocal

:: Set up MSVC environment
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 (
    echo Failed to set up MSVC environment!
    pause
    exit /b 1
)

set "VCPKG_PKGS=C:\Users\mmh\vcpkg\packages"
set "CMAKE_PREFIX_PATH=%VCPKG_PKGS%\spdlog_x64-windows-static-md;%VCPKG_PKGS%\fmt_x64-windows-static-md;%VCPKG_PKGS%\rapidcsv_x64-windows-static-md"
set "CMAKE_INCLUDE_PATH=%VCPKG_PKGS%\rapidcsv_x64-windows-static-md\include"

set "BUILD_START=%TIME%"
echo Started: %DATE% %BUILD_START%

rd /s /q build 2>nul
cmake -B build -S . -G Ninja ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DVCPKG_MANIFEST_MODE=OFF ^
    -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDLL ^
    "-DCMAKE_PREFIX_PATH=%CMAKE_PREFIX_PATH%" ^
    "-DCMAKE_INCLUDE_PATH=%CMAKE_INCLUDE_PATH%"
if errorlevel 1 (
    echo.
    echo Configure failed!
    pause
    exit /b 1
)

cmake --build build
if errorlevel 1 (
    echo.
    echo Build failed!
    pause
    exit /b 1
)

for /f "tokens=1-3 delims=:.," %%a in ("%BUILD_START%") do set /a BUILD_START_S=%%a*3600+%%b*60+%%c
for /f "tokens=1-3 delims=:.," %%a in ("%TIME%") do set /a BUILD_END_S=%%a*3600+%%b*60+%%c
set /a BUILD_ELAPSED=BUILD_END_S-BUILD_START_S
set /a BUILD_M=BUILD_ELAPSED/60
set /a BUILD_S=BUILD_ELAPSED%%60

echo.
echo Build succeeded!
echo Finished: %DATE% %TIME%
echo Time taken: %BUILD_M%m %BUILD_S%s
call "%~dp0zipup.bat"
