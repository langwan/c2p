/* TODO 在mac系统上编译完成，如果使用ubuntu等系统请替换头文件和编译条件 */

#include <Python/Python.h>

/* example.fact method */
int fact(int n) {
	if(n <= 1) {
		return 1;
	}
	return n * fact(n - 1);
}

PyObject* wrap_fact(PyObject* self, PyObject* args) {
	int n, result;
	if(!PyArg_ParseTuple(args, "i:fact", &n))
		return NULL;
	result = fact(n);
	return Py_BuildValue("i", result);
}

/* example.list method */
void tuple(int* n, char* msg) {
	*n = 100;
	msg = strcpy(msg, "hello python i'm c.");
}

PyObject* wrap_tuple(PyObject* self) {
	int n = 0;
	char* msg = NULL;
	msg = (char *)malloc(sizeof(char) * 255);
	tuple(&n, msg);
	PyObject* tuple = PyTuple_New(2);
	PyObject *pn, *pm;
	PyTuple_SetItem(tuple, 0, PyInt_FromLong(n));
	/*TODO 可以在调用的时候打印出c函数中的内容，作为调试*/
	//printf("%s\n", msg);
	PyTuple_SetItem(tuple, 1, PyString_FromString(msg));
	return tuple;
}


static PyMethodDef exampleMethods[] = {
	{"fact", wrap_fact, METH_VARARGS, "Caculate N!"}, 
	{"tuple", (PyCFunction)wrap_tuple, METH_NOARGS, NULL}, 
	{NULL, NULL}
};

void initexample() {
	PyObject* m;
	m = Py_InitModule("example", exampleMethods);
}

