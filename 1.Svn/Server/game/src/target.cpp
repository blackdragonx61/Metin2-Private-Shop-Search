//Find
void SendTargetUpdatePacket(LPDESC d, int iID, int x, int y)

///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void SendTargetUpdatePacket(LPDESC d, int iID, int x, int y, bool bIsShopSearch)
#else
void SendTargetUpdatePacket(LPDESC d, int iID, int x, int y)
#endif

//Find
pck.lY = y;
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
pck.bIsShopSearch = bIsShopSearch;
#endif

//Find
		case TARGET_TYPE_VID:
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		case TARGET_TYPE_VID_SHOP_SEARCH:
#endif

//Find
	if (!tch && info->iType == TARGET_TYPE_VID)
	
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	if (!tch && (info->iType == TARGET_TYPE_VID || info->iType == TARGET_TYPE_VID_SHOP_SEARCH))
#else
	if (!tch && info->iType == TARGET_TYPE_VID)
#endif

//Find
		if (info->bSendToClient)
			SendTargetUpdatePacket(pkChr->GetDesc(), info->iID, x, y);
			
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
		const bool IsShopSearch = (info->iType == TARGET_TYPE_VID_SHOP_SEARCH);
		if (info->bSendToClient)
			SendTargetUpdatePacket(pkChr->GetDesc(), info->iID, x, y, IsShopSearch);
#else
		if (info->bSendToClient)
			SendTargetUpdatePacket(pkChr->GetDesc(), info->iID, x, y);
#endif

///Add new func
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void CTargetManager::DeleteShopSearchTarget(DWORD dwPID)
{
	std::vector<DWORD> vPID;
	for (std::map<DWORD, std::list<LPEVENT>>::const_iterator it = m_map_kListEvent.begin(); it != m_map_kListEvent.end(); ++it)
	{
		for (std::list<LPEVENT>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			LPEVENT event = *(it2);
			if (event == NULL)
				continue;

			TargetInfo* eventInfo = dynamic_cast<TargetInfo*>(event->info);
			if (eventInfo != NULL && eventInfo->iArg1 == static_cast<int>(dwPID))
				vPID.push_back(it->first);
		}
	}
	for (std::vector<DWORD>::const_iterator it = vPID.begin(); it != vPID.end(); ++it)
		DeleteTarget(*(it), SHOP_SEARCH_INDEX, "__SHOPSEARCH_TARGET__");
}
#endif