#Find
	def __init__(self, *args, **kwargs):
		ToolTip.__init__(self, *args, **kwargs)
		self.itemVnum = 0
		self.isShopItem = False
		
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			self.isPrivateSearchItem = False
			
#Find
		ToolTip.ClearToolTip(self)
		
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			self.isPrivateSearchItem = False
			
#Find
	def __AppendAttackGradeInfo(self):
		atkGrade = item.GetValue(1)
		self.AppendTextLine(localeInfo.TOOLTIP_ITEM_ATT_GRADE % atkGrade, self.GetChangeTextLineColor(atkGrade))
		
#Add	
	if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
		def SetPrivateSearchItem(self, slotIndex):
			itemVnum = shop.GetPrivateShopSelectItemVnum(slotIndex)

			if 0 == itemVnum:
				return

			self.ClearToolTip()
			self.isPrivateSearchItem = True
		
			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(shop.GetPrivateShopSelectItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(shop.GetPrivateShopSelectItemAttribute(slotIndex, i))
	
			self.AddItemData(itemVnum, metinSlot, attrSlot)
			
			# if app.ENABLE_CHANGE_LOOK_SYSTEM:
				# self.AppendChangeLookInfoPrivateShopWIndow(slotIndex)

		def __AppendPrivateSearchItemicon(self, itemVnum):
			itemImage = ui.ImageBox()
			itemImage.SetParent(self)
			itemImage.Show()
			item.SelectItem(itemVnum)
			itemImage.LoadImage(item.GetIconImageFileName())
			itemImage.SetPosition((self.toolTipWidth/2)-16, self.toolTipHeight)
			self.toolTipHeight += itemImage.GetHeight()
			self.childrenList.append(itemImage)
			self.ResizeToolTip()
			
#Find
		### Hair Preview Image ###
		if self.__IsHair(itemVnum):	
			self.__AppendHairIcon(itemVnum)
			
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			if self.isPrivateSearchItem:
				if not self.__IsHair(itemVnum):
					self.__AppendPrivateSearchItemicon(itemVnum)
					
#Find
		itemImage.SetPosition(itemImage.GetWidth()/2, self.toolTipHeight)
		
#Change
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			if self.isPrivateSearchItem:
				itemImage.SetPosition((self.toolTipWidth/2)-48, self.toolTipHeight)
			else:
				itemImage.SetPosition((self.toolTipWidth/2)-48, self.toolTipHeight)
		else:
			itemImage.SetPosition(itemImage.GetWidth()/2, self.toolTipHeight)