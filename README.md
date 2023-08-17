# TinyEngine
[![CI Release](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml)
[![Windows](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml)

Tiny Engine is a small piece of software to create interactive applications for Windows based on OpenGL. You can follow the progress of the project here: [TinyEngine Backlog](https://github.com/users/kaijurgeit/projects/5).

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

If you'd like to modify and build the *App* together with *TinyEngine* in **Rider**, you have to disable "Use ReSharper Build" under  *Settings → Build, Execution, Deployment → Toolset*. If you don't do this, the dll will not be rebuild.