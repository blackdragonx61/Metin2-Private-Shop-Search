//Find
		BOOL GetItemData(BYTE tabIdx, DWORD dwSlotPos, const TShopItemData ** c_ppItemData);
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		void SetShopSearchItemData(ShopSearchData* sShopData);
		ShopSearchData* GetShopSearchItemData(DWORD dwIndex);
		void ClearShopSearchData();
		void SortShopSearchData();
		void ShopSearchChangePage(int iPage);
		size_t GetShopSearchResultCount() const { return vShopSearch.size(); }
		int GetShopSearchPage() const { return iShopSearchPage; }
#endif

//Find
		TPrivateShopItemStock	m_PrivateShopItemStock;
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		std::vector<ShopSearchData*> vShopSearch;
		int iShopSearchPage;
#endif