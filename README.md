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

The core functionality lies in the `call_function` method of the `boa::python_file` class.

The following table shows which types are currently supported for method results and arguments.

| Type             | Result             | Argument           |
| ---------------- |:------------------:|:------------------:|
| `void`           | :heavy_check_mark: | :heavy_check_mark: |
| `std::string`    | :heavy_check_mark: | :x:                |
| `std::wstring`   | :heavy_check_mark: | :x:                |
| `char*`          | :x:                | :heavy_check_mark: |
| `char const*`    | :x:                | :heavy_check_mark: |
| `wchar_t*`       | :x:                | :x:                |
| `wchar_t const*` | :x:                | :x:                |
| `int8_t`         | :x:                | :heavy_check_mark: |
| `int16_t`        | :x:                | :heavy_check_mark: |
| `int32_t`        | :x:                | :heavy_check_mark: |
| `int64_t`        | :x:                | :heavy_check_mark: |
| `float`          | :x:                | :heavy_check_mark: |
| `double`         | :x:                | :heavy_check_mark: |
| `PyObject*`      | :heavy_check_mark: | :heavy_check_mark: |
| `Py_ssize_t`     | :x:                | :grey_question:    |
| `PY_LONG_LONG`   | :x:                | :grey_question:    |
