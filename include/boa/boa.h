#pragma once

#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>

#include <Python.h>

namespace boa
{
    class python_file
    {
        static int init_count_;

        PyObject* module_;

    public:

        explicit python_file(std::string const& location);
        ~python_file();

        template <typename TResult, typename... TArgs>
        TResult call_function(std::string const& name, TArgs&&... arguments) const;

    private:

        template <typename... Ts>
        static std::string get_format();

        template <typename T, typename... Ts>
        static void get_inner_format(std::stringstream& ss_format);

        template <typename T>
        static T convert(PyObject* py_object);
    };
}

std::mutex call_mutex, convert_mutex;

template <typename TResult, typename... TArgs>
TResult boa::python_file::call_function(std::string const& name, TArgs&&... arguments) const
{
    std::optional<std::string> format;

    if constexpr (sizeof...(TArgs) > 0)
        format = get_format<TArgs...>();

    call_mutex.lock();

    auto* py_result =
        PyObject_CallMethod(
            module_,
            name.c_str(),
            format ? format->c_str() : nullptr,
            arguments...);

    call_mutex.unlock();

    if (py_result == nullptr)
        throw std::runtime_error("Failed to call the specified python method.");

    if constexpr (!std::is_same_v<TResult, void>)
    {
        convert_mutex.lock();

        auto const converted_result = convert<TResult>(py_result);

        convert_mutex.unlock();

        return converted_result;
    }
}

template <typename... Ts>
std::string boa::python_file::get_format()
{
    std::stringstream ss_format;

    ss_format << "(";

    get_inner_format<Ts...>(ss_format);

    ss_format << ")";

    return ss_format.str();
}

template <typename T, typename... Ts>
void boa::python_file::get_inner_format(std::stringstream& ss_format)
{
    char format_char;

    if      constexpr (std::is_same_v<T, char*> || std::is_same_v<T, char const*>)
        format_char = 's';
    else if constexpr (std::is_same_v<T, float>)
        format_char = 'f';
    else if constexpr (std::is_same_v<T, double>)
        format_char = 'd';
    else if constexpr (std::is_same_v<T, PY_LONG_LONG>)
        format_char = 'L';
    else if constexpr (std::is_same_v<T, unsigned PY_LONG_LONG>)
        format_char = 'K';
    else if constexpr (std::is_same_v<T, Py_ssize_t>)
        format_char = 'n';
    else if constexpr (std::is_same_v<T, PyObject*>)
        format_char = 'O';
    else if constexpr (std::is_integral_v<T>)
    {
        if      constexpr (sizeof(T) == sizeof(char))
            format_char = 'b';
        else if constexpr (sizeof(T) == sizeof(int))
            format_char = 'i';
        else if constexpr (sizeof(T) == sizeof(short))
            format_char = 'h';
        else if constexpr (sizeof(T) == sizeof(long))
            format_char = 'l';
        else if constexpr (sizeof(T) == sizeof(long long))
            format_char = 'L';
    }

    if (format_char == '\0')
        throw std::runtime_error("No format character available for this type.");

    ss_format << format_char;

    if constexpr (sizeof...(Ts) > 0)
    {
        ss_format << ", ";
        get_inner_format<Ts...>(ss_format);
    }
}

template <typename T>
T boa::python_file::convert(PyObject* const py_object)
{
    if constexpr (std::is_same_v<T, PyObject*>)
        return py_object;

    if constexpr (std::is_same_v<T, std::string>)
        return std::string(PyBytes_AsString(py_object));

    if constexpr (std::is_same_v<T, std::wstring>)
    {
        auto* const raw_result = PyUnicode_AsWideCharString(py_object, nullptr);

        std::wstring const result(raw_result);

        PyMem_Free(raw_result);
        return result;
    }

    throw std::runtime_error("Type not convertible from python object.");
}
