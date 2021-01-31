//Find
	CPythonShop::~CPythonShop(void)
	
///Add in
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	ClearShopSearchData();
#endif

//Find
PyObject * shopGetTabCoinType(PyObject * poSelf, PyObject * poArgs)
{
	...
}

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
#include "../GameLib/ItemManager.h"
void CPythonShop::ClearShopSearchData()
{
	for (auto obj : vShopSearch)
		delete obj;
	vShopSearch.clear();
	ShopSearchChangePage(1);
}

void CPythonShop::ShopSearchChangePage(int iPage)
{
	iShopSearchPage = iPage;
}

void CPythonShop::SetShopSearchItemData(ShopSearchData* sShopData)
{
	vShopSearch.push_back(sShopData);
}

ShopSearchData* CPythonShop::GetShopSearchItemData(DWORD dwIndex)
{
	dwIndex += (iShopSearchPage - 1) * 10;
	if (dwIndex >= vShopSearch.size())
		return nullptr;
		
	return vShopSearch.at(dwIndex);
}

void CPythonShop::SortShopSearchData()
{
	/*Sort by ASC
	1) Won
	2) Gold
	*/
	std::sort(vShopSearch.begin(), vShopSearch.end(), [](const ShopSearchData* a, const ShopSearchData* b)
		{
#if defined(ENABLE_CHEQUE_SYSTEM)
			return (a->item.byChequePrice < b->item.byChequePrice) || (a->item.byChequePrice == b->item.byChequePrice && a->item.price < b->item.price);
#else
			return (a->item.price < b->item.price);
#endif
		});
}

PyObject* shopGetPrivateShopSearchResult(PyObject* poSelf, PyObject* poArgs)
{
	int iLine;
	if (!PyTuple_GetInteger(poArgs, 0, &iLine))
		return Py_BuildException();

	auto ShopSearchData = CPythonShop::Instance().GetShopSearchItemData(iLine);
	if (ShopSearchData) 
	{
		CItemData* pItemData;
		if (CItemManager::Instance().GetItemDataPointer(ShopSearchData->item.vnum, &pItemData))
#if defined(ENABLE_CHEQUE_SYSTEM)
			return Py_BuildValue("ssiii", pItemData->GetName(), ShopSearchData->name.c_str(), ShopSearchData->item.count, ShopSearchData->item.price, ShopSearchData->item.byChequePrice);
#else
			return Py_BuildValue("ssii", pItemData->GetName(), ShopSearchData->name.c_str(), ShopSearchData->item.count, ShopSearchData->item.price);
#endif
	}
	
#if defined(ENABLE_CHEQUE_SYSTEM)
	return Py_BuildValue("ssiii", "", "", 0, 0, 0);
#else
	return Py_BuildValue("ssii", "", "", 0, 0);
#endif
}

PyObject* shopGetPrivateShopSelectItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM) 
	{
		auto ShopSearchData = CPythonShop::Instance().GetShopSearchItemData(iIndex);
		if (ShopSearchData)
			return Py_BuildValue("ii", ShopSearchData->item.aAttr[iAttrSlotIndex].bType, ShopSearchData->item.aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* shopGetPrivateShopSelectItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iMetinSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iMetinSocketIndex))
		return Py_BuildException();

	if (iMetinSocketIndex >= 0 && iMetinSocketIndex < ITEM_SOCKET_SLOT_MAX_NUM) 
	{
		auto ShopSearchData = CPythonShop::Instance().GetShopSearchItemData(iIndex);
		if (ShopSearchData)
			return Py_BuildValue("i", ShopSearchData->item.alSockets[iMetinSocketIndex]);
	}

	return Py_BuildValue("i", 0);
}

PyObject* shopGetPrivateShopSelectItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	auto ShopSearchData = CPythonShop::Instance().GetShopSearchItemData(iIndex);
	if (ShopSearchData)
		return Py_BuildValue("i", ShopSearchData->item.vnum);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetPrivateShopSearchResultMaxCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::Instance().GetShopSearchResultCount());
}

PyObject* shopGetPrivateShopSearchResultPage(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::Instance().GetShopSearchPage());
}
#endif

//Find
		{ "BuildPrivateShop",			shopBuildPrivateShop,			METH_VARARGS },
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		{ "GetPrivateShopSearchResult",	shopGetPrivateShopSearchResult,	METH_VARARGS },
		{ "GetPrivateShopSelectItemAttribute",	shopGetPrivateShopSelectItemAttribute,	METH_VARARGS },
		{ "GetPrivateShopSelectItemMetinSocket",	shopGetPrivateShopSelectItemMetinSocket,	METH_VARARGS },
		{ "GetPrivateShopSelectItemVnum",	shopGetPrivateShopSelectItemVnum,	METH_VARARGS },
		{ "GetPrivateShopSearchResultMaxCount",	shopGetPrivateShopSearchResultMaxCount,	METH_VARARGS },
		{ "GetPrivateShopSearchResultPage",	shopGetPrivateShopSearchResultPage,	METH_VARARGS },
#endif