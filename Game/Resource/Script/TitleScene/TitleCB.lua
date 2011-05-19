function TitleScene_CB(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	if selgrouptag == CCTAG_Debug_ReloadMenu then
		return Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag);
	
	
	elseif selgrouptag == CCTag_Menu_00 then
		return TitleScene_MainMenu(itemtag, eventtag, toptag, selgrouptag, selitemtag);
	elseif selgrouptag == CCTag_Menu_14 then
		return TitleScene_ReplaceScene(itemtag, eventtag, toptag, selgrouptag, selitemtag);
	end
end

function TitleScene_MainMenu(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	
	if selitemtag == 5 then
		game.PushScene(ktag_HelpSceneLayer, g_SceneTransTime);
		return;
	end
	
	local grouptag = toptag+selgrouptag;
	local menus = {};
	local spTitleMenus = {};
	local spTitleMenusSelected = {};
	local xmove = 400;
	for i=0, 4 do
		local spritealphaaction = {};
	
		menus[i+1] = game.GetNode({grouptag, grouptag+i+1});
		spTitleMenus[i+1] = game.GetNode({grouptag, grouptag+i+1, grouptag+CCTag_MenuSub_00+i+1});
		spTitleMenusSelected[i+1] = game.GetNode({grouptag, grouptag+i+1, grouptag+CCTag_MenuSub_01+i+1});
		
		local fadetime = 0.3+(4-i)*0.05;
		if i+1 ~= selitemtag then
			local menumoveaction = game.ActionMove(xmove, 0, fadetime, true);
			menumoveaction = game.ActionEase(CCAF_Out, menumoveaction, 0.25);
			game.RunAction(menus[i+1], menumoveaction);
			
			for j=0, 1 do
				spritealphaaction[j+1] = game.ActionFade(CCAF_To, 0, fadetime);
			end
			game.RunAction(spTitleMenus[i+1], spritealphaaction[1]);
			game.RunAction(spTitleMenusSelected[i+1], spritealphaaction[2]);
			
		else
			
			local selectedalphaaction = {};
			local scaleval = 1.05;
			local selectedscaleactionpre = game.ActionScale(scaleval, scaleval, 0.1);
			local selectedscaleactionpost = game.ActionScale(1, 1, 0.1);
			local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});
			
			for j=0, 1 do
				selectedalphaaction[j+1] = game.ActionFade(CCAF_To, 0xff, 0.3);
			end
			
			game.RunAction(spTitleMenus[i+1], selectedalphaaction[1]);
			game.RunAction(spTitleMenusSelected[i+1], selectedalphaaction[2]);
			
			game.RunAction(menus[i+1], selectedscaleaction);
			
			local delayaction = game.ActionDelay(0.3);
			local callfuncaction = game.ActionCallFunc({grouptag, grouptag+i+1});
			local delayreplacesceneaction = game.ActionSequence({delayaction, callfuncaction});
			local callnode = game.AddNullChild({toptag}, {0, 0, 0, toptag+CCTag_Menu_14+i+1});
			game.RunAction(callnode, delayreplacesceneaction);
			
		end
	end
end

function TitleScene_ReplaceScene(itemtag, eventtag, toptag, selgrouptag, selitemtag)
	
	if selitemtag == 1 then
		game.ReplaceScene(ktag_StageSelectSceneLayer, g_SceneTransTime);
	elseif selitemtag == 2 then
		game.ReplaceScene(ktag_HiScoreSceneLayer, g_SceneTransTime);
	elseif selitemtag == 3 then
		game.ReplaceScene(ktag_OptionSceneLayer, g_SceneTransTime);
	elseif selitemtag == 4 then
		game.ReplaceScene(ktag_OnlineSceneLayer, g_SceneTransTime);
	else
		game.PushScene(ktag_HelpSceneLayer, g_SceneTransTime);
	end
	
end