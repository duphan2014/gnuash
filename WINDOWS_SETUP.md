# Windows Setup Guide for Gnuash

This guide will help you set up the development environment and build Gnuash on Windows.

## Prerequisites

### Option 1: MSYS2 (Recommended)

MSYS2 provides a Unix-like environment on Windows with package management.

1. **Download and install MSYS2**:
   - Visit: https://www.msys2.org/
   - Download the installer and run it
   - Follow the installation instructions

2. **Open MSYS2 terminal** and update the package database:
   ```bash
   pacman -Syu
   ```

3. **Install development tools and SDL2**:
   ```bash
   # Install base development tools
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   pacman -S mingw-w64-x86_64-pkg-config
   
   # Install SDL2 and extensions
   pacman -S mingw-w64-x86_64-SDL2
   pacman -S mingw-w64-x86_64-SDL2_ttf
   pacman -S mingw-w64-x86_64-SDL2_mixer
   pacman -S mingw-w64-x86_64-SDL2_image
   ```

4. **Add MSYS2 to your PATH**:
   - Add `C:\msys64\mingw64\bin` to your Windows PATH environment variable
   - Or use the MSYS2 MinGW 64-bit terminal

### Option 2: Standalone MinGW-w64

If you prefer not to use MSYS2, you can install MinGW-w64 standalone:

1. **Install MinGW-w64**:
   - Download from: https://www.mingw-w64.org/downloads/
   - Or use w64devkit: https://github.com/skeeto/w64devkit

2. **Install SDL2 libraries manually**:
   - Download SDL2 development libraries from: https://www.libsdl.org/download-2.0.php
   - Download SDL2_ttf from: https://www.libsdl.org/projects/SDL_ttf/
   - Download SDL2_mixer from: https://www.libsdl.org/projects/SDL_mixer/
   - Download SDL2_image from: https://www.libsdl.org/projects/SDL_image/
   - Extract and copy the libraries to your MinGW installation

### Option 3: Visual Studio (Alternative)

If you prefer Visual Studio:

1. **Install Visual Studio 2022** with C++ development tools
2. **Install vcpkg** package manager
3. **Install SDL2 via vcpkg**:
   ```cmd
   vcpkg install sdl2 sdl2-ttf sdl2-mixer sdl2-image
   ```

## Building the Project

### Using the Windows Batch Script (Easiest)

1. **Open Command Prompt** in the project directory
2. **Run the build script**:
   ```cmd
   build_windows.bat
   ```

### Using Make Directly

1. **Open MSYS2 MinGW 64-bit terminal** (or your preferred terminal)
2. **Navigate to the project directory**:
   ```bash
   cd /c/Projects/c/gnuash
   ```
3. **Build the project**:
   ```bash
   mingw32-make clean
   mingw32-make all
   ```

### Manual Compilation (If Make is not available)

```cmd
gcc -Wall -g -I src -c src/audio.c -o src/audio.o
gcc -Wall -g -I src -c src/ball.c -o src/ball.o
gcc -Wall -g -I src -c src/game.c -o src/game.o
gcc -Wall -g -I src -c src/input.c -o src/input.o
gcc -Wall -g -I src -c src/main.c -o src/main.o
gcc -Wall -g -I src -c src/platform.c -o src/platform.o
gcc -Wall -g -I src -c src/renderer.c -o src/renderer.o
gcc -Wall -g -I src -c src/ui.c -o src/ui.o
gcc -Wall -g -I src -c src/sprite.c -o src/sprite.o
gcc -Wall -g -I src -c src/scene.c -o src/scene.o

gcc -Wall -g -o gnuash.exe src/audio.o src/ball.o src/game.o src/input.o src/main.o src/platform.o src/renderer.o src/ui.o src/sprite.o src/scene.o -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image
```

## Running the Game

After successful compilation:
Make sure you include all the dll files required. If dlls missing, the runtime error dialog will appear e.g. SDL2_ttf.dll is missing. Just copy them to your project folder using 

```cp /mingw64/bin/SDL2.dll .
```

Run the game by

```cmd
./gnuash.exe
```

Make sure the SDL2 DLL files are in your PATH or in the same directory as the executable.

## Troubleshooting

### Common Issues

1. **"SDL.h not found"**:
   - Ensure SDL2 development libraries are installed
   - Check that include paths are correct
   - Verify pkg-config can find SDL2: `pkg-config --cflags sdl2`

2. **"Cannot find -lSDL2"**:
   - Ensure SDL2 libraries are installed
   - Check library paths
   - Verify pkg-config can find SDL2: `pkg-config --libs sdl2`

3. **"DLL not found" at runtime**:
   - Copy SDL2 DLL files to the same directory as gnuash.exe. e.g. cp /mingw64/bin/SDL2.dll .
   - Or ensure SDL2 bin directory is in your PATH
   - # Copy ALL DLLs from MSYS2 MinGW64 to your project folder
   ```
      cp /mingw64/bin/*.dll .
   ```
   # If that fails due to too many files, do it in batches:
   ```
      find /mingw64/bin -name "*.dll" -exec cp {} . \;
   ```
   # Use ldd to see exactly which DLLs your executable needs:
   ```
      ldd gnuash.exe
   ```
   # Then copy only those specific ones

   Alternative - create a batch script to copy commonly needed DLLs:
   ```
   # Create a copy script
   cat > copy_dlls.sh << 'EOF'
   #!/bin/bash
   # Core SDL2 DLLs
   cp /mingw64/bin/SDL2.dll .
   cp /mingw64/bin/SDL2_*.dll .

   # MinGW runtime DLLs  
   cp /mingw64/bin/libgcc_s_seh-1.dll .
   cp /mingw64/bin/libwinpthread-1.dll .
   cp /mingw64/bin/libstdc++-6.dll .

   # All other DLLs (catches everything)
   cp /mingw64/bin/lib*.dll .

   echo "All DLLs copied!"
   EOF

   # Make it executable and run
   chmod +x copy_dlls.sh
   ./copy_dlls.sh
   ```

4. **Make command not found**:
   - Install MSYS2 or MinGW-w64
   - Add the bin directory to your PATH
   - Use the provided batch script instead

### Getting Help

If you encounter issues:

1. **Check the build output** for specific error messages
2. **Verify all prerequisites** are properly installed
3. **Try the MSYS2 route** if other methods fail
4. **Check Windows-specific SDL2 documentation**

## Development Notes

- The project now supports Windows, macOS, and Linux
- SDL2 headers are included differently on each platform
- Windows executables have `.exe` extension automatically added
- Use forward slashes (/) in paths for cross-platform compatibility