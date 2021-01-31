//Find
	void CreateTargetEffect(DWORD dwID, long lx, long ly);
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	void CreateShopSearchTargetEffect(DWORD dwID, long lx, long ly);
	void CreateShopSearchTargetEffect(DWORD dwID, DWORD dwChrVID);
#endif

//Find
	std::map<DWORD, SReserveTargetEffect> m_kMap_dwID_kReserveTargetEffect;
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	std::map<DWORD, DWORD> m_kMap_dwTargetID_dwChrIDShopSearch;
	std::map<DWORD, SReserveTargetEffect> m_kMap_dwID_kReserveTargetEffectShopSearch;
#endif