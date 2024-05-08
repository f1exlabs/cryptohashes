#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "flex.h"

static PyObject *flex_hash_py(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);
#if PY_MAJOR_VERSION >= 3
    flex_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    flex_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef cryptohashesMethods[] = {
    { "flex_hash", flex_hash_py, METH_VARARGS, "Returns the proof of work hash using flex" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef cryptohashesModule = {
    PyModuleDef_HEAD_INIT,
    "cryptohashes",
    "...",
    -1,
    cryptohashesMethods
};

PyMODINIT_FUNC PyInit_cryptohashes(void) {
    return PyModule_Create(&cryptohashesModule);
}

#else

PyMODINIT_FUNC initcryptohashes(void) {
    (void) Py_InitModule("cryptohashes", cryptohashesMethods);
}
#endif
