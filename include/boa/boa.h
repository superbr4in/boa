#pragma once

#include <sstream>
#include <string>

#include <Python.h>

inline std::wstring py_call_method(std::string const& file_path, std::string const& method_name, std::string const& argument)
{
    constexpr auto module_name = "module";

    std::stringstream ss_import;
    ss_import << "import imp" << std::endl;
    ss_import << "imp.load_source('" << module_name << "', '" << file_path << "')" << std::endl;

    Py_Initialize();

    PyRun_SimpleString(ss_import.str().c_str());

    auto* const py_module = PyImport_ImportModule(module_name);
    auto* const py_result = PyObject_CallMethod(py_module, method_name.c_str(), "(s)", argument.c_str());

    std::wstring const result = PyUnicode_AsWideCharString(py_result, nullptr);

    Py_Finalize();

    return result;
}

