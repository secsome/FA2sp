#include "PythonManager.h"

#include <fstream>

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "ModuleFA2.h"

bool PythonManager::IsInitialized;

bool PythonManager::Init()
{
    PyImport_AppendInittab("fa2", &ModuleFA2::Init);
    Py_Initialize();
    IsInitialized = Py_IsInitialized() != 0;
    return IsInitialized;
}

void PythonManager::Release()
{
    Py_Finalize();
}

bool PythonManager::Is_Initialized()
{
    return IsInitialized;
}

bool PythonManager::Execute(const char* filepath)
{
    std::ifstream fin;
    fin.open(filepath, fin.in | fin.binary);
    if (!fin.is_open())
        return false;
    fin.seekg(0, fin.end);
    const auto sz = fin.tellg();
    fin.seekg(0, fin.beg);
    std::string buffer;
    buffer.resize(sz);
    fin.read(buffer.data(), sz);
    fin.close();

    PyRun_SimpleString(buffer.c_str());

    return true;
}
