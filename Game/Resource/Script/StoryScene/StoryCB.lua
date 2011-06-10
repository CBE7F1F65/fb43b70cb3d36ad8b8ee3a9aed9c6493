function StoryScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	if sublayertag == CCSTL_Debug then
		if selgrouptag == CCTag_Debug_ReloadMenu then
			return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
		end
		
	elseif sublayertag == CCSSTL_Menu then
		if selgrouptag == CCSSTM_Menu_Main then
			return StoryScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCSSTM_Menu_MainDelay then
			return StoryScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
end

function StoryScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 400;
	
	local menu = game.GetNode({toplayer, grouptag});
	game.SetTouchEnabled(menu, false);
	
--	for i=0, 2 do
	local i = 0;
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3;
		
		if i+1 ~= selitemtag then
			
			local menumoveaction = game.ActionMove(CCAF_By, xmove, 0, fadetime);
			menumoveaction = game.ActionEase(CCAF_Out, menumoveaction, 0.25);
			local menualphaaction = game.ActionFade(CCAF_To, 0, fadetime);			
			local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});
			
			game.RunAction(menus[i+1], menuaction);
			
		else
			
			local scaleval = 1.05;
			local selectedscaleactionpre = game.ActionScale(CCAF_To, scaleval, scaleval, 0.1);
			local selectedscaleactionpost = game.ActionScale(CCAF_To, 1, 1, 0.1);
			local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});
			
			local selectedalphaaction = game.ActionFade(CCAF_To, 0xff, 0.3);
			
			local selectedaction = game.ActionSpawn({selectedscaleaction, selectedalphaaction});

			game.RunAction(menus[i+1], selectedaction);
			
			local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
			local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCSSTM_Menu_MainDelay+i+1});
			game.RunAction(callnode, callfuncaction);
			
		end
--	end
	
end

function _StoryScene_EnableNextMission(toplayer, toptag)
	local nowstage, nowmission = game.GetNowStageMissionTurn();
	
	game.EnableMission(nowmission+1);
	--Update MissionSelectUI
	
end

function StoryScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_StoryScene_EnableNextMission(toplayer, toptag);
	game.ReplaceScene(ktag_MissionSelectSceneLayer, LConst_SceneTransTime);
end