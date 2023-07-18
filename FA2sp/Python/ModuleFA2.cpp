#include "ModuleFA2.h"

#include "../FA2sp.h"

PyModuleDef ModuleFA2::ModuleDef
{
    PyModuleDef_HEAD_INIT, "fa2", "FA2sp library which provides useful interface to interface with FA2.", -1, MethodsDef, nullptr, nullptr, nullptr, nullptr
};

PyMethodDef ModuleFA2::MethodsDef[] =
{
    {"message_box", ModuleFA2::message_box, METH_VARARGS, "Show message box."},
    {nullptr, nullptr, 0, nullptr}
};

PyObject* ModuleFA2::Init()
{
    return PyModule_Create(&ModuleDef);
}

PyObject* ModuleFA2::message_box(PyObject* self, PyObject* args)
{
    const char* message;
    const char* title;
    unsigned int mask;
    if (!PyArg_ParseTuple(args, "ssl", &message, &title, &mask))
        return nullptr;

    ::MessageBox(NULL, message, title, mask);

    return Py_None;
}
