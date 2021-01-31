//Find
							case REWARD_BOX_UNIQUE_ITEM_CAPE_OF_COURAGE:
								AggregateMonster();
								item->SetCount(item->GetCount()-1);
								break;
								
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
							case PRIVATE_SHOP_SEARCH_LOOKING_GLASS:
							case PRIVATE_SHOP_SEARCH_TRADING_GLASS:
								OpenPrivateShopSearch(item->GetVnum());
								break;
#endif