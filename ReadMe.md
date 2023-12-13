# DE_Wrapper Sample Usage Guide

## Overview

This guide presents a sample implementation utilizing the DE_Wrapper functionality in OCCT (Open CASCADE Technology). The primary objective is to showcase the integration of OCCT DE components through the DE_Wrapper, applicable to both open-source and commercial components. The sample allows for the configuration of the transfer process using a resource file, loading only the necessary DE libraries dynamically.

## Table of Contents

- [Build](#build)
- [Usage](#usage)

## Build

The project is configured with CMake. Dependencies required:

- OCCT 7.8.0 or newer.

Sample command to build:

```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -DBUILD_CONSOLE_CPP=TRUE -DOpenCASCADE_DIR=D:/occt-vc143-64 -DCMAKE_INSTALL_PREFIX=D:/sample_install ..
cmake --build --config Release --target install -j 10 ..
```
## Usage

To use the sample:

1. **Copy dependency to folder**: Copy each dynamic (shared) library of OCCT and its dependencies (tbb, jemalloc, freeimage, ...) to the project folder.

2. **Run the Console Application**: Execute the compiled console application with appropriate command-line arguments. Example:

   ```bash
   ./console  [-from <path>] [-to <path>] [-lib <path>] [-config <path>] [--tess] [--dump] 
   - `-from`: Specify the path to the input CAD file.
   - `-to`: Specify the path to the output CAD file.
   - `-lib`: (Optional) Specify the path to the file with a list of libraries.
   - `-config`: (Optional) Specify the path to the resource file.
   - `--tess`: (Optional) Activate tessellation for the input model before export.
   ```
Example command:
```bash
  ./console -from /path/to/input.cad -to /path/to/output.cad
```
**3. Update Config Files:** By default, CONF and LIBS files are installed with the console. You can modify the LIBS file with the names of DataExchange libs. The default content is as follows:
```
TKDESTEP
TKDEIGES
TKDEGLTF
TKDEOBJ
TKDEPLY
TKDEVRML
TKDESTL
```
Additionally, you can modify transfer parameters for each DE component using the CONF file. It is a resource file with key-value parameters. For more details, please refer to the [DE_Wrapper documentation](https://dev.opencascade.org/doc/overview/html/occt_user_guides__de_wrapper.html).

To create a new CONF file with new LIBS, you can use the following command:
```bash
  ./console -lib LIBS -dump NEWCONF
```
The 'NEWCONF' file will contain the new resource file for the LIBS components.
