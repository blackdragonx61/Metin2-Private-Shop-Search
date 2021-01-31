//Find
		bool SendClientVersionPacket();
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		bool SendPrivateShopSearchClose();
		bool SendPrivateShopSearchBuyItem(int iIndex);
		void PrivateShopSearchChangePage(int iPage);
		bool SendPrivateShopSearchInfoPacket(BYTE, BYTE, int, int, int, int, int, int, int, const char*
#if defined(ENABLE_CHEQUE_SYSTEM)
			, int, int
#endif
		);
#endif

//Find
		bool RecvItemOwnership();
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		bool RecvPrivateShopSearch();
		bool RecvPrivateShopSearchOpen();
#endif