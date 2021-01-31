//Find
int CShopEx::Buy(LPCHARACTER ch, BYTE pos)

///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
int CShopEx::Buy(LPCHARACTER ch, BYTE pos, bool bIsShopSearch)
#else
int CShopEx::Buy(LPCHARACTER ch, BYTE pos)
#endif