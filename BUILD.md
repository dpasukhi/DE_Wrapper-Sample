# Build Instructions for DE_Wrapper Sample

## Quick Start

### Prerequisites
- OCCT 7.8.0+ installed
- CMake 3.15+
- C++17 compiler

### Build Commands

#### Windows (Visual Studio)
```powershell
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 `
  -DBUILD_CONSOLE_CPP=ON `
  -DOpenCASCADE_DIR="C:/occt" `
  -DCMAKE_INSTALL_PREFIX="C:/install" ..
cmake --build . --config Release --target install -j 8
```

#### Linux
```bash
mkdir build && cd build
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_CONSOLE_CPP=ON \
  -DOpenCASCADE_DIR="/usr/local/occt" \
  -DCMAKE_INSTALL_PREFIX="/usr/local" ..
ninja install
```

#### macOS
```bash
mkdir build && cd build
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_CONSOLE_CPP=ON \
  -DOpenCASCADE_DIR="/usr/local/occt" \
  -DCMAKE_INSTALL_PREFIX="/usr/local" ..
ninja install
```

## CMake Options

| Option | Description | Default |
|--------|-------------|---------|
| `BUILD_CONSOLE_CPP` | Build console application | ON |
| `OpenCASCADE_DIR` | Path to OCCT installation | Required |
| `CMAKE_INSTALL_PREFIX` | Installation directory | Platform default |
| `CMAKE_BUILD_TYPE` | Build configuration (Unix) | Release |

## Build Configurations

### Debug Build
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ...
```

### Release with Debug Info
```bash
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ...
```

### MinGW on Windows
```bash
cmake -G "MinGW Makefiles" \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_CONSOLE_CPP=ON \
  -DOpenCASCADE_DIR="C:/occt-mingw" ..
mingw32-make -j8 install
```

## Troubleshooting

### OCCT Not Found
If CMake cannot find OCCT:
1. Set `OpenCASCADE_DIR` to OCCT's cmake directory
2. Or set environment variable: `export OpenCASCADE_DIR=/path/to/occt/lib/cmake/opencascade`

### Missing Dependencies
Install required OCCT dependencies:
- **Windows**: TBB, FreeImage (via vcpkg or manual)
- **Linux**: `sudo apt-get install libtbb-dev libfreeimage-dev`
- **macOS**: `brew install tbb freeimage`

### Library Path Issues
After installation, set library paths:
```bash
# Linux
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/install/bin

# macOS  
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:/path/to/install/bin

# Windows
set PATH=%PATH%;C:\path\to\install\bin
```

## Cross-Compilation

### For ARM64 on x86_64
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=arm64-toolchain.cmake ...
```

### For Windows on Linux (MinGW)
```bash
cmake -DCMAKE_TOOLCHAIN_FILE=mingw-w64-toolchain.cmake ...
```

## Package Generation

### Create Distribution Package
```bash
cmake --build . --target package
```

This creates:
- Windows: `.zip` and `.exe` installer
- Linux: `.tar.gz` and `.deb`
- macOS: `.tar.gz` and `.dmg`

## Testing Build

### Run Tests
```bash
cd install/bin
./ConsoleCPP -from ../test/model.step -to output.stl --tess
```

### Verify Installation
```bash
./ConsoleCPP --help
```

## Advanced Options

### Custom OCCT Build
If using custom OCCT build:
```bash
cmake -DOpenCASCADE_DIR=/custom/occt/build \
      -DCMAKE_PREFIX_PATH=/custom/dependencies ..
```

### Static Linking
For static builds (if OCCT built statically):
```bash
cmake -DBUILD_SHARED_LIBS=OFF ..
```

### Ninja Multi-Config
```bash
cmake -G "Ninja Multi-Config" ..
cmake --build . --config Release
cmake --build . --config Debug
```