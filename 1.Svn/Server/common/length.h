//Find
enum ETeenFlags
{
	...
};

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
enum EPrivateShopSearchState
{
	SHOP_SEARCH_OFF,
	SHOP_SEARCH_LOOKING,
	SHOP_SEARCH_TRADING,
	SHOP_SEARCH_INDEX = 61000,
};
#endif