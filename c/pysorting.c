#define PY_SSIZE_T_CLEAN
#include <Python.h>

#define PDMERGE_TYPE PyObject*
#define PDMERGE_COMPARE(a, b) (PyObject_RichCompareBool((a), (b), Py_LT) > 0 ? -1 : (PyObject_RichCompareBool((a), (b), Py_GT) > 0 ? 1 : 0))
#include "pdmerge.h"

#define DOUBLE_INSERTION_TYPE PyObject*
#define DOUBLE_INSERTION_COMPARE(a, b) (PyObject_RichCompareBool((a), (b), Py_LT) > 0 ? -1 : (PyObject_RichCompareBool((a), (b), Py_GT) > 0 ? 1 : 0))
#include "double_insertion.h"


#define BAD_TYPE_ERROR {PyErr_SetString(PyExc_TypeError, "\"list_to_sort\" must be a list"); return NULL;}

#define SORT_FUNCTION(args, sortFunc) { \
    const PyListObject* list; \
    if (!PyArg_ParseTuple(args, "O", &list)) \
        return NULL; \
    if (!PyList_Check(list)) \
        BAD_TYPE_ERROR; \
    sortFunc(list->ob_item, PyList_Size((PyObject*)list)); \
    Py_RETURN_NONE; \
}

static PyObject* pysorting_pdmerge(PyObject* self, PyObject* args) {
    SORT_FUNCTION(args, pdmerge);
}

static PyObject* pysorting_double_insertion(PyObject* self, PyObject* args) {
    SORT_FUNCTION(args, double_insertion);
}


static PyMethodDef PysortingMethods[] = {
    {"pdmerge", pysorting_pdmerge, METH_VARARGS,
     "pdmerge(list_to_sort: list)\n--\n\nSort the list with pdmerge"},
    {"double_insertion", pysorting_double_insertion, METH_VARARGS,
     "double_insertion(list_to_sort: list)\n--\n\nSort the list with double insertion"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pysortingmodule = {
    PyModuleDef_HEAD_INIT,
    "pysorting",
    NULL,
    -1,
    PysortingMethods
};

PyMODINIT_FUNC PyInit_pysorting() {
    return PyModule_Create(&pysortingmodule);
}
