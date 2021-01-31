import ui
import net
import app
import item
import chat
import grp
import uiCommon
import localeInfo
import shop
import player

from _weakref import proxy


class ActionTextSlot(ui.ImageBox):
    def __init__(self, parent, x, y):
        ui.ImageBox.__init__(self)
        self.SetParent(parent)
        self.SetPosition(x, y)
        self.LoadImage("d:/ymir work/ui/public/Parameter_Slot_00.sub")

        self.mouseReflector = MouseReflector(self)
        self.mouseReflector.SetSize(self.GetWidth(), self.GetHeight())

        self.Enable = True
        self.textLine = ui.MakeTextLine(self)
        self.event = lambda *arg: None
        self.arg = 0
        self.Show()

        self.mouseReflector.UpdateRect()

    def __del__(self):
        ui.ImageBox.__del__(self)

    def SetText(self, text):
        self.textLine.SetText(text)

    def SetEvent(self, event, arg):
        self.event = event
        self.arg = arg

    def Disable(self):
        self.Enable = False

    def OnMouseOverIn(self):
        if not self.Enable:
            return
        self.mouseReflector.Show()

    def OnMouseOverOut(self):
        if not self.Enable:
            return
        self.mouseReflector.Hide()

    def OnMouseLeftButtonDown(self):
        if not self.Enable:
            return
        self.mouseReflector.Down()

    def OnMouseLeftButtonUp(self):
        if not self.Enable:
            return
        self.mouseReflector.Up()
        self.event(self.arg)


class MouseReflector(ui.Window):
    def __init__(self, parent):
        ui.Window.__init__(self)
        self.SetParent(parent)
        self.AddFlag("not_pick")
        self.width = self.height = 0
        self.isDown = False

    def __del__(self):
        ui.Window.__del__(self)

    def Down(self):
        self.isDown = True

    def Up(self):
        self.isDown = False

    def OnRender(self):

        if self.isDown:
            grp.SetColor(ui.WHITE_COLOR)
        else:
            grp.SetColor(ui.HALF_WHITE_COLOR)

        x, y = self.GetGlobalPosition()
        grp.RenderBar(x+2, y+2, self.GetWidth()-4, self.GetHeight()-4)


class CheckBox(ui.ImageBox):
    def __init__(self, parent, x, y, event, filename="d:/ymir work/ui/privatesearch/private_checkboxImg.sub"):
        ui.ImageBox.__init__(self)
        self.SetParent(parent)
        self.SetPosition(x, y)
        self.LoadImage(filename)

        self.mouseReflector = MouseReflector(self)
        self.mouseReflector.SetSize(self.GetWidth(), self.GetHeight())

        image = ui.MakeImageBox(
            self, "d:/ymir work/ui/public/check_image.sub", 0, 0)
        image.AddFlag("not_pick")
        image.SetWindowHorizontalAlignCenter()
        image.SetWindowVerticalAlignCenter()
        image.Hide()
        self.Enable = True
        self.image = image
        self.event = event
        self.Show()

        self.mouseReflector.UpdateRect()

    def __del__(self):
        ui.ImageBox.__del__(self)

    def SetCheck(self, flag):
        if flag:
            self.image.Show()
        else:
            self.image.Hide()

    def Disable(self):
        self.Enable = False

    def OnMouseOverIn(self):
        if not self.Enable:
            return
        self.mouseReflector.Show()

    def OnMouseOverOut(self):
        if not self.Enable:
            return
        self.mouseReflector.Hide()

    def OnMouseLeftButtonDown(self):
        if not self.Enable:
            return
        self.mouseReflector.Down()

    def OnMouseLeftButtonUp(self):
        if not self.Enable:
            return
        self.mouseReflector.Up()
        self.event()


class PrivateShopSeachWindow(ui.ScriptWindow):
    MAX_LINE_COUNT = 10
    MAX_CHAR_LEVEL = 105
    CLICK_LIMIT_TIME = 3
    PAGEBUTTON_MAX_SIZE = 9
    PAGEBUTTON_NUMBER_SIZE = 5
    PAGEONE_MAX_SIZE = 50

    SPECIAL_TITLE_COLOR = 0xff4E3D30

    if app.ENABLE_WOLFMAN_CHARACTER:
        JOB_MAX_COUNT = 5
        JOB_NAME_DIC = {	0: localeInfo.JOB_WARRIOR,
                         1: localeInfo.JOB_ASSASSIN,
                         2: localeInfo.JOB_SURA,
                         3: localeInfo.JOB_SHAMAN,
                         4: localeInfo.JOB_WOLFMAN, }
    else:
        JOB_MAX_COUNT = 4
        JOB_NAME_DIC = {	0: localeInfo.JOB_WARRIOR,
                         1: localeInfo.JOB_ASSASSIN,
                         2: localeInfo.JOB_SURA,
                         3: localeInfo.JOB_SHAMAN, }

    WEAPON_MASK_SUBTYPE_DIC = {
        0:
        {
            item.WEAPON_SWORD: localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
            item.WEAPON_TWO_HANDED: localeInfo.CATEGORY_WEAPON_WEAPON_TWO_HANDED,
        },

        1:
        {
            item.WEAPON_SWORD: localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
            item.WEAPON_DAGGER: localeInfo.CATEGORY_WEAPON_WEAPON_DAGGER,
            item.WEAPON_BOW: localeInfo.CATEGORY_WEAPON_WEAPON_BOW,
            item.WEAPON_ARROW: localeInfo.CATEGORY_WEAPON_WEAPON_ARROW,
            # item.MASK_ITEM_SUBTYPE_WEAPON_WEAPON_QUIVER: localeInfo.CATEGORY_WEAPON_WEAPON_QUIVER,
        },

        2:
        {
            item.WEAPON_SWORD: localeInfo.CATEGORY_WEAPON_WEAPON_SWORD,
        },

        3:
        {
            item.WEAPON_BELL: localeInfo.CATEGORY_WEAPON_WEAPON_BELL,
            item.WEAPON_FAN: localeInfo.CATEGORY_WEAPON_WEAPON_FAN,
        },
    }
    if app.ENABLE_WOLFMAN_CHARACTER:
        WEAPON_MASK_SUBTYPE_DIC[4] = {
            item.WEAPON_CLAW: localeInfo.CATEGORY_WEAPON_WEAPON_CLAW
        }

    ARMOR_MASK_SUBTYPE_DIC = {
        item.ARMOR_BODY: localeInfo.CATEGORY_ARMOR_ARMOR_BODY,
        item.ARMOR_HEAD: localeInfo.CATEGORY_ARMOR_ARMOR_HEAD,
        item.ARMOR_SHIELD: localeInfo.CATEGORY_ARMOR_ARMOR_SHIELD,
        item.ARMOR_WRIST: localeInfo.CATEGORY_JEWELRY_ARMOR_WRIST,
        item.ARMOR_FOOTS: localeInfo.CATEGORY_JEWELRY_ARMOR_FOOTS,
        item.ARMOR_NECK: localeInfo.CATEGORY_JEWELRY_ARMOR_NECK,
        item.ARMOR_EAR: localeInfo.CATEGORY_JEWELRY_ARMOR_EAR,
    }

    COSTUMES_MASK_SUBTYPE_DIC = {
        item.COSTUME_TYPE_BODY:         localeInfo.CATEGORY_COSTUMES_COSTUME_BODY,
        item.COSTUME_TYPE_HAIR:         localeInfo.CATEGORY_COSTUMES_COSTUME_HAIR,
    }

    USE_MASK_SUBTYPE_DIC = {
        item.USE_POTION:                localeInfo.PRIVATESHOPSEARCH_POTION,
        item.USE_ABILITY_UP:            localeInfo.CATEGORY_POTION_ABILITY,
        item.USE_SPECIAL:               localeInfo.PRIVATESHOPSEARCH_USESPECIAL,
        item.USE_TREASURE_BOX:          localeInfo.PRIVATESHOPSEARCH_TREASUREBOX,
        item.USE_CLEAN_SOCKET:          localeInfo.PRIVATESHOPSEARCH_DETACHMENT,
    }

    DS_SUBTYPE_DIC = {
        item.DS_SLOT1:                  localeInfo.PRIVATESHOPSEARCH_DS_BLACK,
        item.DS_SLOT2:                  localeInfo.PRIVATESHOPSEARCH_DS_BLUE,
        item.DS_SLOT3:                  localeInfo.PRIVATESHOPSEARCH_DS_GREEN,
        item.DS_SLOT4:                  localeInfo.PRIVATESHOPSEARCH_DS_RED,
        item.DS_SLOT5:                  localeInfo.PRIVATESHOPSEARCH_DS_WHITE,
        item.DS_SLOT6:                  localeInfo.PRIVATESHOPSEARCH_DS_YELLOW,
    }

    ITEM_MASK_TYPE_DIC = {
        item.ITEM_TYPE_NONE:            localeInfo.PRIVATESHOPSEARCH_ALL,
        item.ITEM_TYPE_WEAPON:          localeInfo.CATEGORY_EQUIPMENT_WEAPON,
        item.ITEM_TYPE_ARMOR:           localeInfo.CATEGORY_EQUIPMENT_ARMOR,
        item.ITEM_TYPE_COSTUME:         localeInfo.CATEGORY_COSTUMES,
        item.ITEM_TYPE_SKILLBOOK:       localeInfo.PRIVATESHOPSEARCH_SKILLBOOK,
        item.ITEM_TYPE_SKILLFORGET:     localeInfo.PRIVATESHOPSEARCH_SKILLFORGET,
        item.ITEM_TYPE_USE:             localeInfo.CATEGORY_ETC,
        item.ITEM_TYPE_BELT:            localeInfo.CATEGORY_JEWELRY_ITEM_BELT,
        item.ITEM_TYPE_ROD:             localeInfo.CATEGORY_FISHING_PICK_FISHING_POLE,
        item.ITEM_TYPE_FISH:            localeInfo.CATEGORY_FISHING_PICK_FOOD,
        item.ITEM_TYPE_DS:              localeInfo.CATEGORY_DRAGON_STONE,
        item.ITEM_TYPE_METIN:           localeInfo.PRIVATESHOPSEARCH_METIN,
        item.ITEM_TYPE_BLEND:           localeInfo.PRIVATESHOPSEARCH_BLEND,
        item.ITEM_TYPE_POLYMORPH:       localeInfo.CATEGORY_ETC_POLYMORPH,
        item.ITEM_TYPE_MATERIAL:        localeInfo.CATEGORY_TUNING,
    }

    ITEM_MASK_MASK_SUBTYPE_DICS = {
        item.ITEM_TYPE_NONE:            {-1: localeInfo.PRIVATESHOPSEARCH_ALL},
        item.ITEM_TYPE_WEAPON:	        WEAPON_MASK_SUBTYPE_DIC,
        item.ITEM_TYPE_ARMOR:	        ARMOR_MASK_SUBTYPE_DIC,
        item.ITEM_TYPE_COSTUME:         COSTUMES_MASK_SUBTYPE_DIC,
        item.ITEM_TYPE_SKILLBOOK:       {-1: localeInfo.PRIVATESHOPSEARCH_SKILLBOOK},
        item.ITEM_TYPE_SKILLFORGET:     {-1: localeInfo.PRIVATESHOPSEARCH_SKILLFORGET},
        item.ITEM_TYPE_USE:             USE_MASK_SUBTYPE_DIC,
        item.ITEM_TYPE_BELT:            {-1: localeInfo.PRIVATESHOPSEARCH_BELT},
        item.ITEM_TYPE_ROD:             {-1: localeInfo.CATEGORY_FISHING_PICK_FISHING_POLE},
        item.ITEM_TYPE_FISH:            {-1: localeInfo.CATEGORY_FISHING_PICK_FOOD},
        item.ITEM_TYPE_DS:              DS_SUBTYPE_DIC,
        item.ITEM_TYPE_METIN:           {-1: localeInfo.PRIVATESHOPSEARCH_METIN},
        item.ITEM_TYPE_BLEND:           {-1: localeInfo.PRIVATESHOPSEARCH_BLEND},
        item.ITEM_TYPE_POLYMORPH:       {-1: localeInfo.CATEGORY_ETC_POLYMORPH},
        item.ITEM_TYPE_MATERIAL:        {-1: localeInfo.CATEGORY_TUNING_RESOURCE},
    }

    def __init__(self):
        ui.ScriptWindow.__init__(self)
        self.isloded = 0
        self.ItemNameValue = None
        self.minlevelvalue = 0
        self.maxlevelvalue = 0
        self.minrefinevalue = 0
        self.maxrefinevalue = 0
        self.mingoldvalue = 0
        self.maxgoldvalue = 0
        self.buybutton = None
        self.searchbutton = None
        self.listslotcount = 0
        self.selectitemRealindex = -1
        self.selectitemindex = -1
        self.SerchItemSlotList = {}
        self.ItemSlotButtonList = {}
        self.pagebuttonList = {}

        self.saveitemMasktypeselectnumber = item.ITEM_TYPE_WEAPON

        self.savejobselectnumber = 0
        self.saveitemMasksubtypeselectnumber = 0
        self.searchclicktime = 0.0
        self.buyclicktime = 0.0
        self.nowpagenumber = 1
        self.pluspagenumber = 0
        self.pagecount = 0
        self.bigpagecount = 1
        self.iscashitem = 0
        self.popup = None

        if app.ENABLE_CHEQUE_SYSTEM:
            self.minchequevalue = 0
            self.maxchequevalue = 0

    def __del__(self):
        self.ItemNameValue = None
        self.buybutton = None
        self.searchbutton = None
        self.popup = None
        self.SerchItemSlotList = {}
        self.ItemSlotButtonList = {}
        self.pagebuttonList = {}
        ui.ScriptWindow.__del__(self)

    def __LoadWindow(self):
        try:
            pyScrLoader = ui.PythonScriptLoader()
            pyScrLoader.LoadScriptFile(
                self, "UIScript/PrivateShopSearchDialog.py")
        except:
            import exception
            exception.Abort(
                "PrivateShopSeachWindow.__LoadWindow.UIScript/PrivateShopSearchDialog.py")

        try:
            self.GetChild("board").SetCloseEvent(ui.__mem_func__(self.Close))
            self.searchbutton = self.GetChild("SearchButton")
            self.searchbutton.SetEvent(ui.__mem_func__(self.Search))
            self.buybutton = self.GetChild("BuyButton")
            self.buybutton.SetEvent(ui.__mem_func__(self.Buy))

            if localeInfo.IsARABIC():
                self.GetChild("leftcenterImg").LeftRightReverse()
                self.GetChild("rightcenterImg").LeftRightReverse()
                self.GetChild("LeftTop").LeftRightReverse()
                self.GetChild("RightTop").LeftRightReverse()
                self.GetChild("LeftBottom").LeftRightReverse()
                self.GetChild("RightBottom").LeftRightReverse()

                self.topcenterimg = self.GetChild("topcenterImg")
                self.topcenterimg.SetPosition(
                    self.GetWidth() - (self.topcenterimg.GetWidth()*2)+10, 36)

                self.bottomcenterImg = self.GetChild("bottomcenterImg")
                self.bottomcenterImg.SetPosition(
                    self.GetWidth() - (self.bottomcenterImg.GetWidth()*2)+10, 320)

                self.centerImg = self.GetChild("centerImg")
                self.centerImg.SetPosition(
                    self.GetWidth() - (self.centerImg.GetWidth()*2)+10, 52)

            self.ItemNameValue = self.GetChild("ItemNameValue")
            self.ItemNameValue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.minlevelvalue = self.GetChild("minLevelValue")
            self.minlevelvalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.maxlevelvalue = self.GetChild("maxLevelValue")
            self.maxlevelvalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.minrefinevalue = self.GetChild("minrefineValue")
            self.minrefinevalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.maxrefinevalue = self.GetChild("maxrefineValue")
            self.maxrefinevalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.mingoldvalue = self.GetChild("GoldminValue")
            self.mingoldvalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            self.maxgoldvalue = self.GetChild("GoldmaxValue")
            self.maxgoldvalue.SetEscapeEvent(ui.__mem_func__(self.Close))
            if app.ENABLE_CHEQUE_SYSTEM:
                self.minchequevalue = self.GetChild("ChequeminValue")
                self.minchequevalue.SetEscapeEvent(ui.__mem_func__(self.Close))
                self.maxchequevalue = self.GetChild("ChequemaxValue")
                self.maxchequevalue.SetEscapeEvent(ui.__mem_func__(self.Close))

            self.prev_button = self.GetChild("prev_button")
            self.prev_button.SetEvent(ui.__mem_func__(self.prevbutton))

            self.next_button = self.GetChild("next_button")
            self.next_button.SetEvent(ui.__mem_func__(self.nextbutton))

            self.first_prev_button = self.GetChild("first_prev_button")
            self.first_prev_button.SetEvent(
                ui.__mem_func__(self.firstprevbutton))

            self.last_next_button = self.GetChild("last_next_button")
            self.last_next_button.SetEvent(
                ui.__mem_func__(self.lastnextbutton))

            if localeInfo.IsARABIC():
                self.prev_button.LeftRightReverse()
                self.next_button.LeftRightReverse()
                self.first_prev_button.LeftRightReverse()
                self.last_next_button.LeftRightReverse()

            self.page1_button = self.GetChild("page1_button")
            self.page1_button.SetEvent(ui.__mem_func__(self.Pagebutton), 1)

            self.page2_button = self.GetChild("page2_button")
            self.page2_button.SetEvent(ui.__mem_func__(self.Pagebutton), 2)

            self.page3_button = self.GetChild("page3_button")
            self.page3_button.SetEvent(ui.__mem_func__(self.Pagebutton), 3)

            self.page4_button = self.GetChild("page4_button")
            self.page4_button.SetEvent(ui.__mem_func__(self.Pagebutton), 4)

            self.page5_button = self.GetChild("page5_button")
            self.page5_button.SetEvent(ui.__mem_func__(self.Pagebutton), 5)

            TemppageSlotButton = []
            TemppageSlotButton.append(self.page1_button)
            TemppageSlotButton.append(self.page2_button)
            TemppageSlotButton.append(self.page3_button)
            TemppageSlotButton.append(self.page4_button)
            TemppageSlotButton.append(self.page5_button)
            TemppageSlotButton.append(self.prev_button)
            TemppageSlotButton.append(self.next_button)
            TemppageSlotButton.append(self.first_prev_button)
            TemppageSlotButton.append(self.last_next_button)
            self.pagebuttonList[0] = TemppageSlotButton

            self.HidePageButton()

        except:
            import exception
            exception.Abort(
                "PrivateShopSeachWindow.__LoadWindow.PrivateShopSearchDialog")

    def Open(self, iscash):
        if self.isloded == 0:
            self.isloded = 1
            self.__LoadWindow()
            self.SetCenterPosition()
            self.SetTop()
            self.__MakeResultSlot()
            self.iscashitem = 1
            if not iscash:
                self.iscashitem = 0
                self.buybutton.Disable()
                self.buybutton.Down()
            ui.ScriptWindow.Show(self)

    def Close(self):
        self.Hide()
        self.isloded = 0
        self.selectitemRealindex = -1
        self.selectitemindex = -1
        self.savejobselectnumber = 0

        self.saveitemMasktypeselectnumber = item.ITEM_TYPE_WEAPON

        self.saveitemMasksubtypeselectnumber = 0
        if self.popup:
            self.popup.Close()
            self.popup = None
        self.ItemNameValue.KillFocus()

        net.ClosePrivateShopSearchWindow()

    def Destroy(self):
        self.Hide()
        self.ClearDictionary()

    def OnPressEscapeKey(self):
        self.Close()
        return True

    def __MakeResultSlot(self):
        yPos = 0
        for i in range(0, self.MAX_LINE_COUNT):
            yPos = 63 + i * 25

            itemSlotImage = ui.MakeImageBox(
                self, "d:/ymir work/ui/public/parameter_slot_04.sub", 150+30, yPos)
            itemSlotImage.SetAlpha(0)
            itemNameSlot = ui.MakeTextLine(itemSlotImage)
            self.Children.append(itemSlotImage)
            self.Children.append(itemNameSlot)

            SellerNameImage = ui.MakeImageBox(
                self, "d:/ymir work/ui/public/parameter_slot_04.sub", 140+125+38, yPos)
            SellerNameImage.SetAlpha(0)
            SellerNameSlot = ui.MakeTextLine(SellerNameImage)
            self.Children.append(SellerNameImage)
            self.Children.append(SellerNameSlot)

            CountSlotImage = ui.MakeImageBox(
                self, "d:/ymir work/ui/public/Parameter_Slot_01.sub", 140+125+120+40, yPos)
            CountSlotImage.SetAlpha(0)
            CountSlot = ui.MakeTextLine(CountSlotImage)
            self.Children.append(CountSlotImage)
            self.Children.append(CountSlot)

            if app.ENABLE_CHEQUE_SYSTEM:

                PriceSlotImage = ui.MakeImageBox(
                    self, "d:/ymir work/ui/public/Parameter_Slot_03.sub", 556, yPos)
                PriceSlotImage.SetAlpha(0)
                PriceSlot = ui.MakeTextLine(PriceSlotImage)
                self.Children.append(PriceSlotImage)
                self.Children.append(PriceSlot)

                ChequeSlotImage = ui.MakeImageBox(
                    self, "d:/ymir work/ui/public/Parameter_Slot_01.sub", 490, yPos)
                ChequeSlotImage.SetAlpha(0)
                ChequeSlot = ui.MakeTextLine(ChequeSlotImage)
                self.Children.append(ChequeSlotImage)
                self.Children.append(ChequeSlot)
            else:
                PriceSlotImage = ui.MakeImageBox(
                    self, "d:/ymir work/ui/public/Parameter_Slot_03.sub", 140+125+85+90+40, yPos)
                PriceSlotImage.SetAlpha(0)
                PriceSlot = ui.MakeTextLine(PriceSlotImage)
                self.Children.append(PriceSlotImage)
                self.Children.append(PriceSlot)

            if localeInfo.IsARABIC():
                itemSlotImage.SetPosition(
                    self.GetWidth() - (140+30) - itemSlotImage.GetWidth() - 3, yPos)
                SellerNameImage.SetPosition(
                    self.GetWidth() - (140+125+38) - SellerNameImage.GetWidth() - 3, yPos)
                CountSlotImage.SetPosition(
                    self.GetWidth() - (140+125+120+40) - CountSlotImage.GetWidth() - 3, yPos)

                if app.ENABLE_CHEQUE_SYSTEM:
                    ChequeSlotImage.SetPosition(
                        self.GetWidth() - (490) - ChequeSlotImage.GetWidth() - 3, yPos)
                    PriceSlotImage.SetPosition(
                        self.GetWidth() - (556) - PriceSlotImage.GetWidth() - 3, yPos)
                else:
                    PriceSlotImage.SetPosition(
                        self.GetWidth() - (140+125+85+90+40) - PriceSlotImage.GetWidth() - 3, yPos)

            anameslotlist = []
            anameslotlist.append(itemNameSlot)
            anameslotlist.append(SellerNameSlot)
            anameslotlist.append(CountSlot)
            anameslotlist.append(PriceSlot)
            if app.ENABLE_CHEQUE_SYSTEM:
                anameslotlist.append(ChequeSlot)

            self.SerchItemSlotList[i] = anameslotlist

            if app.ENABLE_CHEQUE_SYSTEM:
                itemSlotButtonImage = ui.MakeButton(
                    self, 138, yPos, "", "d:/ymir work/ui/", "tab_01.tga", "tab_02.tga", "tab_02.tga")
            else:
                itemSlotButtonImage = ui.MakeButton(
                    self, 138, yPos, "", "d:/ymir work/ui/", "bl_tab_01.tga", "bl_tab_02.tga", "bl_tab_02.tga")
            itemSlotButtonImage.ShowToolTip = lambda slotIndex = i: self.OverInToolTip(
                slotIndex)
            itemSlotButtonImage.HideToolTip = lambda slotIndex = i: self.OverOutToolTip(
                slotIndex)
            itemSlotButtonImage.Hide()
            itemSlotButtonImage.SetEvent(ui.__mem_func__(self.__SelectItem), i)
            self.Children.append(itemSlotButtonImage)

            if localeInfo.IsARABIC():
                itemSlotButtonImage.LeftRightReverse()
                itemSlotButtonImage.SetPosition(
                    self.GetWidth() - 138 - itemSlotButtonImage.GetWidth(), yPos)

            TempitemSlotButtonImage = []
            TempitemSlotButtonImage.append(itemSlotButtonImage)
            self.ItemSlotButtonList[i] = TempitemSlotButtonImage

        self.itemMasksubtypeselectslot = ui.ComboBoxImage(
            self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 115)
        self.itemMasksubtypeselectslot.SetEvent(lambda Masksubtypenumber, argSelf=proxy(
            self): argSelf.OnChangeItemSubTypeSlot(Masksubtypenumber))
        for i in self.WEAPON_MASK_SUBTYPE_DIC[0]:
            self.itemMasksubtypeselectslot.InsertItem(
                i, self.WEAPON_MASK_SUBTYPE_DIC[0][i])
        self.itemMasksubtypeselectslot.SetCurrentItem(
            self.WEAPON_MASK_SUBTYPE_DIC[0][0])
        self.itemMasksubtypeselectslot.Show()
        self.Children.append(self.itemMasksubtypeselectslot)

        if localeInfo.IsARABIC():
            self.itemMasksubtypeselectslot.SetPosition(
                self.GetWidth() - 12 - self.itemMasksubtypeselectslot.GetWidth() - 3, 115)

        self.itemMasktypeselectslot = ui.ComboBoxImage(
            self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 95)
        self.itemMasktypeselectslot.SetEvent(lambda Masktypenumber, argSelf=proxy(
            self): argSelf.OnChangeItemTypeSlot(Masktypenumber))

        for index, itemtypedic in self.ITEM_MASK_TYPE_DIC.items():
            self.itemMasktypeselectslot.InsertItem(
                index, self.ITEM_MASK_TYPE_DIC[index])
        self.itemMasktypeselectslot.SetCurrentItem(
            self.ITEM_MASK_TYPE_DIC[item.ITEM_TYPE_WEAPON])
        self.itemMasktypeselectslot.Show()
        self.Children.append(self.itemMasktypeselectslot)

        if localeInfo.IsARABIC():
            self.itemMasktypeselectslot.SetPosition(
                self.GetWidth() - 12 - self.itemMasktypeselectslot.GetWidth() - 3, 95)

        self.jobselectslot = ui.ComboBoxImage(
            self, "d:/ymir work/ui/privatesearch/private_leftSlotImg.sub", 12, 55)
        self.jobselectslot.SetEvent(lambda jobnumber, argSelf=proxy(
            self): argSelf.OnChangeJobSlot(jobnumber))

        for i in range(0, self.JOB_MAX_COUNT):
            self.jobselectslot.InsertItem(i, self.JOB_NAME_DIC[i])
        self.jobselectslot.SetCurrentItem(self.JOB_NAME_DIC[0])
        self.jobselectslot.Show()
        self.Children.append(self.jobselectslot)

        if localeInfo.IsARABIC():
            self.jobselectslot.SetPosition(
                self.GetWidth() - 12 - self.jobselectslot.GetWidth() - 3, 55)

    def RefreshList(self):
        page = shop.GetPrivateShopSearchResultPage()
        maxcount = shop.GetPrivateShopSearchResultMaxCount()

        for line, nameSlotList in self.SerchItemSlotList.items():
            if app.ENABLE_CHEQUE_SYSTEM:
                itemname, sellername, count, price, cheque = shop.GetPrivateShopSearchResult(
                    line)
                if "" == itemname:
                    nameSlotList[0].SetText("")
                    nameSlotList[1].SetText("")
                    nameSlotList[2].SetText("")
                    nameSlotList[3].SetText("")
                    nameSlotList[4].SetText("")
                    self.ItemSlotButtonList[line][0].Hide()
                else:
                    nameSlotList[0].SetText(itemname)
                    nameSlotList[1].SetText(sellername)
                    nameSlotList[2].SetText(str(count))
                    nameSlotList[3].SetText(self.NumberToMoneyString(price))
                    nameSlotList[4].SetText(str(cheque))
                    self.ItemSlotButtonList[line][0].Show()
            else:
                itemname, sellername, count, price = shop.GetPrivateShopSearchResult(
                    line)
                if "" == itemname:
                    nameSlotList[0].SetText("")
                    nameSlotList[1].SetText("")
                    nameSlotList[2].SetText("")
                    nameSlotList[3].SetText("")
                    self.ItemSlotButtonList[line][0].Hide()
                else:
                    nameSlotList[0].SetText(itemname)
                    nameSlotList[1].SetText(sellername)
                    nameSlotList[2].SetText(str(count))
                    nameSlotList[3].SetText(self.NumberToMoneyString(price))
                    self.ItemSlotButtonList[line][0].Show()

        self.ShowPageButton(maxcount, page)

        if self.bigpagecount == 1:
            self.prev_button.Disable()
            self.prev_button.Down()

        else:
            self.prev_button.Enable()

        if self.bigpagecount - 1 <= 1:
            self.first_prev_button.Disable()
            self.first_prev_button.Down()

        else:
            self.first_prev_button.Enable()

        if maxcount <= self.bigpagecount * self.PAGEONE_MAX_SIZE:
            self.next_button.Disable()
            self.next_button.Down()

        else:
            self.next_button.Enable()

        if maxcount <= (self.bigpagecount+1) * self.PAGEONE_MAX_SIZE:
            self.last_next_button.Disable()
            self.last_next_button.Down()
        else:
            self.last_next_button.Enable()

    def NumberToMoneyString(self, n):
        if n <= 0:
            return "0"

        return "%s %s" % ('.'.join([i-3 < 0 and str(n)[:i] or str(n)[i-3:i] for i in range(len(str(n)) % 3, len(str(n))+1, 3) if i]), "")

    def Pagebutton(self, number):
        if number == self.nowpagenumber:
            return
        if self.bigpagecount > 1:
            if number == self.nowpagenumber - (self.bigpagecount-1) * 5:
                return

        self.clearPagebuttoncolor()
        self.pagebuttonList[0][number-1].SetTextColor(self.SPECIAL_TITLE_COLOR)
        self.pagebuttonList[0][number-1].Down()
        self.pagebuttonList[0][number-1].Disable()
        self.nowpagenumber = int(self.pagebuttonList[0][number-1].GetText())
        net.SendPrivateShopSearchInfoSub(self.nowpagenumber)
        self.clearEffectEtc()

    def firstprevbutton(self):

        if self.bigpagecount - 1 <= 1:
            return

        self.clearPagebuttoncolor()
        self.bigpagecount = 1
        for line, pagebutton in self.pagebuttonList.items():
            for i in range(5):
                pagebutton[i].SetText(str(i+1))

        self.nowpagenumber = int(self.pagebuttonList[0][0].GetText())
        self.pagebuttonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
        self.pagebuttonList[0][0].Down()
        self.pagebuttonList[0][0].Disable()
        net.SendPrivateShopSearchInfoSub(self.nowpagenumber)
        self.clearEffectEtc()

    def lastnextbutton(self):
        maxsize = shop.GetPrivateShopSearchResultMaxCount()
        self.pagecount = maxsize / 10
        self.HidePageButton()
        self.clearPagebuttoncolor()

        if self.pagecount % 5 == 0:
            self.bigpagecount = (self.pagecount/5)
        else:
            self.bigpagecount = (self.pagecount/5) + 1

        pagenumber = 5 * (self.pagecount/5)
        if pagenumber == self.pagecount:
            pagenumber -= 5
        for line, pagebutton in self.pagebuttonList.items():
            for i in range(5):
                pagebutton[i].SetText(str(i+pagenumber+1))

        self.nowpagenumber = self.pagecount
        net.SendPrivateShopSearchInfoSub(self.nowpagenumber)
        self.clearEffectEtc()

    def prevbutton(self):
        if self.bigpagecount == 1:
            return

        self.clearPagebuttoncolor()
        self.bigpagecount -= 1

        for line, pagebutton in self.pagebuttonList.items():
            for i in range(5):
                pagenumber = int(pagebutton[i].GetText()) - 5
                pagebutton[i].SetText(str(pagenumber))

        self.nowpagenumber = int(self.pagebuttonList[0][0].GetText())
        self.pagebuttonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
        self.pagebuttonList[0][0].Down()
        self.pagebuttonList[0][0].Disable()
        net.SendPrivateShopSearchInfoSub(self.nowpagenumber)
        self.clearEffectEtc()

    def nextbutton(self):
        maxitemcount = shop.GetPrivateShopSearchResultMaxCount()
        if maxitemcount < self.bigpagecount * self.PAGEONE_MAX_SIZE:
            return

        for line, pagebutton in self.pagebuttonList.items():
            for i in range(5):
                pagenumber = int(pagebutton[i].GetText()) + 5
                pagebutton[i].SetText(str(pagenumber))

        self.nowpagenumber = int(self.pagebuttonList[0][0].GetText())
        self.bigpagecount += 1
        self.HidePageButton()
        self.clearPagebuttoncolor()
        self.pagebuttonList[0][0].SetTextColor(self.SPECIAL_TITLE_COLOR)
        self.pagebuttonList[0][0].Down()
        self.pagebuttonList[0][0].Disable()
        net.SendPrivateShopSearchInfoSub(self.nowpagenumber)
        self.clearEffectEtc()

    def clearPagebuttoncolor(self):
        for line, pagebutton in self.pagebuttonList.items():
            for i in range(0, self.PAGEBUTTON_NUMBER_SIZE):
                pagebutton[i].SetTextColor(0xffffffff)
                pagebutton[i].SetUp()
                pagebutton[i].Enable()

    def HidePageButton(self):
        for line, pagebutton in self.pagebuttonList.items():
            for i in range(0, self.PAGEBUTTON_MAX_SIZE):
                pagebutton[i].Hide()

    def ShowPageButton(self, maxsize, page):

        if self.bigpagecount > 1:
            maxsize = maxsize - ((self.bigpagecount-1) * self.PAGEONE_MAX_SIZE)
            page = page - (self.bigpagecount-1) * 5

        self.pagecount = maxsize / 10

        if not maxsize % 10 == 0:
            self.pagecount = self.pagecount + 1

        if self.pagecount > 5:
            self.pagecount = 5

        for line, pagebutton in self.pagebuttonList.items():
            for i in range(self.pagecount):
                pagebutton[i].Show()

        self.pagebuttonList[0][5].Show()
        self.pagebuttonList[0][6].Show()
        self.pagebuttonList[0][7].Show()
        self.pagebuttonList[0][8].Show()

        self.clearPagebuttoncolor()
        self.pagebuttonList[0][page-1].SetTextColor(self.SPECIAL_TITLE_COLOR)
        self.pagebuttonList[0][page-1].Down()
        self.pagebuttonList[0][page-1].Disable()
        self.nowpagenumber = page

    def OnUpdate(self):

        if (app.GetTime() - self.searchclicktime) > self.CLICK_LIMIT_TIME and self.searchbutton.IsDIsable() == 0:
            self.searchbutton.Enable()

        if (app.GetTime() - self.buyclicktime) > self.CLICK_LIMIT_TIME and self.buybutton.IsDIsable() == 0 and self.iscashitem == 1:
            self.buybutton.Enable()

    def Search(self):

        privatesearchitemcount_6004 = player.GetItemCountByVnum(60004)
        privatesearchitemcount_6005 = player.GetItemCountByVnum(60005)

        if privatesearchitemcount_6004 <= 0 and privatesearchitemcount_6005 <= 0:
            chat.AppendChat(chat.CHAT_TYPE_INFO,
                            localeInfo.PRIVATESHOPSEARCH_NEED_ITEM_FIND)
            self.Close()
            return

        self.searchclicktime = app.GetTime()
        self.searchbutton.Disable()
        self.searchbutton.SetUp()

        job = self.savejobselectnumber
        Masktype = self.saveitemMasktypeselectnumber
        Masksub = self.saveitemMasksubtypeselectnumber

        if len(self.minrefinevalue.GetText()) <= 0:
            self.minrefinevalue.SetText("0")
        if len(self.maxrefinevalue.GetText()) <= 0:
            self.maxrefinevalue.SetText("9")

        if len(self.minlevelvalue.GetText()) <= 0:
            self.minlevelvalue.SetText("1")
        if len(self.maxlevelvalue.GetText()) <= 0:
            self.maxlevelvalue.SetText("105")

        if len(self.mingoldvalue.GetText()) <= 0:
            self.mingoldvalue.SetText("1")
        if len(self.maxgoldvalue.GetText()) <= 0:
            self.maxgoldvalue.SetText("900000000")

        minrefine = int(self.minrefinevalue.GetText())
        maxrefine = int(self.maxrefinevalue.GetText())
        minlevel = int(self.minlevelvalue.GetText())
        if minlevel == 1:
            minlevel = 0

        maxlevel = int(self.maxlevelvalue.GetText())
        mingold = int(self.mingoldvalue.GetText())
        maxgold = int(self.maxgoldvalue.GetText())
        itemname = self.ItemNameValue.GetText()

        GOLD_MAX = 2000000000
        if mingold >= GOLD_MAX:
            mingold = GOLD_MAX - 1
            self.mingoldvalue.SetText(str(mingold))

        if maxgold >= GOLD_MAX:
            maxgold = GOLD_MAX - 1
            self.maxgoldvalue.SetText(str(maxgold))

        if app.ENABLE_CHEQUE_SYSTEM:
            CHEQUE_MAX = 999
            if len(self.minchequevalue.GetText()) <= 0:
                self.minchequevalue.SetText(str(0))
            if len(self.maxchequevalue.GetText()) <= 0:
                self.maxchequevalue.SetText(str(CHEQUE_MAX))

            mincheque = int(self.minchequevalue.GetText())
            maxcheque = int(self.maxchequevalue.GetText())
            if mincheque > CHEQUE_MAX:
                mincheque = CHEQUE_MAX
                self.minchequevalue.SetText(str(mincheque))

            if maxcheque > CHEQUE_MAX:
                maxcheque = CHEQUE_MAX
                self.maxchequevalue.SetText(str(maxcheque))

            net.SendPrivateShopSearchInfo(job, Masktype, Masksub, minrefine, maxrefine,
                                          minlevel, maxlevel, mingold, maxgold, itemname, mincheque, maxcheque)
        else:
            net.SendPrivateShopSearchInfo(
                job, Masktype, Masksub, minrefine, maxrefine, minlevel, maxlevel, mingold, maxgold, itemname)

        for line, nameSlotList in self.SerchItemSlotList.items():
            nameSlotList[0].SetText("")
            nameSlotList[1].SetText("")
            nameSlotList[2].SetText("")
            nameSlotList[3].SetText("")
            if app.ENABLE_CHEQUE_SYSTEM:
                nameSlotList[4].SetText("")

            self.ItemSlotButtonList[line][0].Hide()

        self.clearEffectEtc()
        self.HidePageButton()
        self.bigpagecount = 1
        for line, pagebutton in self.pagebuttonList.items():
            for i in range(5):
                pagenumber = int(pagebutton[i].GetText()) - 5
                pagebutton[i].SetText(str(i+1))

    def Buy(self):
        if self.selectitemRealindex == -1:
            chat.AppendChat(chat.CHAT_TYPE_INFO,
                            localeInfo.PRIVATESHOPSEARCH_SELECTITEM)
            return

        self.buyclicktime = app.GetTime()
        self.buybutton.Disable()
        self.buybutton.SetUp()

        popup = uiCommon.QuestionDialog()
        popup.SetText(localeInfo.PRIVATESHOPSEARCH_BUYTIME)
        popup.SetAcceptEvent(self.OnBuyAcceptEvent)
        popup.SetCancelEvent(self.OnBuyCloseEvent)
        popup.Open()
        self.popup = popup

    def OnBuyAcceptEvent(self):
        if self.selectitemRealindex == -1:
            chat.AppendChat(chat.CHAT_TYPE_INFO,
                            localeInfo.PRIVATESHOPSEARCH_SELECTITEM)
            return
        net.SendPrivateShopSerchBuyItem(self.selectitemRealindex)
        self.clearEffectEtc()
        self.Search()
        self.popup.Close()
        self.popup = None

    def OnBuyCloseEvent(self):
        self.popup.Close()
        self.popup = None
        self.clearEffectEtc()

    def __SelectItem(self, arg):
        self.selectitemRealindex = arg
        self.selectitemindex = arg
        self.__SelectItemSlotButtonList(arg)

    def __ClearItemSlotButtonList(self):
        for line, ItemSlotButtonList in self.ItemSlotButtonList.items():
            ItemSlotButtonList[0].SetUp()

    def __SelectItemSlotButtonList(self, index):
        for line, ItemSlotButtonList in self.ItemSlotButtonList.items():
            if index != line:
                ItemSlotButtonList[0].SetUp()
            else:
                ItemSlotButtonList[0].Down()

    def SetItemToolTip(self, tooltip):
        self.tooltipitem = tooltip

    def __ShowToolTip(self, slotIndex):
        if self.tooltipitem:
            self.tooltipitem.SetPrivateSearchItem(slotIndex)

    def OverInToolTip(self, slotIndex):
        self.__ShowToolTip(slotIndex)

    def OverOutToolTip(self, slotIndex):
        if self.tooltipitem:
            self.tooltipitem.HideToolTip()

        if self.selectitemindex == slotIndex:
            self.ItemSlotButtonList[slotIndex][0].Down()

    def OnChangeItemSubTypeSlot(self, Masksubtypenumber):

        if self.saveitemMasktypeselectnumber == item.ITEM_TYPE_WEAPON:
            self.itemMasksubtypeselectslot.SetCurrentItem(
                self.WEAPON_MASK_SUBTYPE_DIC[self.savejobselectnumber][Masksubtypenumber])
        else:
            self.itemMasksubtypeselectslot.SetCurrentItem(
                self.ITEM_MASK_MASK_SUBTYPE_DICS[self.saveitemMasktypeselectnumber][Masksubtypenumber])
        self.saveitemMasksubtypeselectnumber = Masksubtypenumber

    def OnChangeJobSlot(self, jobnumber):
        self.jobselectslot.SetCurrentItem(self.JOB_NAME_DIC[jobnumber])
        if jobnumber != self.savejobselectnumber:

            if self.saveitemMasktypeselectnumber == item.ITEM_TYPE_WEAPON:
                self.itemMasksubtypeselectslot.ClearItem()
                Masksubtype = 0
                savefirst = 0
                for i in self.WEAPON_MASK_SUBTYPE_DIC[jobnumber]:
                    self.itemMasksubtypeselectslot.InsertItem(
                        i, self.WEAPON_MASK_SUBTYPE_DIC[jobnumber][i])
                    if Masksubtype == 0:
                        if savefirst == 0:
                            Masksubtype = i
                            savefirst = 1
                self.itemMasksubtypeselectslot.SetCurrentItem(
                    self.WEAPON_MASK_SUBTYPE_DIC[jobnumber][Masksubtype])
                self.saveitemMasksubtypeselectnumber = Masksubtype
            self.savejobselectnumber = jobnumber

    def OnChangeItemTypeSlot(self, Masktypenumber):
        self.itemMasktypeselectslot.SetCurrentItem(
            self.ITEM_MASK_TYPE_DIC[Masktypenumber])
        if Masktypenumber != self.saveitemMasktypeselectnumber:
            self.itemMasksubtypeselectslot.ClearItem()

            if Masktypenumber == item.ITEM_TYPE_WEAPON:
                Masksubtype = 0
                savefirst = 0
                for i in self.WEAPON_MASK_SUBTYPE_DIC[self.savejobselectnumber]:
                    self.itemMasksubtypeselectslot.InsertItem(
                        i, self.WEAPON_MASK_SUBTYPE_DIC[self.savejobselectnumber][i])
                    if Masksubtype == 0:
                        if savefirst == 0:
                            Masksubtype = i
                            savefirst = 1
                self.itemMasksubtypeselectslot.SetCurrentItem(
                    self.WEAPON_MASK_SUBTYPE_DIC[self.savejobselectnumber][Masksubtype])
                self.saveitemMasksubtypeselectnumber = Masksubtype
            else:
                Masksubtype = 0
                savefirst = 0
                for i in self.ITEM_MASK_MASK_SUBTYPE_DICS[Masktypenumber]:
                    self.itemMasksubtypeselectslot.InsertItem(
                        i, self.ITEM_MASK_MASK_SUBTYPE_DICS[Masktypenumber][i])
                    if Masksubtype == 0:
                        if savefirst == 0:
                            Masksubtype = i
                            savefirst = 1
                self.itemMasksubtypeselectslot.SetCurrentItem(
                    self.ITEM_MASK_MASK_SUBTYPE_DICS[Masktypenumber][Masksubtype])
                self.saveitemMasksubtypeselectnumber = Masksubtype
            self.saveitemMasktypeselectnumber = Masktypenumber

    def clearEffectEtc(self):
        self.__ClearItemSlotButtonList()
        self.selectitemRealindex = -1
        self.selectitemindex = -1

    def OnTop(self):
        self.ItemNameValue.SetFocus()
