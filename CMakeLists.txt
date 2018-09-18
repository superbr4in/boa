cmake_minimum_required ( VERSION 3.8 )

find_package ( PythonLibs 3 )

add_library ( boa SHARED
    "source/boa.cpp" )

target_include_directories ( boa PUBLIC
    "include/"
    ${PYTHON_INCLUDE_DIRS} )
target_link_libraries ( boa
    ${PYTHON_LIBRARIES} )
