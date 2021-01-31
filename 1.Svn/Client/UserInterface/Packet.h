//Find
	HEADER_CG_STATE_CHECKER					= 206,
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	HEADER_CG_PRIVATE_SHOP_SEARCH = 216,
	HEADER_CG_PRIVATE_SHOP_SEARCH_CLOSE = 217,
	HEADER_CG_PRIVATE_SHOP_SEARCH_BUY_ITEM = 218,
#endif

//Find
	HEADER_GC_RESPOND_CHANNELSTATUS				= 210,
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	HEADER_GC_PRIVATE_SHOP_SEARCH = 216,
	HEADER_GC_PRIVATE_SHOP_SEARCH_OPEN = 217,
#endif

//Find
typedef struct command_script_select_item
{
    ...
} TPacketCGScriptSelectItem;

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
typedef struct command_privateshop_searchcg
{
	BYTE 	header;
	BYTE 	bJob;
	BYTE 	bMaskType;
	int 	iMaskSub;
	int 	iMinRefine;
	int 	iMaxRefine;
	int 	iMinLevel;
	int 	iMaxLevel;
	int 	iMinGold;
	int 	iMaxGold;
	char	szItemName[CItemData::ITEM_NAME_MAX_LEN + 1];
#if defined(ENABLE_CHEQUE_SYSTEM)
	int 	iMinCheque;
	int 	iMaxCheque;
#endif
} TPacketCGPrivateShopSearch;

typedef struct command_privateshopsearch_item
{
	packet_shop_item item;
	char	szSellerName[CHARACTER_NAME_MAX_LEN + 1];
	DWORD	dwShopPID;
} TPacketGCPrivateShopSearchItem;

typedef struct command_privateshop_searchgc
{
	BYTE		header;
	WORD		size;
} TPacketGCPrivateShopSearch;

typedef struct command_privateshop_searchopengc
{
	BYTE		header;
} TPacketGCPrivateShopSearchOpen;

typedef struct command_privateshop_closecg
{
	BYTE		header;
} TPacketCGPrivateShopSearchClose;
typedef struct command_privateshop_buy_item
{
	BYTE		header;
	BYTE		pos;
	DWORD		dwShopPID;
} TPacketCGPrivateShopSearchBuyItem;
#endif

//Find
	CREATE_TARGET_TYPE_CHARACTER,
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	CREATE_TARGET_TYPE_SHOP_SEARCH = 1 << 2,
#endif

//Find in TPacketGCTargetUpdate;
    long        lX, lY;
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	bool		bIsShopSearch;
#endif