///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
#include "packet.h"
#endif

//Find
	void	DestroyPCShop(LPCHARACTER ch);
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	void ShopSearchBuy(LPCHARACTER ch, const TPacketCGPrivateShopSearchBuyItem* p);
	void ShopSearchProcess(LPCHARACTER ch, const TPacketCGPrivateShopSearch* p);
#endif