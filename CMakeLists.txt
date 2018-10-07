cmake_minimum_required ( VERSION 3.8 )

set ( CMAKE_CXX_STANDARD 17 )

set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "bin/" )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/" )

find_package ( PythonLibs 3 )

add_library ( boa SHARED
    "source/boa.cpp" )

target_include_directories ( boa PUBLIC
    "include/"
    ${PYTHON_INCLUDE_DIRS} )
target_link_libraries ( boa
    ${PYTHON_LIBRARIES} )

add_executable ( boa_test
    "test/boa_test.cpp" )

target_link_libraries ( boa_test
    boa )
