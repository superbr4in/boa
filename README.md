# Boa

## Dependencies

This project depends on the [Python/C API (v3.6)](https://docs.python.org/3.6/c-api/index.html). Use the package manager of your Linux distribution to install the necessary files (e.g. `apt install python3-dev`).

The tests rely on the [Catch2](https://github.com/catchorg/Catch2) test framework.

Use [cmake](https://cmake.org/) to create a shared library from the source code:
```
mkdir build
cd build/
cmake ..
```

## Manual

| Type           | Result       | Parameter          |
| -------------- |:------------:|:------------------:|
| `std::wstring` | ❌ | :heavy_check_mark: |
