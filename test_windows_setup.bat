@echo off
REM Simple test script to verify Windows build environment

echo Testing Windows build environment for Gnuash...
echo.

echo 1. Testing compiler availability...
where gcc >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo   ✓ gcc found
    gcc --version | findstr "gcc"
) else (
    echo   ✗ gcc not found
    echo   Please install MinGW-w64 or MSYS2
)

echo.
echo 2. Testing make availability...
where mingw32-make >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo   ✓ mingw32-make found
    mingw32-make --version | findstr "GNU Make"
) else (
    echo   ✗ mingw32-make not found
    echo   Please install make via MSYS2 or MinGW-w64
)

echo.
echo 3. Testing pkg-config availability...
where pkg-config >nul 2>&1
if %ERRORLEVEL% EQU 0 (
    echo   ✓ pkg-config found
    pkg-config --version
) else (
    echo   ⚠ pkg-config not found ^(optional but recommended^)
    echo   Install via MSYS2 for better SDL2 detection
)

echo.
echo 4. Testing SDL2 availability...
pkg-config --exists sdl2 2>nul
if %ERRORLEVEL% EQU 0 (
    echo   ✓ SDL2 found via pkg-config
    pkg-config --modversion sdl2
) else (
    echo   ⚠ SDL2 not found via pkg-config
    echo   Make sure SDL2 development libraries are installed
)

echo.
echo 5. Testing additional SDL2 libraries...
pkg-config --exists SDL2_ttf 2>nul
if %ERRORLEVEL% EQU 0 (
    echo   ✓ SDL2_ttf found
) else (
    echo   ⚠ SDL2_ttf not found
)

pkg-config --exists SDL2_mixer 2>nul
if %ERRORLEVEL% EQU 0 (
    echo   ✓ SDL2_mixer found
) else (
    echo   ⚠ SDL2_mixer not found
)

pkg-config --exists SDL2_image 2>nul
if %ERRORLEVEL% EQU 0 (
    echo   ✓ SDL2_image found
) else (
    echo   ⚠ SDL2_image not found
)

echo.
echo Test completed. If you see any ✗ marks, please refer to WINDOWS_SETUP.md
echo.
pause