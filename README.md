# TinyEngine
[![CI Release](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/release.yml)
[![Windows](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml/badge.svg)](https://github.com/kaijurgeit/TinyEngine/actions/workflows/windows.yml)

Tiny Engine is a small piece of software to create interactive applications for Windows based on OpenGL.

## Getting Started

This repository is written in C++17 and it was tested using CMake 3.11 and Visual Studio 2022 on Windows.

### Download and Build the Repository

Execute the following lines in your terminal to download and build the repository:

```
git clone https://github.com/kaijurgeit/TinyEngine.git
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build
```

If you'd like to build tests;
```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DBuildTests=ON
```