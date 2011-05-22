function OnlineScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	if selgrouptag == CCTag_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	end
end