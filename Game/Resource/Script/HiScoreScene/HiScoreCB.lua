function TitleScene_CB_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local toquit = true;
	if selitemtag == 1 then
		_TitleScene_EnterOKCancelHiScoreLayer(toplayer, toptag);
		toquit = false;
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	local xmove = 400;
	
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
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
				local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTSTM_HiScore_MenuDelay+i+1});
				game.RunAction(callnode, callfuncaction);
			end
			
		end
	end
end

function TitleScene_CB_OKCancelHiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local toquit = true;
	if selitemtag == 1 then
		game.ResetHiScoreData();
		_TitleScene_UpdateHiScore(toplayer, toptag);
	elseif selitemtag == 3 then
		selitemtag = 2;
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	local xmove = 160;
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
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
				local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTSTM_HiScore_OKCancelDelay+i+1});
				game.RunAction(callnode, callfuncaction);
			end
			
		end
	end
end

function TitleScene_CBDelay_OKCancelHiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveOKCancelHiScoreLayer(toplayer, toptag);
end

function TitleScene_CBDelay_HiScore(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	_TitleScene_LeaveHiScoreLayer(toplayer, toptag);
	_TitleScene_EnterMainLayer(toplayer, toptag);
end
