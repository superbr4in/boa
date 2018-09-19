#pragma once

#include <string>

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
        TResult call_method(std::string const& name, TArgs&&... arguments) const;
    };
}
