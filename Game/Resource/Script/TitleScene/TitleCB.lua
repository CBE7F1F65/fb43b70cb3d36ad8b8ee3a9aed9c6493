function TitleScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	if sublayertag == CCTag_Layer_14 then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	
	elseif sublayertag == CCTag_Layer_01 then
		if selgrouptag == CCTag_Menu_01 then
			return TitleScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_14 then
			return TitleScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	elseif sublayertag == CCTag_Layer_03 then
		if selgrouptag == CCTag_Menu_01 then
			return TitleScene_CB_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_14 then
			return TitleScene_CBDelay_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
end

function TitleScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 5 then
		game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
		return;
	end
	
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 400;
	for i=0, 4 do
	
		menus[i+1] = game.GetNode({toplayer, layertag, grouptag, grouptag+i+1});
		
		local fadetime = 0.3+(4-i)*0.05;
		
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
			
			local delayaction = game.ActionDelay(0.3);
			local callfuncaction = game.ActionCallFunc({toplayer, layertag, grouptag, grouptag+i+1});
			local delayreplacesceneaction = game.ActionSequence({delayaction, callfuncaction});
			local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_14+i+1});
			game.RunAction(callnode, delayreplacesceneaction);
			
		end
	end
end

function TitleScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 1 then
		game.ReplaceScene(ktag_StageSelectSceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 2 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterHiScoreLayer(toplayer, toptag);
--		game.ReplaceScene(ktag_HiScoreSceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 3 then
--		game.ReplaceScene(ktag_OptionSceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 4 then
--		game.ReplaceScene(ktag_OnlineSceneLayer, LConst_SceneTransTime);
	else
		game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
	end
	
end

function TitleScene_CB_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local xmove = 400;
	
	local menu = game.GetNode({toplayer, layertag, grouptag, grouptag+1});
		
	local fadetime = 0.3;

	local scaleval = 1.05;
	local selectedscaleactionpre = game.ActionScale(CCAF_To, scaleval, scaleval, 0.1);
	local selectedscaleactionpost = game.ActionScale(CCAF_To, 1, 1, 0.1);
	local selectedscaleaction = game.ActionSequence({selectedscaleactionpre, selectedscaleactionpost});

	local selectedalphaaction = game.ActionFade(CCAF_To, 0xff, 0.3);
			
	local selectedaction = game.ActionSpawn({selectedscaleaction, selectedalphaaction});

	game.RunAction(menu, selectedaction);
			
	local delayaction = game.ActionDelay(0.3);
	local callfuncaction = game.ActionCallFunc({toplayer, layertag, grouptag, grouptag+1});
	local delayreplacesceneaction = game.ActionSequence({delayaction, callfuncaction});
	local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_14+1});
	game.RunAction(callnode, delayreplacesceneaction);
end

function TitleScene_CBDelay_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveHiScoreLayer(toplayer, toptag);
	_TitleScene_EnterMainLayer(toplayer, toptag);
end