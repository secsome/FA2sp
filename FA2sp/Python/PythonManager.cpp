#include "PythonManager.h"

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
    PyObject* obj = Py_BuildValue("s", filepath);
    FILE* fp = _Py_fopen_obj(obj, "rb");
    if (fp == nullptr)
        return false;
    PyRun_SimpleFile(fp, filepath);
    fclose(fp);
    return true;
}
