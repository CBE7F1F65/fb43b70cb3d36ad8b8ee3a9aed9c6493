
function TitleScene_CB_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local toquit = true;
	if selitemtag == 2 then
		_TitleScene_EnterOKCancelOptionLayer(toplayer, toptag);
		toquit = false;
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, layertag, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	local xmove = 350;
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, layertag, grouptag, grouptag+i+1});
		
		local fadetime = 0.3+(1-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_By, xmove, 0, fadetime);
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
				local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_14+i+1});
				game.RunAction(callnode, callfuncaction);
			end
			
		end
	end
end

function TitleScene_CB_OKCancelOption(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local toquit = true;
	
	if selitemtag == 1 then
		game.ResetIni();
		_TitleScene_UpdateBGMSE(toplayer, toptag);
	elseif selitemtag == 3 then
		selitemtag = 2;
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, layertag, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	local xmove = 400;
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, layertag, grouptag, grouptag+i+1});
		
		local fadetime = 0.3+(1-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_By, xmove, 0, fadetime);
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
				local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_11+i+1});
				game.RunAction(callnode, callfuncaction);
			end
			
		end
	end
end

function TitleScene_CBDelay_OKCancelOption(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveOKCancelOptionLayer(toplayer, toptag);
end

function TitleScene_CBDelay_Option(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveOptionLayer(toplayer, toptag);
	_TitleScene_EnterMainLayer(toplayer, toptag);
end

function _TitleScene_UpdateBGMSE(toplayer, toptag)
	
	bgmvol, sevol = game.GetBGMSEVol();
	
	layertag = toptag + CCTag_Layer_06;
	local bgmbar = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_01});
	game.SetScale(bgmbar, bgmvol/100.0, 1);
	
	local layertag = toptag + CCTag_Layer_07;
	local sebar = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_01});
	game.SetScale(sebar, sevol/100.0, 1);
	
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
	
	_TitleScene_UpdateBGMSE(toplayer, toptag);
	
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
	_TitleScene_UpdateBGMSE(toplayer, toptag);
	
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

function _TitleScene_CB_BGMTouch_Canceled(toplayer, toptag, touchlayer, index)
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