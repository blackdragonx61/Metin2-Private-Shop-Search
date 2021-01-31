//Find
		int			Messenger(LPCHARACTER ch, const char* c_pData, size_t uiBytes);
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		void		PrivateShopSearch(LPCHARACTER ch, const char* data);
		void		PrivateShopSearchClose(LPCHARACTER ch, const char* data);
		void		PrivateShopSearchBuyItem(LPCHARACTER ch, const char* data);
#endif