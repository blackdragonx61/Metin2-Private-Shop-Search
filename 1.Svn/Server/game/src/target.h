//Find
	TARGET_TYPE_VID	= (1 << 1),
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	TARGET_TYPE_VID_SHOP_SEARCH	= (1 << 2),
#endif

//Find
		void Logout(DWORD dwPID);
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		void DeleteShopSearchTarget(DWORD dwPID);
#endif