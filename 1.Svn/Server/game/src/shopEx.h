//Find
	virtual int		Buy(LPCHARACTER ch, BYTE pos);
	
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	virtual int		Buy(LPCHARACTER ch, BYTE pos, bool bIsShopSearch = false);
#else
	virtual int		Buy(LPCHARACTER ch, BYTE pos);
#endif