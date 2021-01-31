//Find
int CShop::Buy(LPCHARACTER ch, BYTE pos)

///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
int CShop::Buy(LPCHARACTER ch, BYTE pos, bool bIsShopSearch)
#else
int CShop::Buy(LPCHARACTER ch, BYTE pos)
#endif

//Find
	if (it == m_map_guest.end())
		return SHOP_SUBHEADER_GC_END;
		
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	if (bIsShopSearch == false && it == m_map_guest.end())
		return SHOP_SUBHEADER_GC_END;
#else
	if (it == m_map_guest.end())
		return SHOP_SUBHEADER_GC_END;
#endif

//Find
	if (IsPCShop())
	{
		if (!pkSelectedItem)
		{
			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
					ch->GetPlayerID(),
					m_pkPC->GetPlayerID());
			return false;
		}

		if ((pkSelectedItem->GetOwner() != m_pkPC))
		{
			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
					ch->GetPlayerID(),
					m_pkPC->GetPlayerID());

			return false;
		}
	}
	
///Change
	if (IsPCShop())
	{
		if (!pkSelectedItem)
		{
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
			if (bIsShopSearch == true)
				return SHOP_SUBHEADER_GC_SOLDOUT;
#endif
			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
					ch->GetPlayerID(),
					m_pkPC->GetPlayerID());
			return false;
		}

		if ((pkSelectedItem->GetOwner() != m_pkPC))
		{
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
			if (bIsShopSearch == true)
				return SHOP_SUBHEADER_GC_SOLDOUT;
#endif
			sys_log(0, "Shop::Buy : Critical: This user seems to be a hacker : invalid pcshop item : BuyerPID:%d SellerPID:%d",
					ch->GetPlayerID(),
					m_pkPC->GetPlayerID());

			return false;
		}
	}

//Find
	if (it->second)	// if other empire, price is triple
		dwPrice *= 3;
		
///Change
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	if (bIsShopSearch == false && it->second)	// if other empire, price is triple
		dwPrice *= 3;
#else
	if (it->second)	// if other empire, price is triple
		dwPrice *= 3;
#endif