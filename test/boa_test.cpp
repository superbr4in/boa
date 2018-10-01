#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <boa/boa.h>

#include <libgen.h>

using namespace boa;

constexpr auto test_file_name_argument_types = "boa_test_argument_types.py";
constexpr auto test_file_name_procedure = "boa_test_procedure.py";

constexpr auto test_function_name_get_types = "get_types";

constexpr auto test_function_name_procedure = "procedure";
constexpr auto test_function_name_procedure_args = "procedure_args";

python_file get_sibling_python_file(std::string const& file_name)
{
    std::stringstream ss_path;
    ss_path << dirname(const_cast<char*>(std::string(__FILE__).c_str())) << "/" << file_name;

    return python_file(ss_path.str());
}

TEST_CASE("call_function<void>")
{
    auto const test_file = get_sibling_python_file(test_file_name_procedure);
    std::string const function_name(test_function_name_procedure);

    CHECK_NOTHROW(test_file.call_function<void>(function_name));
}

TEST_CASE("call_function<void, T>")
{
    auto const test_file = get_sibling_python_file(test_file_name_procedure);
    std::string const function_name(test_function_name_procedure_args);

    CHECK_NOTHROW(test_file.call_function<void, int>(function_name, 5));
}

TEST_CASE("call_function<std::wstring>")
{
    auto const result =
        get_sibling_python_file(test_file_name_argument_types).call_function<std::wstring>(
            test_function_name_get_types);
    CHECK(result == L"");
}

TEST_CASE("call_function<std::wstring, PyObject*>")
{
    auto const result =
        get_sibling_python_file(test_file_name_argument_types).call_function<std::wstring, PyObject*>(
            test_function_name_get_types,
            PyLong_FromLong(0));
    CHECK(result == L"<class 'int'>");
}

TEST_CASE("call_function<PyObject*, PyObject*>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::wstring const expected(L"<class 'int'>");

    std::wstring actual(expected.size(), '\0');
    PyUnicode_AsWideChar(
        test_file.call_function<PyObject*, PyObject*>(
            test_function_name_get_types,
            PyLong_FromLong(0)),
        actual.data(),
        actual.size());

    CHECK(actual == expected);
}

TEST_CASE("call_function<std::wstring, T>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);
    std::string const fn(test_function_name_get_types);

    CHECK(test_file.call_function<std::wstring, char*>(fn, const_cast<char*>("x")) == L"<class 'str'>");

    CHECK(test_file.call_function<std::wstring, char const*>(fn, "x") == L"<class 'str'>");

    CHECK(test_file.call_function<std::wstring, int8_t>  (fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int16_t> (fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int32_t> (fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int64_t> (fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint8_t> (fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint16_t>(fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint32_t>(fn, 0) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, uint64_t>(fn, 0) == L"<class 'int'>");

    CHECK(test_file.call_function<std::wstring, char>              (fn, '\0') == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, short>             (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, int>               (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, long>              (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, long long>         (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned char>     (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned short>    (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned int>      (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned long>     (fn,   0 ) == L"<class 'int'>");
    CHECK(test_file.call_function<std::wstring, unsigned long long>(fn,   0 ) == L"<class 'int'>");

    CHECK(test_file.call_function<std::wstring, float> (fn, 0) == L"<class 'float'>");
    CHECK(test_file.call_function<std::wstring, double>(fn, 0) == L"<class 'float'>");
}

TEST_CASE("call_function<std::wstring, TArgs...>")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    auto const actual =
        test_file.call_function
            <std::wstring, char const*, char, int, double, char const*, char const*>
            (test_function_name_get_types, "ab", 'c', 24, 6.3, "x", "y");
    CHECK(actual == L"<class 'str'><class 'int'><class 'int'><class 'float'><class 'str'><class 'str'>");
}

TEST_CASE("THROW: Invalid function")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    CHECK_THROWS(test_file.call_function<std::wstring>("invalid"));
}

TEST_CASE("THROW: Function wrong arguments")
{
    auto const test_file = get_sibling_python_file(test_file_name_procedure);

    CHECK_THROWS(test_file.call_function<void, int>(test_function_name_procedure, 5));
}

TEST_CASE("THROW: Function wrong return type")
{
    auto const test_file = get_sibling_python_file(test_file_name_procedure);

    CHECK_THROWS(test_file.call_function<std::wstring>(test_function_name_procedure));
}
