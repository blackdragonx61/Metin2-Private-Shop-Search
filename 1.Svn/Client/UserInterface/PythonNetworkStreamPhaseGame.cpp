//Find
			case HEADER_GC_ITEM_USE:
				ret = RecvItemUsePacket();
				break;
				
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
			case HEADER_GC_PRIVATE_SHOP_SEARCH:
				ret = RecvPrivateShopSearch();
				break;
			case HEADER_GC_PRIVATE_SHOP_SEARCH_OPEN:
				ret = RecvPrivateShopSearchOpen();
				break;
#endif

//Find
bool CPythonNetworkStream::SendRefinePacket(BYTE byPos, BYTE byType)
{
	...
}

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
bool CPythonNetworkStream::RecvPrivateShopSearch()
{
	TPacketGCPrivateShopSearch p;
	if (!Recv(sizeof(p), &p))
		return false;

	CPythonShop::Instance().ClearShopSearchData();
	unsigned int iPacketSize = (p.size - sizeof(TPacketGCPrivateShopSearch));
	for (; iPacketSize > 0; iPacketSize -= sizeof(TPacketGCPrivateShopSearchItem))
	{
		TPacketGCPrivateShopSearchItem Item;
		if (!Recv(sizeof(TPacketGCPrivateShopSearchItem), &Item))
			return false;

		ShopSearchData* SShopSearch = new ShopSearchData();
		SShopSearch->item = Item.item;
		SShopSearch->name.assign(Item.szSellerName);
		SShopSearch->dwShopPID = Item.dwShopPID;
		CPythonShop::Instance().SetShopSearchItemData(SShopSearch);
	}

	CPythonShop::Instance().SortShopSearchData();
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshPShopSearchDialog", Py_BuildValue("()"));
	return true;
}

bool CPythonNetworkStream::RecvPrivateShopSearchOpen()
{
	TPacketGCPrivateShopSearchOpen p;
	if (!Recv(sizeof(p), &p))
		return false;

	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OpenPShopSearchDialogCash", Py_BuildValue("()"));
	return true;
}

void CPythonNetworkStream::PrivateShopSearchChangePage(int iPage)
{
	CPythonShop::Instance().ShopSearchChangePage(iPage);
	PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshPShopSearchDialog", Py_BuildValue("()"));
}

bool CPythonNetworkStream::SendPrivateShopSearchInfoPacket(BYTE bJob, BYTE bMaskType, int iMaskSub, int iMinRefine, int iMaxRefine, int iMinLevel, int iMaxLevel, int iMinGold, int iMaxGold, const char* szItemName
#if defined(ENABLE_CHEQUE_SYSTEM)
	, int iMinCheque, int iMaxCheque
#endif
)
{
	TPacketCGPrivateShopSearch packet;
	packet.header = HEADER_CG_PRIVATE_SHOP_SEARCH;
	packet.bJob = bJob;
	packet.bMaskType = bMaskType;
	packet.iMaskSub = iMaskSub;
	packet.iMinRefine = iMinRefine;
	packet.iMaxRefine = iMaxRefine;
	packet.iMinLevel = iMinLevel;
	packet.iMaxLevel = iMaxLevel;
	packet.iMinGold = iMinGold;
	packet.iMaxGold = iMaxGold;
	std::strcpy(packet.szItemName, szItemName);
#if defined(ENABLE_CHEQUE_SYSTEM)
	packet.iMinCheque = iMinCheque;
	packet.iMaxCheque = iMaxCheque;
#endif

	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}

bool CPythonNetworkStream::SendPrivateShopSearchClose()
{
	TPacketCGPrivateShopSearchClose packet;
	packet.header = HEADER_CG_PRIVATE_SHOP_SEARCH_CLOSE;
	if (!Send(sizeof(packet), &packet))
		return false;

	CPythonShop::Instance().ClearShopSearchData();
	return SendSequence();
}

bool CPythonNetworkStream::SendPrivateShopSearchBuyItem(int iIndex)
{
	auto Item = CPythonShop::Instance().GetShopSearchItemData(iIndex);
	if (Item == nullptr)
		return false;

	TPacketCGPrivateShopSearchBuyItem packet;
	packet.header = HEADER_CG_PRIVATE_SHOP_SEARCH_BUY_ITEM;
	packet.pos = Item->item.display_pos;
	packet.dwShopPID = Item->dwShopPID;
	if (!Send(sizeof(packet), &packet))
		return false;

	return SendSequence();
}
#endif

//Find
	if (CREATE_TARGET_TYPE_LOCATION == kTargetCreate.byType)
	{
		rkpyMiniMap.CreateTarget(kTargetCreate.lID, kTargetCreate.szTargetName);
	}
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	else if (CREATE_TARGET_TYPE_SHOP_SEARCH == kTargetCreate.byType)
	{
		rkpyMiniMap.CreateTarget(kTargetCreate.lID, kTargetCreate.szTargetName, kTargetCreate.dwVID);
		rkpyBG.CreateShopSearchTargetEffect(kTargetCreate.lID, kTargetCreate.dwVID);
	}
#endif

//Find
	rkpyBG.CreateTargetEffect(kTargetUpdate.lID, kTargetUpdate.lX, kTargetUpdate.lY);
	
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	if (kTargetUpdate.bIsShopSearch == true)
		rkpyBG.CreateShopSearchTargetEffect(kTargetUpdate.lID, kTargetUpdate.lX, kTargetUpdate.lY);
	else
		rkpyBG.CreateTargetEffect(kTargetUpdate.lID, kTargetUpdate.lX, kTargetUpdate.lY);
#else
	rkpyBG.CreateTargetEffect(kTargetUpdate.lID, kTargetUpdate.lX, kTargetUpdate.lY);
#endif