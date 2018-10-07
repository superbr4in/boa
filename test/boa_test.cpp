#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <boa/boa.h>

#include <libgen.h>

using namespace boa;

constexpr auto FUNC_GET_TYPES      = "get_types";
constexpr auto FUNC_PROCEDURE      = "procedure";
constexpr auto FUNC_PROCEDURE_ARGS = "procedure_args";
constexpr auto FUNC_REFLECT        = "reflect";
constexpr auto FUNC_RESULT_BYTES   = "result_bytes";

python_file get_test_file()
{
    std::string const path_cpp(__FILE__);

    std::stringstream ss_path_py;
    ss_path_py << path_cpp.substr(0, path_cpp.find_last_of('.')) << ".py";

    return python_file(ss_path_py.str());
}

TEST_CASE("call_function<void>")
{
    CHECK_NOTHROW(get_test_file().call_function<void>(FUNC_PROCEDURE));
}

TEST_CASE("call_function<void, T>")
{
    CHECK_NOTHROW(get_test_file().call_function<void, int>(FUNC_PROCEDURE_ARGS, 0));
}

TEST_CASE("call_function<std::string>")
{
    CHECK(get_test_file().call_function<std::string>(FUNC_RESULT_BYTES) == "");
}

TEST_CASE("call_function<std::wstring>")
{
    std::wstring const ws = L"test";
    CHECK(get_test_file().call_function<std::wstring, wchar_t const*>(FUNC_REFLECT, ws.c_str()) == ws);
}

TEST_CASE("call_function<Integral>")
{
    auto const t_file = get_test_file();
    std::string const f = FUNC_REFLECT;

    CHECK(t_file.call_function< int8_t,   int8_t> (f,  INT8_MAX)  ==  INT8_MAX);
    CHECK(t_file.call_function< int16_t,  int16_t>(f,  INT16_MAX) ==  INT16_MAX);
    CHECK(t_file.call_function< int32_t,  int32_t>(f,  INT32_MAX) ==  INT32_MAX);
    CHECK(t_file.call_function< int64_t,  int64_t>(f,  INT64_MAX) ==  INT64_MAX);
    CHECK(t_file.call_function<uint8_t,  uint8_t> (f, UINT8_MAX)  == UINT8_MAX);
    CHECK(t_file.call_function<uint16_t, uint16_t>(f, UINT16_MAX) == UINT16_MAX);
    CHECK(t_file.call_function<uint32_t, uint32_t>(f, UINT32_MAX) == UINT32_MAX);
    CHECK(t_file.call_function<uint64_t, uint64_t>(f, UINT64_MAX) == UINT64_MAX);
}

TEST_CASE("call_function<std::wstring, PyObject*>")
{
    auto const result =
        get_test_file().call_function<std::wstring, PyObject*>(
            FUNC_GET_TYPES,
            PyLong_FromLong(0));
    CHECK(result == L"<class 'int'>");
}

TEST_CASE("call_function<PyObject*, PyObject*>")
{
    std::wstring const expected(L"<class 'int'>");

    std::wstring actual(expected.size(), '\0');
    PyUnicode_AsWideChar(
        get_test_file().call_function<PyObject*, PyObject*>(
            FUNC_GET_TYPES,
            PyLong_FromLong(0)),
        actual.data(),
        actual.size());

    CHECK(actual == expected);
}

TEST_CASE("call_function<std::wstring, T>")
{
    auto const t_file = get_test_file();
    std::string const f = FUNC_GET_TYPES;

    CHECK(t_file.call_function<std::wstring, char*>(f, const_cast<char*>("x")) == L"<class 'str'>");

    CHECK(t_file.call_function<std::wstring, char const*>(f, "x") == L"<class 'str'>");

    CHECK(t_file.call_function<std::wstring, int8_t>  (f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, int16_t> (f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, int32_t> (f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, int64_t> (f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, uint8_t> (f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, uint16_t>(f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, uint32_t>(f, 0) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, uint64_t>(f, 0) == L"<class 'int'>");

    CHECK(t_file.call_function<std::wstring, char>              (f, '\0') == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, short>             (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, int>               (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, long>              (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, long long>         (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, unsigned char>     (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, unsigned short>    (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, unsigned int>      (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, unsigned long>     (f,   0 ) == L"<class 'int'>");
    CHECK(t_file.call_function<std::wstring, unsigned long long>(f,   0 ) == L"<class 'int'>");

    CHECK(t_file.call_function<std::wstring, float> (f, 0) == L"<class 'float'>");
    CHECK(t_file.call_function<std::wstring, double>(f, 0) == L"<class 'float'>");
}

TEST_CASE("call_function<std::wstring, TArgs...>")
{
    auto const actual =
        get_test_file().call_function
            <std::wstring, char const*, char, int, double, char const*, char const*>
            (FUNC_GET_TYPES, "ab", 'c', 24, 6.3, "x", "y");
    CHECK(actual == L"<class 'str'><class 'int'><class 'int'><class 'float'><class 'str'><class 'str'>");
}

TEST_CASE("THROW: Invalid function")
{
    CHECK_THROWS(get_test_file().call_function<std::wstring>("invalid"));
}

TEST_CASE("THROW: Function wrong arguments")
{
    CHECK_THROWS(get_test_file().call_function<void, int>(FUNC_PROCEDURE, 0));
}

TEST_CASE("THROW: Function wrong return type")
{
    CHECK_THROWS(get_test_file().call_function<std::wstring>(FUNC_PROCEDURE));
}
