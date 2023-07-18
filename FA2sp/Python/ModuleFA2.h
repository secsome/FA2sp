#pragma once

#define PY_SSIZE_T_CLEAN
#include <Python.h>

class ModuleFA2
{
public:
    static PyObject* Init();

    static PyObject* message_box(PyObject* self, PyObject* args);
    static PyObject* write_log(PyObject* self, PyObject* args);
    static PyObject* get_current_map_dict(PyObject* self, PyObject* args);

private:
    static PyModuleDef ModuleDef;
    static PyMethodDef MethodsDef[];
};