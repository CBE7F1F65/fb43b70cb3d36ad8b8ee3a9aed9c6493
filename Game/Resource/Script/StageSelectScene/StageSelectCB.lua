function StageSelectScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	if sublayertag == CCTag_Layer_14 then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	-- Main menu
	elseif sublayertag == CCTag_Layer_01 then
		if selgrouptag == CCTag_Menu_01 then
			return StageSelectScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_14 then
			return StageSelectScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
	
end

function StageSelectScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 40;
	local ymove = 40;
	
	for i=0, 8 do
	
		menus[i+1] = game.GetNode({toplayer, layertag, grouptag, grouptag+i+1});
		
		local fadetime = 0.3+(8-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			local menumoveaction = game.ActionMove(CCAF_By, xmove, ymove, fadetime);
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

function StageSelectScene_CBDelay_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 9 then
		game.ReplaceScene(ktag_TitleSceneLayer, LConst_SceneTransTime);
	else
		game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
	end
	
end
