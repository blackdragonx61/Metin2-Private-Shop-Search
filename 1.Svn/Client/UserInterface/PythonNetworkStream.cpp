//Find
			Set(HEADER_GC_PARTY_INVITE,	CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPartyInvite), STATIC_SIZE_PACKET));
			
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
			Set(HEADER_GC_PRIVATE_SHOP_SEARCH, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPrivateShopSearch), DYNAMIC_SIZE_PACKET));
			Set(HEADER_GC_PRIVATE_SHOP_SEARCH_OPEN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCPrivateShopSearchOpen), STATIC_SIZE_PACKET));
#endif