//Find
PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	...
}

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
PyObject* netSendPrivateShopSearchInfoSub(PyObject* poSelf, PyObject* poArgs)
{
	int iPage;
	if (!PyTuple_GetInteger(poArgs, 0, &iPage))
		return Py_BuildException();

	CPythonNetworkStream::Instance().PrivateShopSearchChangePage(iPage);
	return Py_BuildNone();
}

PyObject* netSendPrivateShopSerchBuyItem(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	CPythonNetworkStream::Instance().SendPrivateShopSearchBuyItem(iIndex);
	return Py_BuildNone();
}

PyObject* netSendPrivateShopSearchInfo(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bIdx = 0;

	BYTE bJob;
	if (!PyTuple_GetByte(poArgs, bIdx++, &bJob))
		return Py_BuildException();
	BYTE bMaskType;
	if (!PyTuple_GetByte(poArgs, bIdx++, &bMaskType))
		return Py_BuildException();
	int iMaskSub;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMaskSub))
		return Py_BuildException();
	int iMinRefine;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMinRefine))
		return Py_BuildException();
	int iMaxRefine;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMaxRefine))
		return Py_BuildException();
	int iMinLevel;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMinLevel))
		return Py_BuildException();
	int iMaxLevel;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMaxLevel))
		return Py_BuildException();
	int iMinGold;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMinGold))
		return Py_BuildException();
	int iMaxGold;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMaxGold))
		return Py_BuildException();
	char* szItemName;
	if (!PyTuple_GetString(poArgs, bIdx++, &szItemName))
		return Py_BuildException();
#if defined(ENABLE_CHEQUE_SYSTEM)
	int iMinCheque;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMinCheque))
		return Py_BuildException();
	int iMaxCheque;
	if (!PyTuple_GetInteger(poArgs, bIdx++, &iMaxCheque))
		return Py_BuildException();
#endif

	CPythonNetworkStream::Instance().SendPrivateShopSearchInfoPacket(bJob, bMaskType, iMaskSub, iMinRefine, iMaxRefine, iMinLevel, iMaxLevel, iMinGold, iMaxGold, szItemName
#if defined(ENABLE_CHEQUE_SYSTEM)
		, iMinCheque, iMaxCheque
#endif
	);
	return Py_BuildNone();
}

PyObject* netClosePrivateShopSearchWindow(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream::Instance().SendPrivateShopSearchClose();
	return Py_BuildNone();
}
#endif

//Find
		{ "SetSkillGroupFake",						netSetSkillGroupFake,						METH_VARARGS },
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		{ "SendPrivateShopSearchInfoSub",			netSendPrivateShopSearchInfoSub,			METH_VARARGS },
		{ "SendPrivateShopSerchBuyItem",			netSendPrivateShopSerchBuyItem,				METH_VARARGS },
		{ "SendPrivateShopSearchInfo",				netSendPrivateShopSearchInfo,				METH_VARARGS },	
		{ "ClosePrivateShopSearchWindow",			netClosePrivateShopSearchWindow,			METH_VARARGS },		
#endif