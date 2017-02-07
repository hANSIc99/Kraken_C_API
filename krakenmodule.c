#include <Python.h>
#include <structmember.h>
#include <stdio.h>
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

static int Kraken_traverse(Kraken *self, visitproc visit, void *arg){

	Py_VISIT(self->first);
	Py_VISIT(self->last);

	return 0;
}

static int Kraken_clear(Kraken *self){

	Py_CLEAR(self->first);
	Py_CLEAR(self->last);

	return 0;
}

static void Kraken_dealloc(Kraken* self){

	printf("dealloc called\n");
	Kraken_clear(self);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *Kraken_new(PyTypeObject *type, PyObject *args, PyObject *kwds){

	printf("Kraken new executed\n");

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

/* pass api- and secret-key durin initialization */

static int Kraken_init(Kraken *self, PyObject *args, PyObject *kwds){

	printf("Kraken init executed\n");

	PyObject *first = NULL, *last = NULL, *tmp;

	static char *kwlist[] = {"first", "last", "number", NULL};

	if(!PyArg_ParseTupleAndKeywords(args, kwds, "|SSi", kwlist, &first, &last, &self->number))
		return -1;

	if(first){
		tmp = self->first;
		Py_INCREF(first);
		self->first = first;
		Py_DECREF(tmp);
	}

	if(last){
		tmp = self->last;
		Py_INCREF(last);
		self->last = last;
		Py_DECREF(tmp);
	}

	return 0;
}

static PyMemberDef Kraken_members[] = {
	{"number", T_INT, offsetof(Kraken, number), 0, "Kraken number"},
	{NULL} /* Sentinel */
};





static PyGetSetDef Kraken_getseters[] = {

	{NULL}
};

static PyTypeObject *Kraken_name(Kraken* self){

	printf("Kraken_name called\n");

	return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Kraken_methods[] = {
	{"name", (PyCFunction)Kraken_name, METH_NOARGS, "Return the first and last name"},
	{NULL}	/* Sentinel */
};

static PyTypeObject kraken_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
		"kraken.Kraken",             /* tp_name */
	sizeof(Kraken), /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)Kraken_dealloc,   /* tp_dealloc */
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
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC,        /* tp_flags */
	"Kraken objects",           /* tp_doc */
	0,
	0,
	0,
	0,
	0,
	0,
	Kraken_methods,
	Kraken_members,
	Kraken_getseters,
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

	if (PyType_Ready(&kraken_Type) < 0)
		return NULL;

	m = PyModule_Create(&krakenmodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&kraken_Type);
	PyModule_AddObject(m, "Kraken", (PyObject *)&kraken_Type);
	return m;
}






