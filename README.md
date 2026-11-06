# Theatre management

[![C++ CI](https://github.com/PADOALEX/Theatre/actions/workflows/ci.yml/badge.svg)](https://github.com/PADOALEX/Theatre/actions/workflows/ci.yml)

A historical C++ console application using linked lists and text-file storage. Each ticket consumes one seat. Loading rejects oversized actor counts before accessing the fixed actor array.

## Build and run

Install Visual Studio 2022 or later with the Desktop development with C++ workload, CMake 3.20+ and Python 3.12+ for regression tests. Run from the repository root on Windows:

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\app.exe
```

The original Visual Studio solution remains available. The CMake executable is named `app`; executable location depends on the selected generator. Automated tests use temporary directories for file-based scenarios and verify behavior with bounded subprocess timeouts.

## Scope

This is a single-user academic program, without a database, authentication or deployment. It uses Windows/MSVC secure CRT functions. Text-file storage is a trusted local exercise format; interrupted writes and multiple processes are not supported. The maintained .NET successor is [PADO TheatreBook](https://github.com/PADOALEX/PADO-TheatreBook).
