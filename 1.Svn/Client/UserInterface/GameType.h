//Find
typedef struct packet_shop_item
{
    ...
} TShopItemData;

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
struct ShopSearchData 
{
	TShopItemData item;
	std::string name;
	DWORD dwShopPID;
};
#endif