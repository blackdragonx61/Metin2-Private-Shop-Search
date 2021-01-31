//Find
#ifdef ENABLE_COSTUME_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM",	1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_COSTUME_SYSTEM",	0);
#endif

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	PyModule_AddIntConstant(poModule, "BL_PRIVATESHOP_SEARCH_SYSTEM", true);
#else
	PyModule_AddIntConstant(poModule, "BL_PRIVATESHOP_SEARCH_SYSTEM", false);
#endif

///@If you don't use these, add:
	PyModule_AddIntConstant(poModule, "ENABLE_WOLFMAN_CHARACTER", false);
	PyModule_AddIntConstant(poModule, "ENABLE_CHEQUE_SYSTEM", false);