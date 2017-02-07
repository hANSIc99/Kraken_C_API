/*
 * =====================================================================================
 *
 *       Filename:  krakenprivatemodule.c
 *
 *    Description:  Private API functions
 *
 *        Version:  1.0
 *        Created:  06.02.2017 17:37:51
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
#if 0
	PyObject *api_key;
	PyObject *sec_key;
#endif

	const char *api_key;
	const char *sec_key;

	struct kraken_api *kr_api;
} private;

static int private_traverse(private *self, visitproc visit, void *arg){

	Py_VISIT(self->sec_key);
	Py_VISIT(self->api_key);

	return 0;
}

static int private_clear(private *self){

	printf("clear calles\n");
	Py_CLEAR(self->sec_key);
	Py_CLEAR(self->api_key);

	return 0;
}

/* 
module = PyImport_ImportModule("testPython");
*/
static void private_dealloc(private* self){

	printf("dealloc called\n");
	private_clear(self);
	Py_TYPE(self)->tp_free((PyObject*)self);
}
static PyObject *private_new(PyTypeObject *type, PyObject *args, PyObject *kwds){

	printf("Kraken new executed\n");

	private *self;

	self = (private *)type->tp_alloc(type, 0);
#if 0
	if(self != NULL){
		self->api_key = PyUnicode_FromString("");
		if(self->api_key == NULL){
			Py_DECREF(self);
			return NULL;
		}

		self->sec_key = PyUnicode_FromString("");
		if(self->sec_key == NULL){
			Py_DECREF(self);
			return NULL;				
		}


	}
#endif
	return (PyObject*)self;

}
/* fehler bei self pointer irgendwo */
static int private_set_api_char(private *self){


	printf("in private_set_api_angekommen\n");

	printf("address: %lu\n", (unsigned long)self);


	printf("value of my_result: %s\n", self->api_key);

	return 0;
}

/* pass api- and secret-key durin initialization */
static int private_init(private *self, PyObject *args, PyObject *kwds){

	printf("private init executed\n");


	const char *api_key, *sec_key;

	if(!PyArg_ParseTuple(args, "ss", &(self->api_key), &(self->sec_key)))
		       return -1;

	printf("api-key: %s\n", self->api_key);
	printf("sec-key: %s\n", self->sec_key);

	private_set_api_char(self);

	
	kraken_init(&(self->kr_api), api_key, sec_key);

	return 0;
}



static PyMemberDef private_members[] = {
	{NULL} /* Sentinel */
};


static PyGetSetDef private_getseters[] = {

	{NULL}
};

static PyTypeObject *private_get_key(private* self){

	printf("private_get_key called\n");

	return PyUnicode_FromFormat("%S ", self->sec_key);
}

static PyMethodDef private_methods[] = {
	{"name", (PyCFunction)private_get_key, METH_NOARGS, "Return the first and last name"},
	{NULL}	/* Sentinel */
};

static PyTypeObject krakenprivate_Type = {
	PyVarObject_HEAD_INIT(NULL, 0)
		"kraken.private",             /* tp_name */
	sizeof(private), /* tp_basicsize */
	0,                         /* tp_itemsize */
	(destructor)private_dealloc,   /* tp_dealloc */
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
	"private objects",           /* tp_doc */
	0,
	0,
	0,
	0,
	0,
	0,
	private_methods,
	private_members,
	private_getseters,
	0,
	0,
	0,
	0,
	0,
	(initproc)private_init,
	0,
	private_new,
};

static PyModuleDef krakenprivatemodule = {
	PyModuleDef_HEAD_INIT,
	"kraken",
	"Module that inherits private API functions.",
	-1,
	NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_private(void){

	PyObject* m;

	if (PyType_Ready(&krakenprivate_Type) < 0)
		return NULL;

	m = PyModule_Create(&krakenprivatemodule);
	if (m == NULL)
		return NULL;

	Py_INCREF(&krakenprivate_Type);
	PyModule_AddObject(m, "private", (PyObject *)&krakenprivate_Type);
	return m;
}






