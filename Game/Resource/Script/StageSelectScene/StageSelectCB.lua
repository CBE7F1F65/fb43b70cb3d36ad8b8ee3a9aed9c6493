function StageSelectScene_CB(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	if selgrouptag == CCTAG_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag);
	end
end