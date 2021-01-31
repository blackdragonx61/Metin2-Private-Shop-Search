//Find
	m_dwMountTime = 0;
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	bPrivateShopSearchState = SHOP_SEARCH_OFF;
#endif

//Find in void CHARACTER::CloseMyShop()
		SetPolymorph(GetJob(), true);

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		CTargetManager::instance().DeleteShopSearchTarget(static_cast<DWORD>(GetVID()));
#endif

//Find
				pkChrCauser->SetShopOwner(this);
				
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
				if (CTargetManager::instance().GetTargetInfo(pkChrCauser->GetPlayerID(), TARGET_TYPE_VID_SHOP_SEARCH, static_cast<DWORD>(GetVID())))
					CTargetManager::instance().DeleteTarget(pkChrCauser->GetPlayerID(), SHOP_SEARCH_INDEX, "__SHOPSEARCH_TARGET__");
#endif

///Add new func
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void CHARACTER::OpenPrivateShopSearch(DWORD dwVnum)
{
	if (GetDesc() == NULL)
		return;
	
	if (GetPrivateShopSearchState() != SHOP_SEARCH_OFF)
		return;
		
	if (GetExchange() || GetMyShop() || GetShopOwner() || IsOpenSafebox() || IsCubeOpen())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_CLOSE_TABS"));
		return;
	}

	TPacketGCPrivateShopSearchOpen p;
	p.header = HEADER_GC_PRIVATE_SHOP_SEARCH_OPEN;
	GetDesc()->Packet(&p, sizeof(p));

	bPrivateShopSearchState = (dwVnum == PRIVATE_SHOP_SEARCH_LOOKING_GLASS) ? SHOP_SEARCH_LOOKING : SHOP_SEARCH_TRADING;
}
#endif