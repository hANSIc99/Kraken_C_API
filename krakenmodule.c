#include <Python.h>
#include "kraken_api.h"

typedef struct {
	/* makro that brings in the standard python object fields */	
	PyObject_HEAD
	/* Type-specific fields go here. */
	char* sec_key;
	char* api_key;

	PyObject *first;
	PyObject *last;

	int number;

	struct kraken_api *kr_api;
} Kraken;

static void Kraken_dealloc(Kraken* self){

	Py_XDECREF(self->first);
	Py_XDECREF(self->last);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyTypeObject kraken_NoddyType = {
	PyVarObject_HEAD_INIT(NULL, 0)
		"kraken.Kraken",             /* tp_name */
	sizeof(Kraken), /* tp_basicsize */
	0,                         /* tp_itemsize */
	0,                         /* tp_dealloc */
	0,                         /* tp_print */
	0,                         /* tp_getattr */
	0,                         /* tp_setattr */
	0,                         /* tp_reserved */
	0,                         /* tp_repr */
	0,                         /* tp_as_number */
	0,                         /* tp_as_sequence */
	0,                         /* tp_as_mapping */
	0,                         /* tp_hash  */
	0,                         /* tp_call */
	0,                         /* tp_str */
	0,                         /* tp_getattro */
	0,                         /* tp_setattro */
	0,                         /* tp_as_buffer */
	Py_TPFLAGS_DEFAULT,        /* tp_flags */
	"Kraken objects",           /* tp_doc */
};

static PyModuleDef krakenmodule = {
	PyModuleDef_HEAD_INIT,
	"kraken",
	"Module that inherits Kraken API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

	PyMODINIT_FUNC
PyInit_kraken(void)
{
	PyObject* m;

	kraken_NoddyType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&kraken_NoddyType) < 0)
		return NULL;

	m = PyModule_Create(&krakenmodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&kraken_NoddyType);
	PyModule_AddObject(m, "Kraken", (PyObject *)&kraken_NoddyType);
	return m;
}






