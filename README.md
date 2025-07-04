## How to build the project

### Linux or WSL (prefered dev env)

Requirements:

- CMake version >=3.15
- gcc with C23 support
- Make or ninja

If using make:

```bash
mkdir build/
cd build/
cmake ..
make
# You will find the executable in  build/src/unnamed_project
```

Feeling like a Ninja ?

```bash
cd build/
cmake -G Ninja ..
ninja
# You will find the executable in  build/src/unnamed_project
```

### Windows

If using codeblocks:

If using VSCode:
