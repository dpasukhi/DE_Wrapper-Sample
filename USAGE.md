# Usage Guide for DE_Wrapper Sample

## Basic Usage

### Simple Conversion
Convert a STEP file to STL:
```bash
./ConsoleCPP -from model.step -to model.stl
```

### With Tessellation
Generate mesh before export (required for STL, OBJ, PLY):
```bash
./ConsoleCPP -from model.iges -to model.stl --tess
```

## Command Line Options

```bash
./ConsoleCPP [-from <input>] [-to <output>] [-lib <libs>] [-config <conf>] [--tess] [-dump <conf>]
```

### Required Arguments
- `-from <path>`: Input CAD file
- `-to <path>`: Output CAD file

### Optional Arguments
- `-lib <path>`: Custom library list file (default: LIBS)
- `-config <path>`: Custom configuration file (default: CONF)
- `--tess`: Enable tessellation/meshing
- `-dump <path>`: Generate configuration template

## File Format Support

### Input/Output Formats

| Extension | Format | Library | Tessellation |
|-----------|--------|---------|--------------|
| .step, .stp | STEP | TKDESTEP | Optional |
| .iges, .igs | IGES | TKDEIGES | Optional |
| .stl | STL | TKDESTL | Required |
| .gltf, .glb | glTF | TKDEGLTF | Required |
| .obj | OBJ | TKDEOBJ | Required |
| .ply | PLY | TKDEPLY | Required |
| .vrml, .wrl | VRML | TKDEVRML | Required |
| .brep | BREP | TKDECascade | Optional |
| .xbf | XBF | TKDECascade | Optional |

## Examples

### 1. STEP to STL Conversion
```bash
# Basic conversion (will auto-tessellate)
./ConsoleCPP -from part.step -to part.stl

# With explicit tessellation
./ConsoleCPP -from part.step -to part.stl --tess
```

### 2. IGES to glTF with Custom Config
```bash
./ConsoleCPP -from model.iges -to model.gltf -config high_quality.conf --tess
```

### 3. Batch Conversion
```bash
# Convert all STEP files to STL
for file in *.step; do
    ./ConsoleCPP -from "$file" -to "${file%.step}.stl" --tess
done
```

### 4. Using Minimal Libraries
Create `minimal.libs`:
```
TKDESTEP
TKDESTL
```

Run conversion:
```bash
./ConsoleCPP -from model.stp -to model.stl -lib minimal.libs --tess
```

### 5. Generate Custom Configuration
```bash
# Create config for specific libraries
./ConsoleCPP -lib custom.libs -dump custom.conf

# Then use it
./ConsoleCPP -from input.step -to output.iges -config custom.conf
```

## Configuration Files

### LIBS File Format
List libraries to load, one per line:
```
TKDESTEP
TKDEIGES
TKDESTL
# Comments are ignored
TKDEGLTF
```

### CONF File Parameters

#### Global Settings
```ini
# Units (1=mm, 2=m, etc.)
global.length.unit : 1
global.angular.unit : 1

# Vendor priority
global.priority.vendor : TKDESTEP TKDEIGES TKDESTL
```

#### STEP Configuration
```ini
# Read settings
provider.STEP.OCC.read.precision.val : 0.0001
provider.STEP.OCC.read.step.product.name : 1
provider.STEP.OCC.read.color : 1

# Write settings
provider.STEP.OCC.write.precision.val : 0.0001
provider.STEP.OCC.write.step.assembly : 2
provider.STEP.OCC.write.color : 1
```

#### STL Configuration
```ini
# ASCII or Binary
provider.STL.OCC.write.stl.mode : 1

# Mesh quality
provider.STL.OCC.read.triangulation : 1
provider.STL.OCC.write.triangulation : 1
```

## Advanced Usage

### Custom Library Paths

#### Linux/macOS
```bash
export LD_LIBRARY_PATH=/custom/lib/path:$LD_LIBRARY_PATH
./ConsoleCPP -from input.stp -to output.stl
```

#### Windows
```cmd
set PATH=C:\custom\lib\path;%PATH%
ConsoleCPP.exe -from input.stp -to output.stl
```

## Integration Examples

### Python Script
```python
import subprocess
import os

def convert_cad(input_file, output_file, tessellate=False):
    cmd = ['./ConsoleCPP', '-from', input_file, '-to', output_file]
    if tessellate:
        cmd.append('--tess')
    
    result = subprocess.run(cmd, capture_output=True, text=True)
    return result.returncode == 0

# Usage
if convert_cad('model.step', 'model.stl', tessellate=True):
    print("Conversion successful!")
```

### Bash Function
```bash
convert_cad() {
    local input="$1"
    local output="$2"
    local options="${3:-}"
    
    ./ConsoleCPP -from "$input" -to "$output" $options
    
    if [ $? -eq 0 ]; then
        echo "✓ Converted: $input → $output"
    else
        echo "✗ Failed: $input"
        return 1
    fi
}

# Usage
convert_cad "part.step" "part.stl" "--tess"
```

### Makefile Integration
```makefile
MODELS = $(wildcard *.step)
OUTPUTS = $(MODELS:.step=.stl)

all: $(OUTPUTS)

%.stl: %.step
	./ConsoleCPP -from $< -to $@ --tess

clean:
	rm -f *.stl
```

## Error Handling

### Common Errors and Solutions

| Error | Cause | Solution |
|-------|-------|----------|
| "Could not open library" | Missing OCCT library | Check library path, install dependencies |
| "Cannot read file" | Unsupported format | Add required library to LIBS file |
| "Tessellation failed" | Invalid geometry | Check model, adjust precision |
| "Write failed" | Permissions/disk space | Check write permissions and disk space |
| "Configuration not found" | Missing CONF file | Use -config to specify path |

### Exit Codes

- `0`: Success
- `1`: Invalid arguments
- `2`: File read error
- `3`: File write error
- `4`: Library load error
- `5`: Configuration error

## Tips and Best Practices

1. **Always use tessellation** for mesh formats (STL, OBJ, PLY)
2. **Test with small files** before batch processing
3. **Keep configurations** for different quality levels
4. **Load only needed libraries** for better performance
5. **Use binary STL** for large models
6. **Check exit codes** in scripts
7. **Validate output** with CAD viewers

## Format-Specific Notes

### STEP Files
- Supports assemblies and colors
- Best for CAD data exchange
- Preserves exact geometry

### STL Files
- Requires tessellation
- No color support
- Best for 3D printing

### glTF Files
- Supports materials and textures
- Best for web visualization
- Requires tessellation

### IGES Files
- Older format, wide support
- Limited assembly support
- Good for surface data

### OBJ Files
- Supports materials and textures
- Common in 3D graphics
- Requires tessellation

### BREP Files
- Boundary representation format
- Supports complex geometries
- Best for CAD data exchange

### XBF Files
- eXtended Binary Format (OpenCASCADE native)
- Supports complex geometries and metadata
- Best for efficient storage and transmission
- Preserves full OCCT model structure
