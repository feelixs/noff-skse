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

echo.
echo Build succeeded!
pause
