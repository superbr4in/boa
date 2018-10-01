#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <boa/boa.h>

#include <libgen.h>

using namespace boa;

constexpr auto test_file_name_argument_types = "boa_test_argument_types.py";

python_file get_sibling_python_file(std::string const& file_name)
{
    std::stringstream ss_path;
    ss_path << dirname(const_cast<char*>(std::string(__FILE__).c_str())) << "/" << file_name;

    return python_file(ss_path.str());
}

TEST_CASE("call_function<std::wstring, PyObject*>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);
    std::string const function_name("get_types");

    CHECK(test_file.call_function<std::wstring, PyObject*>(function_name, PyLong_FromLong(0)) == L"<class 'int'>");
}

TEST_CASE("call_function<PyObject*, PyObject*>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);
    std::string const function_name("get_types");

    std::wstring const expected(L"<class 'int'>");

    std::wstring actual(expected.size(), '\0');
    PyUnicode_AsWideChar(
        test_file.call_function<PyObject*, PyObject*>(function_name, PyLong_FromLong(0)),
        actual.data(),
        actual.size());

    CHECK(actual == expected);
}

TEST_CASE("call_function<std::wstring, T>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);
    std::string const function_name("get_types");

    CHECK(test_file.call_function<std::wstring, char*>(function_name, const_cast<char*>("x")) == L"<class 'str'>");

    CHECK(test_file.call_function<std::wstring, char const*>(function_name, "x") == L"<class 'str'>");

    CHECK(test_file.call_function<std::wstring, int8_t>  (function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int16_t> (function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int32_t> (function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int64_t> (function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint8_t> (function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint16_t>(function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint32_t>(function_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint64_t>(function_name, 0) == L"<class 'int'>");

    CHECK(test_file.call_function<std::wstring, char>              (function_name, '\0') == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, short>             (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int>               (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, long>              (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, long long>         (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned char>     (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned short>    (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned int>      (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned long>     (function_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned long long>(function_name,   0 ) == L"<class 'int'>");

    CHECK(test_file.call_function<std::wstring, float> (function_name, 0) == L"<class 'float'>");
    CHECK(test_file.call_function<std::wstring, double>(function_name, 0) == L"<class 'float'>");
}

TEST_CASE("call_function<std::wstring, TArgs...>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);
    std::string const function_name("get_types");

    auto const actual =
        test_file.call_function
            <std::wstring, char const*, char, int, double, char const*, char const*>
            (function_name, "ab", 'c', 24, 6.3, "x", "y");
    CHECK(actual == L"<class 'str'><class 'int'><class 'int'><class 'float'><class 'str'><class 'str'>");
}
