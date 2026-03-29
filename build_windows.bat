@echo off
REM Windows build script for Gnuash
REM This script provides an easy way to build the project on Windows

echo Building Gnuash for Windows...
echo.

REM Check if make is available
where mingw32-make >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: 'make' command not found!
    echo Please install one of the following:
    echo   1. MSYS2 ^(recommended^): https://www.msys2.org/
    echo   2. MinGW-w64: https://www.mingw-w64.org/
    echo   3. Git for Windows ^(includes make^)
    echo.
    pause
    exit /b 1
)

REM Check if gcc is available
where gcc >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: 'gcc' compiler not found!
    echo Please install MinGW-w64 or MSYS2
    echo.
    pause
    exit /b 1
)

REM Check if pkg-config is available
where pkg-config >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo WARNING: 'pkg-config' not found. Using fallback library flags.
    echo For better SDL2 detection, install pkg-config via MSYS2
    echo.
)

REM Build the project
echo Running make...
mingw32-make clean
mingw32-make all

if %ERRORLEVEL% EQU 0 (
    echo.
    echo SUCCESS: Build completed successfully!
    echo Executable: gnuash.exe
    echo.
    echo To run the game, type: gnuash.exe
    echo.
) else (
    echo.
    echo ERROR: Build failed!
    echo Please check the error messages above.
    echo.
)

pause