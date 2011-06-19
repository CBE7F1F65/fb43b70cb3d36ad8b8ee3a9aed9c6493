function TitleScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	if sublayertag == CCSTL_Debug then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	-- Main menu
	elseif sublayertag == CCTSTL_Menu then
		if selgrouptag == CCTSTM_Menu_Main then
			return TitleScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_Menu_MainDelay then
			return TitleScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	-- HiScore
	elseif sublayertag == CCTSTL_HiScore then
		if selgrouptag == CCTSTM_HiScore_Menu then
			return TitleScene_CB_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_HiScore_OKCancel then
			return TitleScene_CB_OKCancelHiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_HiScore_OKCancelDelay then
			return TitleScene_CBDelay_OKCancelHiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_HiScore_MenuDelay then
			return TitleScene_CBDelay_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	--Option
	elseif sublayertag == CCTSTL_Option then
		if selgrouptag == CCTSTM_Option_Menu then
			return TitleScene_CB_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_Option_OKCancel then
			return TitleScene_CB_OKCancelOption(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_Option_OKCancelDelay then
			return TitleScene_CBDelay_OKCancelOption(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_Option_MenuDelay then
			return TitleScene_CBDelay_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	-- Online
	elseif sublayertag == CCTSTL_Online then
		if selgrouptag == CCTSTM_Online_Menu then
			return TitleScene_CB_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTSTM_Online_MenuDelay then
			return TitleScene_CBDelay_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
end

function TitleScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 4 then
		game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
		return;
	end
	
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 400;
	
	local menu = game.GetNode({toplayer, grouptag});
	game.SetTouchEnabled(menu, false);
	
	for i=0, 5 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(4-i)*0.04;
		
		if i+1 ~= selitemtag then
			
			local txmove = xmove;
			if i > 3 then
				txmove = - xmove;
			end
			local menumoveaction = game.ActionMove(CCAF_By, txmove, 0, fadetime);
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
			local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTSTM_Menu_MainDelay+i+1});
			game.RunAction(callnode, callfuncaction);
			
		end
	end
end

function TitleScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 1 then
		game.ReplaceScene(ktag_StageSelectSceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 2 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterOptionLayer(toplayer, toptag);
	elseif selitemtag == 3 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterOnlineLayer(toplayer, toptag);
	elseif selitemtag == 5 then
		
		game.TryStage(LConst_SurvivalStageIndex);
		game.TryMission(LConst_SurvivalMissionIndex);
		game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 6 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterHiScoreLayer(toplayer, toptag);
	else
		game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
	end
	
end
