function PlayScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	if sublayertag == CCTag_Layer_14 then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	-- Enemy
	elseif sublayertag == CCTag_Layer_02 or sublayertag == CCTag_Layer_08 then
		-- EnemyStateEvent
		if selgrouptag == CCTag_Menu_11 then
			return PlayScene_CB_EnemyStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex);
		end
	
	-- Main menu
	elseif sublayertag == CCTag_Layer_13 then
		-- Main menu
		if selgrouptag == CCTag_Menu_01 then
			return PlayScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 01 item apup atkup defup
		elseif selgrouptag == CCTag_Menu_03 then
			return PlayScene_CB_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- QuitRestart
		elseif selgrouptag == CCTag_Menu_04 then
			return PlayScene_CB_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 02 modify ...
		elseif selgrouptag == CCTag_Menu_05 then
			return PlayScene_CB_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 03 use get
		elseif selgrouptag == CCTag_Menu_06 then
			return PlayScene_CB_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 03 Delay
		elseif selgrouptag == CCTag_Menu_09 then
			return PlayScene_CBDelay_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 02 Delay
		elseif selgrouptag == CCTag_Menu_10 then
			return PlayScene_CBDelay_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- QuitRestart
		elseif selgrouptag == CCTag_Menu_11 then
			return PlayScene_CBDelay_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 01 Delay
		elseif selgrouptag == CCTag_Menu_12 then
			return PlayScene_CBDelay_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	
	-- Target/Turn/Mission Over
	elseif sublayertag == CCTag_Layer_04 then
		-- Target menu
		if selgrouptag == CCTag_Menu_04 then
			return PlayScene_CB_Target(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_06 then
			return PlayScene_CB_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_09 then
			return PlayScene_CBDelay_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCTag_Menu_11 then
			return PlayScene_CBDelay_Target(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
	
end

function PlayScene_CB_EnemyStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + selgrouptag;
	
	game.RemoveChild({toplayer, grouptag+selitemtag});
	local stateAction = LGlobal_GetData(dataindex);	
	_PlayScene_StepForward(stateAction);
end

function PlayScene_CBDelay_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_03;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
	game.SetTouchEnabled(mainmenu, true);
	
end

function PlayScene_CBDelay_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_04;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
	game.SetTouchEnabled(mainmenu, true);
end

function PlayScene_CBDelay_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_05;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
	game.SetTouchEnabled(mainmenu, true);
end

function PlayScene_CBDelay_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_06;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
	game.SetTouchEnabled(mainmenu, true);
end

function PlayScene_CBDispatch_MainMenu_Sub_01(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_01;
	
	-- Command
	if callitemtag == grouptag+1 then
		--item
		if selitemtag == 1 then
		--APup
		elseif selitemtag == 2 then
		--ATKup
		elseif selitemtag == 3 then
		--DEFup
		elseif selitemtag == 4 then
		end
	end
	
	return false;
		
end

function PlayScene_CBDispatch_MainMenu_QuitRestart(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_01;
	-- Menu
	if callitemtag == grouptag+4 then
		-- TODO: Target
		if selitemtag == 1 then
			_PlayScene_DoShowTurnStart(toplayer, toptag, true);
		--Quit
		elseif selitemtag == 2 then
			game.PushScene(ktag_MissionSelectSceneLayer, LConst_SceneTransTime);
		--Restart
		else
			game.PushScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
		end
	end
	
	return false;
		
end

function PlayScene_CBDispatch_MainMenu_Sub_02(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	-- Item
	local grouptag = layertag + CCTag_Menu_03;
	
	if callitemtag == grouptag+1 then
		-- GetFromGame;(Item List)
	-- APup
	elseif callitemtag == grouptag+2 then
	-- ATKup
	elseif callitemtag == grouptag+2 then
	-- DEFup
	elseif callitemtag == grouptag+2 then
	end
	
	return false;
		
end

function PlayScene_CBDispatch_MainMenu_Sub_03(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	-- Item->...
	local grouptag = layertag + CCTag_Menu_05;
	
	local itemindex = callitemtag-(grouptag+1);
		-- use
		game.UseItem(itemindex);
	if selitemtag == 1 then
		--get
		game.BuyItem(itemindex);
	else
	end
	
	return false;
		
end

function PlayScene_CB_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local callitemtag, posdata = LGobal_PopPlaySceneMenuData();

	local toquit = true;
	
	if selitemtag < 4 then
		if PlayScene_CBDispatch_MainMenu_QuitRestart(callitemtag, toplayer, toptag, sublayertag, selitemtag) then
			return
		end
	end
			
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	
	local xorig = posdata[1];
	local yorigcen = posdata[2];
	
	for i=0, 2 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(2-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			local yorig = yorigcen - (i-1)*70
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_To, xorig, yorig, fadetime);
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
			
		end
	end
	
	
	if toquit then
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_11+selitemtag+1});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PlayScene_CB_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local callitemtag, posdata = LGobal_PopPlaySceneMenuData();
	
	local toquit = true;
	
	if selitemtag <= LConst_CommandCount then
		if PlayScene_CBDispatch_MainMenu_Sub_01(callitemtag, toplayer, toptag, sublayertag, selitemtag) then
			return
		end
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	
	local xorig = posdata[1];
	local yorigcen = posdata[2];
	
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(1-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			local yorig = yorigcen - (i-0.5)*70
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_To, xorig, yorig, fadetime);
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
			
		end
	end
	
	
	if toquit then
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_12+selitemtag+1});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PlayScene_CB_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local callitemtag, posdata = LGobal_PopPlaySceneMenuData();
	
	local toquit = true;
	
	if selitemtag < 3 then
		if PlayScene_CBDispatch_MainMenu_Sub_03(callitemtag, toplayer, toptag, sublayertag, selitemtag) then
			return
		end
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	
	local xorig = posdata[1];
	local yorigcen = posdata[2];
	
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(1-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			local yorig = yorigcen - (i-0.5)*70
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_To, xorig, yorig, fadetime);
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
			
		end
	end
	
	
	if toquit then
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_10+selitemtag+1});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PlayScene_CB_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local callitemtag, posdata = LGobal_PopPlaySceneMenuData();
	
	local toquit = true;
	
	if selitemtag < 3 then
		if PlayScene_CBDispatch_MainMenu_Sub_03(callitemtag, toplayer, toptag, sublayertag, selitemtag) then
			return
		end
	end
		
	local layertag = toptag+sublayertag;
	local grouptag = layertag+selgrouptag;
	
	if toquit then
		local menu = game.GetNode({toplayer, grouptag});
		game.SetTouchEnabled(menu, false);
	end
	
	local menus = {};
	
	local xorig = posdata[1];
	local yorigcen = posdata[2];
	
	for i=0, 1 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(1-i)*0.05;
		
		if i+1 ~= selitemtag then
			
			local yorig = yorigcen - (i-0.5)*70
			
			if toquit then
				local menumoveaction = game.ActionMove(CCAF_To, xorig, yorig, fadetime);
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
			
		end
	end
	
	
	if toquit then
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_09+selitemtag+1});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCTag_Menu_01});
		game.SetTouchEnabled(mainmenu, false);
	end
			
end

function _PlayScene_CB_AddUseGet(toplayer, toptag, layertag, itemtag, posdata)
		
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTag_Menu_06;

	local xorig = posdata[1];
	local yorigcen = posdata[2];
	local xmove = posdata[3];
	local ymove = posdata[4];
	
	for i=0, 1 do
		
		local yorig = yorigcen - (i-0.5)*70;
		local x = xorig + xmove;
		local y = yorig + ymove;
		
		spMenus[i+1] = game.CreateSprite(SI_GUISub_Use+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_GUISub_Use_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, yorig, CCTag_Menu_06, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, x, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	
	menus[3] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTag_Menu_06, grouptag+3);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_06, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
	LGobal_PushPlaySceneMenuData(itemtag, posdata);
	
end

function _PlayScene_CB_AddQuitRestart(toplayer, toptag, layertag, itemtag, posdata)
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTag_Menu_04;

	local xorig = posdata[1];
	local yorigcen = posdata[2];
	local xmove = posdata[3];
	local ymove = posdata[4];
	
	for i=0, 2 do
		
		local yorig = yorigcen - (i-1)*70;
		local x = xorig + xmove;
		local y = yorig + ymove;
		
		spMenus[i+1] = game.CreateSprite(SI_GUISub_Target+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_GUISub_Target_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, yorig, CCTag_Menu_04, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, x, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	
	menus[4] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTag_Menu_04, grouptag+4);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_04, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
	LGobal_PushPlaySceneMenuData(itemtag, posdata);
	
end

function _PlayScene_CB_Action(toplayer, toptag)
	_PlayScene_ExitPlanning(toplayer, toptag);
	_PlayScene_StateFinish(STATE_Planning);
end

function PlayScene_CB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local layertag = toptag + sublayertag;
	local grouptag = layertag + selgrouptag;
	
	local item = game.GetNode({toplayer, grouptag+selitemtag});
	local xbase, ybase = game.GetPosition(item);

	-- command
	if selitemtag == 1 then
	-- action
	elseif selitemtag == 2 then
		_PlayScene_CB_Action(toplayer, toptag);
	-- wait
	elseif selitemtag == 3 then
	-- menu
	elseif selitemtag == 4 then
		_PlayScene_CB_AddQuitRestart(toplayer, toptag, layertag, itemtag, {xbase, ybase, 0, 145});
	end
	
end

function PlayScene_CB_Target(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, delaytime)
	
	local layertag = toptag + sublayertag;
	
	local movedownaction = game.ActionMove(CCAF_To, 0, -480, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
	
	if delaytime ~= nil then
		local delayaction = game.ActionDelay(delaytime);
		movedownaction = game.ActionSequence({delayaction, movedownaction});
	end
	
	game.RunAction(layernode, movedownaction);
	
	if delaytime == nil then
		delaytime = LConst_DelayActionTime;
	else
		delaytime = delaytime + LConst_DelayActionTime;
	end
	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, delaytime);
	local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCTag_Menu_11+selitemtag+1});

	game.RunAction(callnode, callfuncaction);
	
end

function PlayScene_CBDelay_Target(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCTag_Menu_01;
	
	game.RemoveAllChildren({toplayer, grouptag});
	grouptag = layertag + CCTag_Menu_04;
	game.RemoveChild({toplayer, grouptag});
	
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, 0);
	_PlayScene_StateFinish(STATE_ShowTurnStart);
	_PlayScene_StateFinish(STATE_ShowTarget);
	
	layertag = toptag + CCTag_Layer_11;
	grouptag = layertag+CCTag_Menu_01;
	local planrendertexturesprite = game.GetNode({toplayer, grouptag}, NODETYPE_RenderTexture);
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	local tintaction = game.ActionTint(CCAF_To, 0xffffff, LConst_ItemVanishTime);
	local spaction = game.ActionSpawn({fadeaction, tintaction});
	game.RunAction(planrendertexturesprite, spaction);
--	game.SetIsVisible(planlayernode, true);
	
end

function PlayScene_CB_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
end

function PlayScene_CBDelay_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
end