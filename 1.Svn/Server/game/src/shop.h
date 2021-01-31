//Find
		virtual int	Buy(LPCHARACTER ch, BYTE pos);
		
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		const std::vector<SHOP_ITEM>& GetItemVector() const { return m_itemVector; }
		LPCHARACTER GetShopOwner() { return m_pkPC; }
		virtual int	Buy(LPCHARACTER ch, BYTE pos, bool bIsShopSearch = false);
#else
		virtual int	Buy(LPCHARACTER ch, BYTE pos);
#endif