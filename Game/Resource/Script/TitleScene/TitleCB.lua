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
	elseif sublayertag == CCTag_Layer_05 then
		if selgrouptag == CCTag_Menu_01 then
			return TitleScene_CB_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_14 then
			return TitleScene_CBDelay_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	elseif sublayertag == CCTag_Layer_09 then
		if selgrouptag == CCTag_Menu_01 then
			return TitleScene_CB_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_14 then
			return TitleScene_CBDelay_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
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
	elseif selitemtag == 3 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterOptionLayer(toplayer, toptag);
	elseif selitemtag == 4 then
		_TitleScene_LeaveMainLayer(toplayer, toptag);
		_TitleScene_EnterOnlineLayer(toplayer, toptag);
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

function TitleScene_CB_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 2 then
		return;
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 400;
	for i=0, 1 do
	
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

function TitleScene_CBDelay_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveOptionLayer(toplayer, toptag);
	_TitleScene_EnterMainLayer(toplayer, toptag);
end



function TitleScene_CB_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 1 then
		return;
	elseif selitemtag == 2 then
		return;
	end
	
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	local menus = {};
	local xmove = 400;
	for i=0, 2 do
	
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

function TitleScene_CBDelay_Online(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveOnlineLayer(toplayer, toptag);
	_TitleScene_EnterMainLayer(toplayer, toptag);
end


function _TitleScene_CB_BGMTouch_SetValue(toplayer, toptag, touchlayer, index, flag)
	
	local x, y, time, rectx, recty, rectw, recth = game.GetTouchInfo(touchlayer, index, flag);
	
	local layertag = toptag + CCTag_Layer_06;
	
	if x < rectx then
		x = rectx;
	elseif x > rectx + rectw then
		x = rectx + rectw;
	end
	
	local bgmvol = (x-rectx)/rectw*100;
	game.SetBGMSEVol(bgmvol);
	bgmvol = game.GetBGMSEVol();
	
	local bgmbar = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_01});
	game.SetScale(bgmbar, bgmvol/100.0, 1);
	
end

function _TitleScene_CB_SETouch_SetValue(toplayer, toptag, touchlayer, index, flag)
	
	local x, y, time, rectx, recty, rectw, recth = game.GetTouchInfo(touchlayer, index, flag);
	
	local layertag = toptag + CCTag_Layer_07;
	
	if x < rectx then
		x = rectx;
	elseif x > rectx + rectw then
		x = rectx + rectw;
	end
	
	local sevol = (x-rectx)/rectw*100;
	local bgmvol = -1;
	game.SetBGMSEVol(bgmvol, sevol);
	bgmvol, sevol = game.GetBGMSEVol();
	
	local sebar = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_01});
	game.SetScale(sebar, sevol/100.0, 1);
	
end

function _TitleScene_CB_BGMTouch_Began(toplayer, toptag, touchlayer, index)	
	_TitleScene_CB_BGMTouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Began);	
end

function _TitleScene_CB_BGMTouch_Moved(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_BGMTouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);
end

function _TitleScene_CB_BGMTouch_Ended(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_BGMTouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);--CCTI_Ended
end

function _TitleScene_CB_SETouch_Canceled(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_BGMTouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);--CCTI_Ended
end

function _TitleScene_CB_SETouch_Began(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_SETouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Began);
end

function _TitleScene_CB_SETouch_Moved(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_SETouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);
end

function _TitleScene_CB_SETouch_Ended(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_SETouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);--CCTI_Ended
end

function _TitleScene_CB_SETouch_Canceled(toplayer, toptag, touchlayer, index)
	_TitleScene_CB_SETouch_SetValue(toplayer, toptag, touchlayer, index, CCTI_Moved);--CCTI_Ended
end