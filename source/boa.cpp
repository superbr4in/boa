#include <sstream>

#include <boa/boa.h>

int boa::python_file::init_count_ = 0;

boa::python_file::python_file(std::string const& location)
{
    std::stringstream ss_module_name;
    ss_module_name << "module" << init_count_;

    if (init_count_++ == 0)
        Py_Initialize();

    std::stringstream ss_import;
    ss_import << "import imp" << std::endl;
    ss_import << "imp.load_source('" << ss_module_name.str() << "', '" << location << "')" << std::endl;
    PyRun_SimpleString(ss_import.str().c_str());

    module_ = PyImport_ImportModule(ss_module_name.str().c_str());
}
boa::python_file::~python_file()
{
    if (--init_count_ == 0)
        Py_Finalize();
}
