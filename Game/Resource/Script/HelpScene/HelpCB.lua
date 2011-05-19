function HelpScene_CB(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	if selgrouptag == CCTAG_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag);
		
	elseif selgrouptag == CCTag_Menu_00 then
		return HelpScene_MainMenu(itemtag, eventtag, toptag, selgrouptag, selitemtag);
	end
end

function HelpScene_MainMenu(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	game.PopScene();
end