//Find
		PIXEL_POSITION		m_posSafeboxOpen;
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	protected:
		BYTE				bPrivateShopSearchState;
	public:
		BYTE				GetPrivateShopSearchState() const { return bPrivateShopSearchState; }
		void				SetPrivateShopSearchState(BYTE bState) { bPrivateShopSearchState = bState; }
		void				OpenPrivateShopSearch(DWORD dwVnum);
#endif