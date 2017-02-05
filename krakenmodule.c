#include <Python.h>
#include <structmember.h>
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

static PyObject *Kraken_new(PyTypeObject *type, PyObject *args, PyObject *kwds){

	Kraken *self;

	self = (Kraken *)type->tp_alloc(type, 0);

	if(self != NULL){
		self->first = PyUnicode_FromString("");
		if(self->first == NULL){
			Py_DECREF(self);
			return NULL;
		}

		self->last = PyUnicode_FromString("");
		if(self->last == NULL){
			Py_DECREF(self);
			return NULL;				
		}

		self->number = 0;

	}

	return (PyObject*)self;

}

static int Kraken_init(Kraken *self, PyObject *args, PyObject *kwds){

	PyObject *first = NULL, *last = NULL, *tmp;

	static char *kwlist[] = {"first", "last", "number", NULL};

	if(!PyArg_ParseTupleAndKeywords(args, kwds, "|00i", kwlist, &first, &last, &self->number))
		return -1;

	if(first){
		tmp = self->first;
		Py_INCREF(first);
		self->first = first;
		Py_XDECREF(tmp);
	}

	if(last){
		tmp = self->last;
		Py_INCREF(last);
		self->last = last;
		Py_XDECREF(tmp);
	}

	return 0;
}

static PyMemberDef Kraken_members[] = {
	{"first", T_OBJECT_EX, offsetof(Kraken, first), 0, "first name"},
	{"last", T_OBJECT_EX, offsetof(Kraken, last), 0, "last name"},
	{"number", T_INT, offsetof(Kraken, number), 0, "Kraken number"},
	{NULL} /* Sentinel */
};

static PyTypeObject *Kraken_name(Kraken* self){

	if(self->first == NULL){
		PyErr_SetString(PyExc_AttributeError, "first");
		return NULL;
	}


	if(self->last == NULL){
		PyErr_SetString(PyExc_AttributeError, "last");
		return NULL;
	}

	return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Kraken_methods[] = {
	{"name", (PyCFunction)Kraken_name, METH_NOARGS, "Return the first and last name"},
	{NULL}	/* Sentinel */
};

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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,        /* tp_flags */
	"Kraken objects",           /* tp_doc */
	0,
	0,
	0,
	0,
	0,
	0,
	Kraken_methods,
	Kraken_members,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Kraken_init,
	0,
	Kraken_new,
};

static PyModuleDef krakenmodule = {
	PyModuleDef_HEAD_INIT,
	"kraken",
	"Module that inherits Kraken API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_kraken(void){

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






