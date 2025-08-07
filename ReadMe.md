# DE_Wrapper Sample - CAD File Format Converter

## Overview

DE_Wrapper Sample is a demonstration application showcasing the **Data Exchange Wrapper (DE_Wrapper)** functionality in **OpenCASCADE Technology (OCCT)**. This project provides a flexible, configurable CAD file format converter with dynamic library loading capabilities, supporting conversion between various CAD formats including STEP, IGES, STL, glTF, OBJ, PLY, VRML, BREP, and XBF.

### Key Features

- **Multiple CAD Format Support**: Convert between STEP, IGES, STL, glTF, OBJ, PLY, VRML, BREP, and XBF formats
- **Dynamic Library Loading**: Load only necessary Data Exchange libraries at runtime
- **Cross-Platform Support**: Works on Windows, Linux, and macOS
- **Configurable Transfer Process**: Fine-tune conversion parameters via resource files
- **Optional Tessellation**: Generate meshes from CAD models before export
- **Thread-Safe Operations**: Safe multi-threaded library loading

## Table of Contents

- [Requirements](#requirements)
- [Build Instructions](#build-instructions)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Supported Formats](#supported-formats)
- [API Documentation](#api-documentation)
- [Architecture](#architecture)
- [Troubleshooting](#troubleshooting)

## Requirements

### Prerequisites

- **OCCT 7.8.0** or newer
- **CMake 3.15** or newer
- **C++17** compatible compiler:
  - Visual Studio 2019+ (Windows)
  - GCC 7+ (Linux)
  - Clang 9+ (macOS)
- **Optional Dependencies** (for full format support):
  - draco (for mesh compression support in glTF)
  - RapidJSON (for glTF format)

### Supported Platforms

- Windows 10/11 (x64)
- Ubuntu 20.04+ / Debian 10+
- macOS 11.0+ (Big Sur or newer)
- RHEL/CentOS 8+

## Build Instructions

### 1. Clone the Repository

```bash
git clone https://github.com/yourusername/DE_Wrapper-Sample.git
cd DE_Wrapper-Sample
```

### 2. Create Build Directory

```bash
mkdir build
cd build
```

### 3. Configure with CMake

#### Windows (Visual Studio)
```bash
cmake -G "Visual Studio 17 2022" -A x64 \
  -DBUILD_CONSOLE_CPP=ON \
  -DOpenCASCADE_DIR="C:/path/to/occt" \
  -DCMAKE_INSTALL_PREFIX="C:/path/to/install" ..
```

#### Linux/macOS (Unix Makefiles or Ninja)
```bash
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_CONSOLE_CPP=ON \
  -DOpenCASCADE_DIR="/path/to/occt" \
  -DCMAKE_INSTALL_PREFIX="/path/to/install" ..
```

### 4. Build the Project

#### Windows
```bash
cmake --build . --config Release --target install -j 8
```

#### Linux/macOS
```bash
cmake --build . --target install -j 8
# or with make:
make -j8 install
```

## Installation

After successful build and installation:

1. **Library Dependencies**: The installation process automatically copies required OCCT libraries to the installation directory.

2. **Directory Structure**:
```
install_dir/
├── bin/           # Release executables and libraries
├── bind/          # Debug executables and libraries  
├── bini/          # RelWithDebInfo executables and libraries
├── CONF           # Default configuration file
└── LIBS           # Default library list
```

3. **Environment Setup** (Optional):
```bash
# Linux/macOS
export LD_LIBRARY_PATH=/path/to/install/bin:$LD_LIBRARY_PATH
export PATH=/path/to/install/bin:$PATH

# Windows
set PATH=C:\path\to\install\bin;%PATH%
```

## Usage

### Command Line Interface

The console application provides a simple interface for CAD file conversion:

```bash
./ConsoleCPP [options]
```

#### Options

| Option | Description | Required | Example |
|--------|-------------|----------|---------|
| `-from <path>` | Input CAD file path | Yes | `-from model.step` |
| `-to <path>` | Output CAD file path | Yes | `-to model.stl` |
| `-lib <path>` | Path to library list file | No | `-lib custom_libs.txt` |
| `-config <path>` | Path to configuration file | No | `-config myconfig.conf` |
| `--tess` | Enable tessellation before export | No | `--tess` |
| `-dump <path>` | Generate configuration template | No | `-dump newconfig.conf` |

### Basic Examples

#### 1. Simple Format Conversion
```bash
# Convert STEP to STL
./ConsoleCPP -from input.step -to output.stl

# Convert IGES to glTF with tessellation
./ConsoleCPP -from model.iges -to model.gltf --tess
```

#### 2. Using Custom Configuration
```bash
# Use custom configuration for fine-tuned conversion
./ConsoleCPP -from input.stp -to output.obj -config custom.conf
```

#### 3. Generate Configuration Template
```bash
# Create a new configuration file for specified libraries
./ConsoleCPP -lib my_libs.txt -dump my_config.conf
```

### Advanced Examples

#### Batch Processing (Shell Script)
```bash
#!/bin/bash
for file in *.step; do
    ./ConsoleCPP -from "$file" -to "${file%.step}.stl" --tess
done
```

#### Using Custom Library Set
Create a file `minimal_libs.txt`:
```
TKDESTEP
TKDESTL
```

Then use it:
```bash
./ConsoleCPP -from model.stp -to model.stl -lib minimal_libs.txt
```

## Configuration

### Library List File (LIBS)

The LIBS file specifies which Data Exchange libraries to load. Default content:

```
TKDESTEP        # STEP format support
TKDEIGES        # IGES format support  
TKDEGLTF        # glTF format support
TKDEOBJ         # OBJ format support
TKDEPLY         # PLY format support
TKDEVRML        # VRML format support
TKDESTL         # STL format support
TKDECascade     # Native OCCT BREP and XBF format
```

### Configuration File (CONF)

The CONF file contains detailed parameters for each format. Key sections include:

#### Global Settings
```ini
global.priority.vendor : TKDESTEP TKDEIGES TKDESTL
global.length.unit : 1
global.angular.unit : 1
```

#### Format-Specific Settings (Example: STEP)
```ini
provider.STEP.OCC.read.precision.mode : 0
provider.STEP.OCC.read.precision.val : 0.0001
provider.STEP.OCC.read.step.product.name : 1
provider.STEP.OCC.read.step.product.context : 1
provider.STEP.OCC.read.step.shape.repr : 1
provider.STEP.OCC.read.step.assembly.level : 1
provider.STEP.OCC.read.step.shape.relationship : 1
provider.STEP.OCC.read.step.shape.aspect : 1
provider.STEP.OCC.read.step.constructivegeom.representation : 0
provider.STEP.OCC.read.step.stepcaf.subshapes.name : 0
provider.STEP.OCC.read.step.encoding : 0
provider.STEP.OCC.read.step.nonmanifold : 0
provider.STEP.OCC.read.step.ideas : 0
provider.STEP.OCC.read.step.all.shapes : 0
provider.STEP.OCC.read.step.root.transformation : 1
provider.STEP.OCC.read.color : 1
provider.STEP.OCC.read.name : 1
provider.STEP.OCC.read.layer : 1
provider.STEP.OCC.read.props : 1
provider.STEP.OCC.read.metadata : 1

provider.STEP.OCC.write.precision.mode : 0
provider.STEP.OCC.write.precision.val : 0.0001
provider.STEP.OCC.write.step.assembly : 2
provider.STEP.OCC.write.step.schema : 1
provider.STEP.OCC.write.step.product.name : 
provider.STEP.OCC.write.step.tessellated : 2
provider.STEP.OCC.write.step.vertex.mode : 0
provider.STEP.OCC.write.color : 1
provider.STEP.OCC.write.name : 1
provider.STEP.OCC.write.layer : 1
provider.STEP.OCC.write.props : 1
provider.STEP.OCC.write.model.type : 0
```

## Supported Formats

| Format | Extension | Read | Write | Tessellation | Colors | Assembly |
|--------|-----------|------|-------|--------------|--------|----------|
| STEP | .step, .stp | ✅ | ✅ | Optional | ✅ | ✅ |
| IGES | .iges, .igs | ✅ | ✅ | Optional | ✅ | ❌ |
| STL | .stl | ✅ | ✅ | Required | ❌ | ❌ |
| glTF | .gltf, .glb | ✅ | ✅ | Required | ✅ | ✅ |
| OBJ | .obj | ✅ | ✅ | Required | ✅ | ❌ |
| PLY | .ply | ✅ | ✅ | Required | ✅ | ❌ |
| VRML | .vrml, .wrl | ✅ | ✅ | Required | ✅ | ❌ |
| BREP | .brep | ✅ | ✅ | Optional | ❌ | ❌ |
| XBF | .xbf | ✅ | ✅ | Optional | ✅ | ✅ |

## API Documentation

### CoreDE Library API

The CoreDE library provides the main conversion functionality:

```cpp
// Main conversion function
bool Convert(const std::string& theInputPath, 
             const std::string& theOutputPath,
             bool theTessellate = false);

// Configuration management
bool LoadConfiguration(const std::string& theConfigPath);
bool SaveConfiguration(const std::string& theConfigPath);

// Dynamic library management
bool LoadComponent(std::string theComp);
const std::map<std::string, bool>& Components();
```

### Usage in Your Application

```cpp
#include "Converter.hxx"

int main() {
    // Load configuration
    if (!LoadConfiguration("config.conf")) {
        std::cerr << "Failed to load configuration" << std::endl;
        return 1;
    }
    
    // Perform conversion with tessellation
    bool success = Convert("input.step", "output.stl", true);
    
    if (success) {
        std::cout << "Conversion successful!" << std::endl;
    }
    
    return success ? 0 : 1;
}
```

## Architecture

### Component Overview

```
DE_Wrapper-Sample/
├── src/
│   ├── CoreDE/          # Core library with conversion logic
│   │   ├── Converter.hxx
│   │   └── Converter.cxx
│   └── ConsoleCPP/      # Command-line interface
│       └── Console.cxx
├── data/
│   ├── CONF             # Default configuration
│   └── LIBS             # Default library list
└── adm/
    └── cmake/           # CMake modules
        └── FindOCCT.cmake
```

### Design Patterns

- **Singleton Pattern**: Global DE_Wrapper instance management
- **Factory Pattern**: Dynamic component loading
- **Mutex Protection**: Thread-safe library loading
- **Resource Management**: External configuration files

## Troubleshooting

### Common Issues

#### 1. Library Not Found
**Error**: `Could not open: [libTKDESTEP.so] or [TKDESTEP.so]`

**Solution**: 
- Ensure OCCT libraries are in the library path
- Check file permissions
- Verify library naming convention

#### 2. Conversion Failure
**Error**: `Cannot read file: unsupported format`

**Solution**:
- Verify the input file format
- Check if required library is listed in LIBS file
- Ensure file is not corrupted

#### 3. Tessellation Issues
**Error**: `Tessellation failed for shape`

**Solution**:
- Adjust mesh parameters in configuration
- Check model validity using OCCT tools
- Try different precision values

### Performance Tips

1. **Library Loading**: Load only necessary libraries for your formats
2. **Tessellation**: Adjust mesh deflection for quality vs. speed
3. **Parallel Processing**: Use thread pools for batch conversions
4. **Memory Management**: Clear document between conversions for large batches

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request

## License

This sample is provided under the same license as OCCT. Please refer to OCCT documentation for licensing details.

## References

- [OCCT Documentation](https://dev.opencascade.org/doc/overview/html/index.html)
- [DE_Wrapper User Guide](https://dev.opencascade.org/doc/overview/html/occt_user_guides__de_wrapper.html)
- [OCCT Data Exchange](https://dev.opencascade.org/doc/overview/html/occt_user_guides__xde.html)

## Support

For issues, questions, or suggestions:
- Open an issue on GitHub
- Consult OCCT forums
- Review OCCT documentation

---
**Version**: 1.0.0  
**Last Updated**: 2025-08-07  
**Compatibility**: OCCT 7.8.0+