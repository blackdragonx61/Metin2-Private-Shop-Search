///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void CShopManager::ShopSearchProcess(LPCHARACTER ch, const TPacketCGPrivateShopSearch* p)
{
	if (ch == NULL || ch->GetDesc() == NULL || p == NULL)
		return;

	if (ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_CLOSE_TABS"));
		return;
	}

	TEMP_BUFFER buf;

	for (std::map<DWORD, CShop*>::const_iterator it = m_map_pkShopByPC.begin(); it != m_map_pkShopByPC.end(); ++it)
	{
		CShop* tShopTable = it->second;
		if (tShopTable == NULL)
			continue;

		LPCHARACTER GetOwner = tShopTable->GetShopOwner();
		if (GetOwner == NULL || ch == GetOwner)
			continue;

		const std::vector<CShop::SHOP_ITEM>& vItemVec = tShopTable->GetItemVector();
		for (std::vector<CShop::SHOP_ITEM>::const_iterator ShopIter = vItemVec.begin(); ShopIter != vItemVec.end(); ++ShopIter)
		{
			LPITEM item = ShopIter->pkItem;
			if (item == NULL)
				continue;

			/*First n character equals(case insensitive)*/
			if (strncasecmp(item->GetName(), p->szItemName, strlen(p->szItemName)))
				continue;

			if ((p->iMinRefine <= item->GetRefineLevel() && p->iMaxRefine >= item->GetRefineLevel()) == false)
				continue;

			if ((p->iMinLevel <= item->GetLevelLimit() && p->iMaxLevel >= item->GetLevelLimit()) == false)
				continue;

			if ((p->iMinGold <= ShopIter->price && p->iMaxGold >= ShopIter->price) == false)
				continue;

#if defined(ENABLE_CHEQUE_SYSTEM)
			if ((p->iMinCheque <= it2->cheque_price && p->iMaxCheque >= it2->cheque_price) == false)
				continue;
#endif

			if (p->bMaskType != ITEM_NONE && p->bMaskType != item->GetType()) // ITEM_NONE: All Categories
				continue;

			if (p->iMaskSub != -1 && p->iMaskSub != item->GetSubType()) // -1: No SubType Check
				continue;

			switch (p->bJob)
			{
			case JOB_WARRIOR:
				if (item->GetAntiFlag() & ITEM_ANTIFLAG_WARRIOR)
					continue;
				break;

			case JOB_ASSASSIN:
				if (item->GetAntiFlag() & ITEM_ANTIFLAG_ASSASSIN)
					continue;
				break;

			case JOB_SHAMAN:
				if (item->GetAntiFlag() & ITEM_ANTIFLAG_SHAMAN)
					continue;
				break;

			case JOB_SURA:
				if (item->GetAntiFlag() & ITEM_ANTIFLAG_SURA)
					continue;
				break;

#if defined(ENABLE_WOLFMAN_CHARACTER)
			case JOB_WOLFMAN:
				if (item->GetAntiFlag() & ITEM_ANTIFLAG_WOLFMAN)
					continue;
				break;
#endif
			}

			TPacketGCPrivateShopSearchItem pack2;
			pack2.item.vnum = ShopIter->vnum;
			pack2.item.price = ShopIter->price;
			pack2.item.count = ShopIter->count;
#if defined(ENABLE_CHEQUE_SYSTEM)
			pack2.item.byChequePrice = it2->cheque_price;
#endif
			pack2.item.display_pos = static_cast<BYTE>(std::distance(vItemVec.begin(), ShopIter));
			pack2.dwShopPID = GetOwner->GetPlayerID();
			std::memcpy(&pack2.szSellerName, GetOwner->GetName(), sizeof(pack2.szSellerName));
			std::memcpy(&pack2.item.alSockets, item->GetSockets(), sizeof(pack2.item.alSockets));
			std::memcpy(&pack2.item.aAttr, item->GetAttributes(), sizeof(pack2.item.aAttr));
			buf.write(&pack2, sizeof(pack2));
		}
	}

	if (buf.size() <= 0)
		return;

	TPacketGCPrivateShopSearch pack;
	pack.header = HEADER_GC_PRIVATE_SHOP_SEARCH;
	pack.size = static_cast<WORD>(sizeof(pack) + buf.size());
	ch->GetDesc()->BufferedPacket(&pack, sizeof(pack));
	ch->GetDesc()->Packet(buf.read_peek(), buf.size());
}

#include "unique_item.h"
#include "target.h"
void CShopManager::ShopSearchBuy(LPCHARACTER ch, const TPacketCGPrivateShopSearchBuyItem* p)
{
	if (ch == NULL || ch->GetDesc() == NULL || p == NULL)
		return;

	if (ch->GetExchange() || ch->GetMyShop() || ch->GetShopOwner() || ch->IsOpenSafebox() || ch->IsCubeOpen())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_CLOSE_TABS"));
		return;
	}

	LPCHARACTER ShopCH = CHARACTER_MANAGER::instance().FindByPID(p->dwShopPID);
	if (ShopCH == NULL)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_NO_SHOP"));
		return;
	}

	if (ch == ShopCH) // what?
		return;

	CShop* pkShop = ShopCH->GetMyShop();
	if (pkShop == NULL || pkShop->IsPCShop() == false)
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_NO_SHOP"));
		return;
	}

	const BYTE bState = ch->GetPrivateShopSearchState();
	switch (bState)
	{
	case SHOP_SEARCH_LOOKING:
	{
		if (ch->CountSpecifyItem(PRIVATE_SHOP_SEARCH_LOOKING_GLASS) == 0)
		{
			const TItemTable* GlassTable = ITEM_MANAGER::instance().GetTable(PRIVATE_SHOP_SEARCH_LOOKING_GLASS);
			if (GlassTable)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_WHERE_IS_ITEM"), GlassTable->szLocaleName);
			return;
		}
		if (ch->GetMapIndex() != ShopCH->GetMapIndex())
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_SAMEMAP_ERR"));
			return;
		}

		const DWORD dwSellerVID(ShopCH->GetVID());
		if (CTargetManager::instance().GetTargetInfo(ch->GetPlayerID(), TARGET_TYPE_VID_SHOP_SEARCH, dwSellerVID))
			CTargetManager::instance().DeleteTarget(ch->GetPlayerID(), SHOP_SEARCH_INDEX, "__SHOPSEARCH_TARGET__");

		CTargetManager::Instance().CreateTarget(ch->GetPlayerID(), SHOP_SEARCH_INDEX, "__SHOPSEARCH_TARGET__", TARGET_TYPE_VID_SHOP_SEARCH, dwSellerVID, 0, ch->GetMapIndex(), "Shop Search", 1);

		if (CTargetManager::instance().GetTargetInfo(ch->GetPlayerID(), TARGET_TYPE_VID_SHOP_SEARCH, dwSellerVID))
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_SUCCESS_TARGET"));
		break;
	}

	case SHOP_SEARCH_TRADING:
	{
		if (ch->CountSpecifyItem(PRIVATE_SHOP_SEARCH_TRADING_GLASS) == 0)
		{
			const TItemTable* GlassTable = ITEM_MANAGER::instance().GetTable(PRIVATE_SHOP_SEARCH_TRADING_GLASS);
			if (GlassTable)
				ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_WHERE_IS_ITEM"), GlassTable->szLocaleName);
			return;
		}

		ch->SetMyShopTime();
		int ret = pkShop->Buy(ch, p->bPos, true);

		if (SHOP_SUBHEADER_GC_OK != ret)
		{
			TPacketGCShop pack;
			pack.header = HEADER_GC_SHOP;
			pack.subheader = static_cast<BYTE>(ret);
			pack.size = sizeof(TPacketGCShop);
			ch->GetDesc()->Packet(&pack, sizeof(pack));
		}
		else
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("SHOP_SEARCH_OK"));

		break;
	}
	default:
		sys_err("ShopSearchBuy ch(%s) wrong state(%d)", ch->GetName(), bState);
		break;
	}
}
#endif