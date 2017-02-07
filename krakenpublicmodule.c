/*
 * =====================================================================================
 *
 *       Filename:  krakenpublicmodule.c
 *
 *    Description:  Public Api functions
 *
 *        Version:  1.0
 *        Created:  06.02.2017 17:37:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
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
} public;

static int public_traverse(public *self, visitproc visit, void *arg){

	Py_VISIT(self->first);
	Py_VISIT(self->last);

	return 0;
}

static int public_clear(public *self){

	Py_CLEAR(self->first);
	Py_CLEAR(self->last);

	return 0;
}

static void public_dealloc(public* self){

	printf("dealloc called\n");
	public_clear(self);
	Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *public_new(PyTypeObject *type, PyObject *args, PyObject *kwds){

	printf("public new executed\n");

	public *self;

	self = (public *)type->tp_alloc(type, 0);

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

static int public_init(public *self, PyObject *args, PyObject *kwds){

	printf("public init executed\n");

	PyObject *first = NULL, *last = NULL, *tmp;

	static char *kwlist[] = {"first", "last", "number", NULL};

	if(!PyArg_ParseTupleAndKeywords(args, kwds, "|ss", kwlist, &first, &last))
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


static PyMemberDef public_members[] = {
	{"number", T_INT, offsetof(public, number), 0, "Kraken number"},
	{NULL} /* Sentinel */
};


static PyGetSetDef public_getseters[] = {

	{NULL}
};

static PyTypeObject *public_name(public* self){

	printf("public_name called\n");

	return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef public_methods[] = {
	{"name", (PyCFunction)public_name, METH_NOARGS, "Return the first and last name"},
	{NULL}	/* Sentinel */
};

static PyTypeObject krakenpublic_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
		"kraken.public",             /* tp_name */
	sizeof(public), /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)public_dealloc,   /* tp_dealloc */
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
	"public objects",           /* tp_doc */
	0,
	0,
	0,
	0,
	0,
	0,
	public_methods,
	public_members,
	public_getseters,
	0,
	0,
	0,
	0,
	0,
	(initproc)public_init,
	0,
	public_new,
};

static PyModuleDef krakenpublicmodule = {
	PyModuleDef_HEAD_INIT,
	"kraken",
	"Module that inherits public API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_public(void){

	PyObject* m;

	if (PyType_Ready(&krakenpublic_Type) < 0)
		return NULL;

	m = PyModule_Create(&krakenpublicmodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&krakenpublic_Type);
	PyModule_AddObject(m, "public", (PyObject *)&krakenpublic_Type);
	return m;
}

