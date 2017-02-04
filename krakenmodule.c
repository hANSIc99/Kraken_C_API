#include <Python.h>

static PyObject *spam_system(PyObject *self, PyObject *args){

    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    return Py_BuildValue("i", sts);
}

static PyMethodDef SpamMethods[] = {
    
    {"system",  spam_system, METH_VARARGS,
     "Execute a shell command."},
    
    {NULL, NULL, 0, NULL}        /* Sentinel */
};




PyMODINIT_FUNC initspam(void){

    (void) Py_InitModule("spam", SpamMethods);
}

int main(int argc, char *argv[]){

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(argv[0]);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Add a static module */
    initspam();
}






