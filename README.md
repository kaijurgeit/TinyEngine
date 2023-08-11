# TinyEngine
[![CI Release](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml)
[![Windows](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml)

Tiny Engine is a small piece of software to create interactive applications for Windows based on OpenGL.

## Getting Started

This repository is written in C++17 and it was tested using CMake 3.11 and Visual Studio 2022 on Windows.

### Download and Build the Repository

Download the repository:

```
git clone https://github.com/kaijurgeit/TinyEngine.git
```

Build the repository. Add `--config <build_type>` to specify a Debug or Release <build_type>:

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build
```

Build with tests enabled:

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DBuildTests=ON
cmake --build build
```

Run tests:
```
cd build; ctest -j 10 -C <build_type>
```

Run Application:
```
./build/application/<build_type>/Application.exe
```