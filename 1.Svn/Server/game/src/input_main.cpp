///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void CInputMain::PrivateShopSearchClose(LPCHARACTER ch, const char* data)
{
	ch->SetPrivateShopSearchState(SHOP_SEARCH_OFF);
}
void CInputMain::PrivateShopSearchBuyItem(LPCHARACTER ch, const char* data)
{
	const TPacketCGPrivateShopSearchBuyItem* p = reinterpret_cast<const TPacketCGPrivateShopSearchBuyItem*>(data);
	CShopManager::Instance().ShopSearchBuy(ch, p);
}
void CInputMain::PrivateShopSearch(LPCHARACTER ch, const char* data)
{
	const TPacketCGPrivateShopSearch* p = reinterpret_cast<const TPacketCGPrivateShopSearch*>(data);
	CShopManager::Instance().ShopSearchProcess(ch, p);
}
#endif

//Find
	case HEADER_CG_SAFEBOX_ITEM_MOVE:
		SafeboxItemMove(ch, c_pData);
		break;
		
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	case HEADER_CG_PRIVATE_SHOP_SEARCH:
		PrivateShopSearch(ch, c_pData);
		break;
	case HEADER_CG_PRIVATE_SHOP_SEARCH_CLOSE:
		PrivateShopSearchClose(ch, c_pData);
		break;
	case HEADER_CG_PRIVATE_SHOP_SEARCH_BUY_ITEM:
		PrivateShopSearchBuyItem(ch, c_pData);
		break;
#endif