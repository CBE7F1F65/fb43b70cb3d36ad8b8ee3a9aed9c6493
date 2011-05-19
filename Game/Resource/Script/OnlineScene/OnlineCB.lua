function OnlineScene_CB(itemtag, eventtag, toptag, sublayertag, selgrouptag, selitemtag)
	if selgrouptag == CCTag_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag);
	end
end