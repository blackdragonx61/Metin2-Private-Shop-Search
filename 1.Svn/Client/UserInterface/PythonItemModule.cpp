//Find
	PyModule_AddIntConstant(poModule, "MATERIAL_DS_REFINE_HOLLY",	CItemData::MATERIAL_DS_REFINE_HOLLY);
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	PyModule_AddIntConstant(poModule, "DS_SLOT1",					CItemData::DS_SLOT1);
	PyModule_AddIntConstant(poModule, "DS_SLOT2",					CItemData::DS_SLOT2);
	PyModule_AddIntConstant(poModule, "DS_SLOT3",					CItemData::DS_SLOT3);
	PyModule_AddIntConstant(poModule, "DS_SLOT4",					CItemData::DS_SLOT4);
	PyModule_AddIntConstant(poModule, "DS_SLOT5",					CItemData::DS_SLOT5);
	PyModule_AddIntConstant(poModule, "DS_SLOT6",					CItemData::DS_SLOT6);
	PyModule_AddIntConstant(poModule, "USE_CLEAN_SOCKET",			CItemData::USE_CLEAN_SOCKET);
	PyModule_AddIntConstant(poModule, "ITEM_TYPE_SKILLFORGET",		CItemData::ITEM_TYPE_SKILLFORGET);
	PyModule_AddIntConstant(poModule, "MATERIAL_LEATHER",			CItemData::MATERIAL_LEATHER);
#endif