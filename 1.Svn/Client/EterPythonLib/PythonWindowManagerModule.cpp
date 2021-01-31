///Add
#include "../UserInterface/Locale_inc.h"

//Find
PyObject * wndButtonDisable(PyObject * poSelf, PyObject * poArgs)
{
	...
}

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
PyObject* wndIsDisable(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();

	const BOOL IsDisable = dynamic_cast<UI::CButton*>(pWindow)->IsDisable();
	return Py_BuildValue("i", IsDisable);
}
#endif

//Find
		{ "Disable",					wndButtonDisable,					METH_VARARGS },
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		{ "IsDisable",					wndIsDisable,						METH_VARARGS },
#endif