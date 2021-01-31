//Find
std::string g_strEffectName = "d:/ymir work/effect/etc/direction/direction_land.mse";

///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
static const std::string g_strShopSearchEffectName = "d:/ymir work/effect/etc/direction/direction_land2.mse";
#endif

//Find
	{
		std::map<DWORD, SReserveTargetEffect>::iterator itor = m_kMap_dwID_kReserveTargetEffect.begin();
		for (; itor != m_kMap_dwID_kReserveTargetEffect.end();)
		{
			DWORD dwID = itor->first;
			SReserveTargetEffect & rReserveTargetEffect = itor->second;

			float ilx = float(rReserveTargetEffect.ilx);
			float ily = float(rReserveTargetEffect.ily);

			float fHeight = rkMap.GetHeight(ilx, ily);
			if (0.0f == fHeight)
			{
				++itor;
				continue;
			}

			CreateSpecialEffect(dwID, ilx, ily, fHeight, g_strEffectName.c_str());

			itor = m_kMap_dwID_kReserveTargetEffect.erase(itor);
		}
	}
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	for (const auto& itor : m_kMap_dwTargetID_dwChrIDShopSearch)
	{
		CInstanceBase* pInstance = CPythonCharacterManager::Instance().GetInstancePtr(itor.second);
		if (!pInstance)
			continue;
		TPixelPosition kPixelPosition;
		pInstance->NEW_GetPixelPosition(&kPixelPosition);
		CreateSpecialEffect(itor.first, +kPixelPosition.x, -kPixelPosition.y, +kPixelPosition.z, g_strShopSearchEffectName.c_str());
	}
	for (auto itor = m_kMap_dwID_kReserveTargetEffectShopSearch.begin(); itor != m_kMap_dwID_kReserveTargetEffectShopSearch.end();)
	{
		const SReserveTargetEffect& rReserveTargetEffect = itor->second;
		const auto ilx = static_cast<float>(rReserveTargetEffect.ilx);
		const auto ily = static_cast<float>(rReserveTargetEffect.ily);
		const auto fHeight = rkMap.GetHeight(ilx, ily);
		if (0.0f == fHeight) {
			++itor;
			continue;
		}
		CreateSpecialEffect(itor->first, ilx, ily, fHeight, g_strShopSearchEffectName.c_str());
		itor = m_kMap_dwID_kReserveTargetEffectShopSearch.erase(itor);
	}
#endif

//Find
	m_kMap_dwID_kReserveTargetEffect.clear();
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	m_kMap_dwTargetID_dwChrIDShopSearch.clear();
	m_kMap_dwID_kReserveTargetEffectShopSearch.clear();
#endif

//Find
	if (m_kMap_dwTargetID_dwChrID.end() != m_kMap_dwTargetID_dwChrID.find(dwID))
	{
		m_kMap_dwTargetID_dwChrID.erase(dwID);
	}
	
///Add
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
	if (m_kMap_dwID_kReserveTargetEffectShopSearch.end() != m_kMap_dwID_kReserveTargetEffectShopSearch.find(dwID))
		m_kMap_dwID_kReserveTargetEffectShopSearch.erase(dwID);
	if (m_kMap_dwTargetID_dwChrIDShopSearch.end() != m_kMap_dwTargetID_dwChrIDShopSearch.find(dwID))
		m_kMap_dwTargetID_dwChrIDShopSearch.erase(dwID);
#endif

///Add new funcs
#if defined(BL_PRIVATESHOP_SEARCH_SYSTEM)
void CPythonBackground::CreateShopSearchTargetEffect(DWORD dwID, DWORD dwChrVID)
{
	m_kMap_dwTargetID_dwChrIDShopSearch.emplace(dwID, dwChrVID);
}
void CPythonBackground::CreateShopSearchTargetEffect(DWORD dwID, long lx, long ly)
{
	if (m_kMap_dwTargetID_dwChrIDShopSearch.end() != m_kMap_dwTargetID_dwChrIDShopSearch.find(dwID))
		return;

	CMapOutdoor& rkMap = GetMapOutdoorRef();
	DWORD dwBaseX, dwBaseY;
	rkMap.GetBaseXY(&dwBaseX, &dwBaseY);

	const auto ilx = +static_cast<float>(lx - static_cast<decltype(lx)>(dwBaseX));
	const auto ily = -static_cast<float>(ly - static_cast<decltype(ly)>(dwBaseY));
	const auto fHeight = rkMap.GetHeight(ilx, ily);

	if (0.0f == fHeight) {
		SReserveTargetEffect ReserveTargetEffect{ static_cast<int>(ilx), static_cast<int>(ily) };
		m_kMap_dwID_kReserveTargetEffectShopSearch.emplace(dwID, ReserveTargetEffect);
		return;
	}

	CreateSpecialEffect(dwID, ilx, ily, fHeight, g_strShopSearchEffectName.c_str());
}
#endif
