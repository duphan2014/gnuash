# PowerShell script to test Windows build environment for Gnuash

Write-Host "Testing Windows build environment for Gnuash..." -ForegroundColor Cyan
Write-Host ""

function Test-Command {
    param($CommandName)
    try {
        Get-Command $CommandName -ErrorAction Stop | Out-Null
        return $true
    } catch {
        return $false
    }
}

function Test-PkgConfig {
    param($Package)
    try {
        & pkg-config --exists $Package 2>$null
        return $LASTEXITCODE -eq 0
    } catch {
        return $false
    }
}

Write-Host "1. Testing compiler availability..."
if (Test-Command "gcc") {
    Write-Host "   ✓ gcc found" -ForegroundColor Green
    $version = & gcc --version 2>$null | Select-Object -First 1
    Write-Host "   $version" -ForegroundColor Gray
} else {
    Write-Host "   ✗ gcc not found" -ForegroundColor Red
    Write-Host "   Please install MinGW-w64 or MSYS2" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "2. Testing make availability..."
if (Test-Command "mingw32-make") {
    Write-Host "   ✓ mingw32-make found" -ForegroundColor Green
    $version = & mingw32-make --version 2>$null | Select-Object -First 1
    Write-Host "   $version" -ForegroundColor Gray
} else {
    Write-Host "   ✗ mingw32-make not found" -ForegroundColor Red
    Write-Host "   Please install mingw32-make via MSYS2 or MinGW-w64" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "3. Testing pkg-config availability..."
if (Test-Command "pkg-config") {
    Write-Host "   ✓ pkg-config found" -ForegroundColor Green
    $version = & pkg-config --version 2>$null
    Write-Host "   Version: $version" -ForegroundColor Gray
} else {
    Write-Host "   ⚠ pkg-config not found (optional but recommended)" -ForegroundColor Yellow
    Write-Host "   Install via MSYS2 for better SDL2 detection" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "4. Testing SDL2 availability..."
if (Test-PkgConfig "sdl2") {
    Write-Host "   ✓ SDL2 found via pkg-config" -ForegroundColor Green
    $version = & pkg-config --modversion sdl2 2>$null
    Write-Host "   Version: $version" -ForegroundColor Gray
} else {
    Write-Host "   ⚠ SDL2 not found via pkg-config" -ForegroundColor Yellow
    Write-Host "   Make sure SDL2 development libraries are installed" -ForegroundColor Yellow
}

Write-Host ""
Write-Host "5. Testing additional SDL2 libraries..."
$sdlLibs = @("SDL2_ttf", "SDL2_mixer", "SDL2_image")
foreach ($lib in $sdlLibs) {
    if (Test-PkgConfig $lib) {
        Write-Host "   ✓ $lib found" -ForegroundColor Green
    } else {
        Write-Host "   ⚠ $lib not found" -ForegroundColor Yellow
    }
}

Write-Host ""
Write-Host "Test completed. If you see any ✗ marks, please refer to WINDOWS_SETUP.md" -ForegroundColor Cyan
Write-Host ""
Write-Host "Press any key to continue..."
$Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown") | Out-Null