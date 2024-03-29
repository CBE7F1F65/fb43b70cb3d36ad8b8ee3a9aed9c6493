function MissionSelectScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	if sublayertag == CCSTL_Debug then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	-- Main menu
	elseif sublayertag == CCMSSTL_Menu then
		if selgrouptag == CCMSSTM_Menu_Main then
			return MissionSelectScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCMSSTM_Menu_Page then
			return MissionSelectScene_CB_PageMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCMSSTM_Menu_PageDelay then
			return MissionSelectScene_CBDelay_PageMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCMSSTM_Menu_MainDelay then
			return MissionSelectScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
end

function MissionSelectScene_CB_PageMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 3 then
		
		local scaleval = 1.05;
		local selectedscaleactionpre = game.ActionScale(CCAF_To, scaleval, scaleval, 0.1);
		local selectedscaleactionpost = game.ActionScale(CCAF_To, 1, 1, 0.1);
		local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});
		local selectedalphaaction = game.ActionFade(CCAF_To, 0xff, 0.3);
		local selectedaction = game.ActionSpawn({selectedscaleaction, selectedalphaaction});
		local menuitem = game.GetNode({toplayer, itemtag})
		game.RunAction(menuitem, selectedaction);
			
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCMSSTM_Menu_PageDelay+selitemtag});
		game.RunAction(callnode, callfuncaction);
		MissionSelectScene_CB_MainMenu(-1, toplayer, toptag, sublayertag, CCMSSTM_Menu_Main, -1);
		return;
		
	end
	
	local nowstage = game.GetNowStageMissionTurn();
	if nowstage == LConst_ExtraStageIndex then
		return;
	end
	
	local layertag = toptag+sublayertag;
	local grouptag = layertag+CCMSSTM_Menu_Main;
	local menunode = game.GetNode({toplayer, grouptag});
	if selitemtag == 1 then
		LGlobal_MSS_NowPage = LGlobal_MSS_NowPage-1;
		if LGlobal_MSS_NowPage < 0 then
			LGlobal_MSS_NowPage = 2;
		end
	elseif selitemtag == 2 then
		LGlobal_MSS_NowPage = LGlobal_MSS_NowPage+1;
		if LGlobal_MSS_NowPage > 2 then
			LGlobal_MSS_NowPage = 0;
		end
	end
	
	local x = LGlobal_MSS_NowPage*960;
	local moveaction = game.ActionMove(CCAF_To, -x, 0, LConst_DelayActionTime);
	moveaction = game.ActionEase(CCAF_In, moveaction, 0.25);
	game.RunAction(menunode, moveaction);
	
end

function MissionSelectScene_CBDelay_PageMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
		game.ReplaceScene(ktag_StageSelectSceneLayer, LConst_SceneTransTime);
end

function MissionSelectScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
			
	local toquit = true;
	
	local nowstage = game.GetNowStageMissionTurn();
	local missioncount = LConst_MissionIndex_End;
	if nowstage == LConst_ExtraStageIndex then
		missioncount = LConst_MissionIndex_ExtraStage;
	end
	
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	local xmove = 40;
	local ymove = -40;
	
	for i=0, missioncount-1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(missioncount-i)*0.01;
		
		if i+1 ~= selitemtag then
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_By, xmove, ymove, fadetime);
				menumoveaction = game.ActionEase(CCAF_Out, menumoveaction, 0.25);
				local menualphaaction = game.ActionFade(CCAF_To, 0, fadetime);			
				local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});
			
				game.RunAction(menus[i+1], menuaction);
			end
			
		else
			
			local scaleval = 1.05;
			local selectedscaleactionpre = game.ActionScale(CCAF_To, scaleval, scaleval, 0.1);
			local selectedscaleactionpost = game.ActionScale(CCAF_To, 1, 1, 0.1);
			local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});
			
			local selectedalphaaction = game.ActionFade(CCAF_To, 0xff, 0.3);
			
			local selectedaction = game.ActionSpawn({selectedscaleaction, selectedalphaaction});

			game.RunAction(menus[i+1], selectedaction);
			
			if toquit then
				local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
				local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCMSSTM_Menu_MainDelay+i+1});
				game.RunAction(callnode, callfuncaction);
			end
			
		end
	end
end

function MissionSelectScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	game.TryMission(selitemtag-1);
	if selitemtag == 1 then
		game.ReplaceScene(ktag_StorySceneLayer, LConst_SceneTransTime);
	else
		game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
	end
	
end
