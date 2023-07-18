#include "ModuleFA2.h"

#include "../FA2sp.h"

#include <CMapData.h>
#include <CINI.h>

PyModuleDef ModuleFA2::ModuleDef
{
    PyModuleDef_HEAD_INIT, "fa2", "FA2sp library which provides useful interface to interface with FA2.", -1, MethodsDef, nullptr, nullptr, nullptr, nullptr
};

PyMethodDef ModuleFA2::MethodsDef[] =
{
    {"message_box", ModuleFA2::message_box, METH_VARARGS, "Show message box."},
    {"write_log", ModuleFA2::write_log, METH_VARARGS, "Write to log."},
    {"get_current_map_dict", ModuleFA2::get_current_map_dict, METH_NOARGS, "Get current map dict."},
    {"set_current_map_dict", ModuleFA2::set_current_map_dict, METH_VARARGS, "Set current map dict."},
    {"merge_current_map_dict", ModuleFA2::merge_current_map_dict, METH_VARARGS, "Merge current map dict."},
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

    const auto ret = ::MessageBox(NULL, message, title, mask);

    return PyLong_FromLong(ret);
}

PyObject* ModuleFA2::write_log(PyObject* self, PyObject* args)
{
    const char* log;
    if (!PyArg_ParseTuple(args, "s", &log))
        return nullptr;

    Logger::Raw(log);

    return Py_None;
}

PyObject* ModuleFA2::get_current_map_dict(PyObject* self, PyObject* Py_UNUSED(args))
{
    auto& ini = CMapData::Instance->INI.Dict;
    auto ret = PyDict_New();

    for (auto& [section_name, section] : ini)
    {
        auto section_dict = PyDict_New();
        for (auto& [key, value] : section.GetEntities())
            PyDict_SetItemString(section_dict, key, PyUnicode_FromString(value));
        PyDict_SetItemString(ret, section_name, section_dict);
    }

    return ret;
}

PyObject* ModuleFA2::set_current_map_dict(PyObject* self, PyObject* args)
{
    PyObject* dict;
    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict))
        return nullptr;

    auto& ini = CMapData::Instance->INI;
    ini.ClearAndLoad(nullptr); // pass nullptr to just clear it
    
    auto section_names = PyDict_Keys(dict);
    const auto section_count = PyList_Size(section_names);
    for (auto i = 0; i < section_count; ++i)
    {
        auto section_name = PyList_GetItem(section_names, i);
        auto pSection = ini.AddSection(PyUnicode_AsUTF8(section_name));
        auto section = PyDict_GetItem(dict, section_name);
        auto keys = PyDict_Keys(section);
        const auto key_count = PyList_Size(keys);
        for (auto j = 0; j < key_count; ++j)
        {
            auto key = PyList_GetItem(keys, j);
            auto value = PyDict_GetItem(section, key);
            ini.WriteString(pSection, PyUnicode_AsUTF8(key), PyUnicode_AsUTF8(value));
        }
    }

    return Py_None;
}

PyObject* ModuleFA2::merge_current_map_dict(PyObject* self, PyObject* args)
{
    PyObject* dict;
    if (!PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict))
        return nullptr;

    auto& ini = CMapData::Instance->INI;
    auto section_names = PyDict_Keys(dict);
    const auto section_count = PyList_Size(section_names);
    for (auto i = 0; i < section_count; ++i)
    {
        auto section_name = PyList_GetItem(section_names, i);
        auto pSection = ini.AddOrGetSection(PyUnicode_AsUTF8(section_name));
        auto section = PyDict_GetItem(dict, section_name);
        auto keys = PyDict_Keys(section);
        const auto key_count = PyList_Size(keys);
        for (auto j = 0; j < key_count; ++j)
        {
            auto key = PyList_GetItem(keys, j);
            auto value = PyDict_GetItem(section, key);
            ini.WriteString(pSection, PyUnicode_AsUTF8(key), PyUnicode_AsUTF8(value));
        }
    }

    return Py_None;
}