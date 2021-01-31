#Add
if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
	import uiPrivateShopSearch
	
#Find
		self.wndMall = wndMall
		
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			self.wndPrivateShopSearch = uiPrivateShopSearch.PrivateShopSeachWindow()
			
#Find
		self.wndCubeResult.SetItemToolTip(self.tooltipItem)
		
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			self.wndPrivateShopSearch.SetItemToolTip(self.tooltipItem)
			
#Find
		if self.wndItemSelect:
			self.wndItemSelect.Destroy()
			
#Add
		if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
			if self.wndPrivateShopSearch:
				self.wndPrivateShopSearch.Destroy()
				del self.wndPrivateShopSearch
				
#Find
	def SelectMouseButtonEvent(self, dir, event):
		self.wndTaskBar.SelectMouseButtonEvent(dir, event)
		
#Add
	if app.BL_PRIVATESHOP_SEARCH_SYSTEM:
		def OpenPShopSearchDialogCash(self):
			self.wndPrivateShopSearch.Open(1)
		def RefreshPShopSearchDialog(self):
			self.wndPrivateShopSearch.RefreshList()