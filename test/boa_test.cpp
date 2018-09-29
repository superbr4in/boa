#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <boa/boa.h>

#include <libgen.h>

using namespace boa;

constexpr auto test_file_name_argument_types = "boa_test_argument_types.py";

python_file get_sibling_python_file(std::string file_name)
{
    std::stringstream ss_path;
    ss_path << dirname(const_cast<char*>(std::string(__FILE__).c_str())) << "/" << file_name;

    return python_file(ss_path.str());
}

TEST_CASE("call_method<std::wstring, PyObject*>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::string const method_name("get_types");

    CHECK(test_file.call_method<std::wstring, PyObject*>(method_name, PyLong_FromLong(0)) == L"<class 'int'>");
}

TEST_CASE("call_method<PyObject*, PyObject*>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::string const method_name("get_types");

    std::wstring const expected(L"<class 'int'>");

    std::wstring actual(expected.size(), '\0');
    PyUnicode_AsWideChar(
        test_file.call_method<PyObject*, PyObject*>(method_name, PyLong_FromLong(0)),
        actual.data(),
        actual.size());

    CHECK(actual == expected);
}

TEST_CASE("call_method<std::wstring, T>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::string const method_name("get_types");

    CHECK(test_file.call_method<std::wstring, char*>      (method_name, const_cast<char*>("x")) == L"<class 'str'>");
    CHECK(test_file.call_method<std::wstring, char const*>(method_name,                   "x" ) == L"<class 'str'>");

    CHECK(test_file.call_method<std::wstring, int8_t>  (method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int16_t> (method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int32_t> (method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int64_t> (method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint8_t> (method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint16_t>(method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint32_t>(method_name, 0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint64_t>(method_name, 0) == L"<class 'int'>");

    CHECK(test_file.call_method<std::wstring, char>              (method_name, '\0') == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, short>             (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int>               (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, long>              (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, long long>         (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned char>     (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned short>    (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned int>      (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned long>     (method_name,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned long long>(method_name,   0 ) == L"<class 'int'>");

    CHECK(test_file.call_method<std::wstring, float> (method_name, 0) == L"<class 'float'>");
    CHECK(test_file.call_method<std::wstring, double>(method_name, 0) == L"<class 'float'>");
}

TEST_CASE("call_method<std::wstring, TArgs...>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::string const method_name("get_types");

    auto const actual =
        test_file.call_method
            <std::wstring, char const*, char, int, double, char const*, char const*>
            (method_name, "ab", 'c', 24, 6.3, "x", "y");
    CHECK(actual == L"<class 'str'><class 'int'><class 'int'><class 'float'><class 'str'><class 'str'>");
}
