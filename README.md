# OpenGL Project Template

Simple C++ OpenGL template using:

* C++17
* CMake
* GLFW 3.5.1
* GLAD 2.0.8
* OpenGL 4.6 Core
* MSVC

## Requirements

Install:

1. **Visual Studio** with MSVC / Desktop development with C++
2. **CMake**
3. **Git**
4. **Python**
5. **Jinja2**

Install Jinja2:

```bash
python -m pip install Jinja2
```

## Setup

Clone the project, then run:

```bash
make init
```

This will configure CMake and download GLFW and GLAD automatically.

## Build & Run

Build:

```bash
make build
```

Run:

```bash
make run
```

Or rebuild from scratch:

```bash
make rebuild
```

Clean build files:

```bash
make clean
```

## Make Commands

| Command        | Description       |
| -------------- | ----------------- |
| `make init`    | Initialize CMake  |
| `make build`   | Build project     |
| `make rebuild` | Clean and rebuild |
| `make run`     | Run application   |
| `make clean`   | Clean build       |

## Project Structure

```text
OpenGLProject/
├── CMakeLists.txt
├── Makefile
├── README.md
├── include/
├── src/
│   └── main.cpp
└── build/
```

`build/` is generated automatically by CMake.
