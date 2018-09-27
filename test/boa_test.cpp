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

TEST_CASE("call_method<std::wstring> | 1 argument")
{
    auto const test_file = get_sibling_python_file(test_file_name_argument_types);

    std::string const method_name("get_types");
    CHECK(test_file.call_method<std::wstring, char const*>   (method_name, "\0") == L"<class 'str'>");
    CHECK(test_file.call_method<std::wstring, int8_t>        (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint8_t>       (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int16_t>       (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint16_t>      (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int32_t>       (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint32_t>      (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int64_t>       (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, uint64_t>      (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, char>          (method_name, '\0') == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned char> (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, short>         (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned short>(method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, int>           (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned>      (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, long>          (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, unsigned long> (method_name,    0) == L"<class 'int'>");
    CHECK(test_file.call_method<std::wstring, float>         (method_name,    0) == L"<class 'float'>");
    CHECK(test_file.call_method<std::wstring, double>        (method_name,    0) == L"<class 'float'>");
}
