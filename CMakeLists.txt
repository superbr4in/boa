cmake_minimum_required ( VERSION 3.8 )

find_package ( PythonLibs 3 )

include_directories (
    ${PYTHON_INCLUDE_DIRS} )

add_library ( boa SHARED
    "include/boa/boa.h" )
set_target_properties ( boa PROPERTIES LINKER_LANGUAGE CXX )

target_link_libraries ( boa
    ${PYTHON_LIBRARIES} )

