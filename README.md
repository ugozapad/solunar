# Solunar Engine

An open-source 3D graphics engine created to learn how games and engines works

## Features

- Custom compile-time reflection system
- Crossplatform support
- OpenGL 3.3 Forward renderer (which use direct state access if enabled)
- Entity Component node-based world

## Requirements

- C++ 14 compiler
- CMake 3.16 or higher

## Building

- Get the repository

  ```shell
  git clone https://github.com/ugozapad/solunar.git
  ```

- Generate projects or build scripts

  ```shell
  cmake -B build -G "Visual Studio 17 2022"
  ```

- Build using target build system

  ```shell
  msbuild build\solunar.sln
  ```

## License

This project licensed under terms of the __MIT__ license. See [this](./LICENSE) file for details
