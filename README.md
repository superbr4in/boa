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

The core functionality lies in the `call_method` function of the `boa::python_file` class.

The following table shows which types are currently supported for method results and arguments.

| Type | Result | Argument |
| --- |:---:|:---:|
| `std::string` | ❌ | ❌ |
| `std::wstring` | ✔️ | ❌ |
| `char*` | ❌ | ✔️ |
| `char const*` | ❌ | ✔️ |
| `wchar_t*` | ❌ | ❌ |
| `wchar_t const*` | ❌ | ❌ |
| `int8_t` | ❌ | ✔️ |
| `int16_t` | ❌ | ✔️ |
| `int32_t` | ❌ | ✔️ |
| `int64_t` | ❌ | ✔️ |
| `float` | ❌ | ✔️ |
| `double` | ❌ | ✔️ |
| `PyObject*` | ✔️ | ✔️ |
| `Py_ssize_t` | ❌ | ❔ |
| `PY_LONG_LONG` | ❌ | ❔ |
