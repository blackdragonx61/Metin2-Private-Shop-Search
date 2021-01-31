//Find
	Set(HEADER_CG_SAFEBOX_ITEM_MOVE, sizeof(TPacketCGItemMove), "SafeboxItemMove", true);
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	Set(HEADER_CG_PRIVATE_SHOP_SEARCH, sizeof(TPacketCGPrivateShopSearch), "PrivateShopSearch", true);
	Set(HEADER_CG_PRIVATE_SHOP_SEARCH_CLOSE, sizeof(TPacketCGPrivateShopSearchClose), "PrivateShopSearchClose", true);
	Set(HEADER_CG_PRIVATE_SHOP_SEARCH_BUY_ITEM, sizeof(TPacketCGPrivateShopSearchBuyItem), "PrivateShopSearchBuyItem", true);
#endif