function PlayScene_CB(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	if sublayertag == CCSTL_Debug then
		return Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag);
	
	-- Enemy
	elseif sublayertag == CCPSTL_Enemy or sublayertag == CCPSTL_EnemyOnSide then
		-- EnemyStateEvent
		if selgrouptag == CCPSTM_Enemy_CallNode then
			return PSCB_EnemyStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex);
		end
		
	-- Plan
	elseif sublayertag == CCPSTL_Plan then
		-- PlanStateEvent
		if selgrouptag == CCPSTM_Plan_CallNode then
			return PSCB_PlanStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex);
		end
	
	-- Main menu
	elseif sublayertag == CCPSTL_Menu then
		-- Main menu
		if selgrouptag == CCPSTM_Menu_Main then
			return PSCB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 01 item apup atkup defup
		elseif selgrouptag == CCPSTM_Menu_SubLevel01 then
			return PSCB_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- QuitRestart
		elseif selgrouptag == CCPSTM_Menu_QuitRestart then
			return PSCB_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 02 modify ...
		elseif selgrouptag == CCPSTM_Menu_SubLevel02 then
			return PSCB_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 03 use get
		elseif selgrouptag == CCPSTM_Menu_SubLevel03 then
			return PSCB_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 03 Delay
		elseif selgrouptag == CCPSTM_Menu_SubLevel03Delay then
			return PSCBDelay_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 02 Delay
		elseif selgrouptag == CCPSTM_Menu_SubLevel02Delay then
			return PSCBDelay_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- QuitRestart
		elseif selgrouptag == CCPSTM_Menu_QuitRestartDelay then
			return PSCBDelay_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		-- Sub 01 Delay
		elseif selgrouptag == CCPSTM_Menu_SubLevel01Delay then
			return PSCBDelay_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	
	-- Target/Turn/Mission Over
	elseif sublayertag == CCPSTL_Message then
		-- Target menu
		if selgrouptag == CCPSTM_Message_TargetMenu then
			return PSCB_TurnStartAndTarget(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCPSTM_Message_OverMenu then
			return PSCB_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCPSTM_Message_OverMenuDelay then
			return PSCBDelay_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		elseif selgrouptag == CCPSTM_Message_TargetMenuDelay then
			return PSCBDelay_TurnStartAndTarget(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag);
		end
	end
	
end

function PSCB_EnemyStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + selgrouptag;
	
	game.RemoveChild({toplayer, grouptag+selitemtag});
	local stateAction = LGlobal_GetData(dataindex);	
	PS_StepForward(stateAction);
end

function PSCB_PlanStateEvent(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, dataindex)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + selgrouptag;
	
	game.RemoveChild({toplayer, grouptag+selitemtag});
	local stateAction = LGlobal_GetData(dataindex);	
	PS_StepForward(stateAction);
end

function PSCBDelay_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Menu_SubLevel01;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
	game.SetTouchEnabled(mainmenu, true);
	
end

function PSCBDelay_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Menu_QuitRestart;
	game.RemoveChild({toplayer, grouptag});
	
	if selitemtag == 2 then
		game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
	end
	
	local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
	game.SetTouchEnabled(mainmenu, true);
end

function PSCBDelay_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Menu_SubLevel02;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
	game.SetTouchEnabled(mainmenu, true);
end

function PSCBDelay_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Menu_SubLevel03;
	game.RemoveChild({toplayer, grouptag});
	
	local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
	game.SetTouchEnabled(mainmenu, true);
end

function PlayScene_CBDispatch_MainMenu_Sub_01(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Menu_Main;
	
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
	local grouptag = layertag + CCPSTM_Menu_Main;
	-- Menu
	if callitemtag == grouptag+4 then
		-- Target
		if selitemtag == 1 then
			PS_ShowTurnStartAndTarget(toplayer, toptag, true);
			PS_SetMenuEnable(toplayer, toptag, false);
		-- Help
		elseif selitemtag == 2 then
--			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
		--Quit
		elseif selitemtag == 3 then
			local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
			if nowstage == LConst_SurvivalStageIndex and nowmission == LConst_SurvivalMissionIndex then
				game.ReplaceScene(ktag_TitleSceneLayer, LConst_SceneTransTime);
			else
				game.ReplaceScene(ktag_MissionSelectSceneLayer, LConst_SceneTransTime);
			end
		--Restart
		else
			game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
		end
	end
	
	return false;
		
end

function PlayScene_CBDispatch_MainMenu_Sub_02(callitemtag, toplayer, toptag, sublayertag, selitemtag)
	
	local layertag = toptag + sublayertag;
	-- Item
	local grouptag = layertag + CCPSTM_Menu_SubLevel01;
	
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
	local grouptag = layertag + CCPSTM_Menu_SubLevel02;
	
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

function PSCB_MainMenu_QuitRestart(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local callitemtag, posdata = LGobal_PopPlaySceneMenuData();

	local toquit = true;
	
	if selitemtag < 5 then
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
	
	for i=0, 3 do
	
		menus[i+1] = game.GetNode({toplayer, grouptag+i+1});
		
		local fadetime = 0.3+(3-i)*0.02;
		
		if i+1 ~= selitemtag then
			
			local yorig = yorigcen - (i-1.5)*70
			
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
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Menu_QuitRestartDelay+selitemtag});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PSCB_MainMenu_Sub_01(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
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
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Menu_SubLevel01Delay+selitemtag});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PSCB_MainMenu_Sub_02(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
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
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Menu_SubLevel02Delay+selitemtag});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
		game.SetTouchEnabled(mainmenu, false);
	end
end

function PSCB_MainMenu_Sub_03(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
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
		local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Menu_SubLevel03Delay+selitemtag});
		game.RunAction(callnode, callfuncaction);
		
		local mainmenu = game.GetNode({toplayer, layertag+CCPSTM_Menu_Main});
		game.SetTouchEnabled(mainmenu, false);
	end
			
end

function PS_CB_AddUseGet(toplayer, toptag, layertag, itemtag, posdata)
		
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCPSTM_Menu_SubLevel03;

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

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, yorig, CCPSTM_Menu_SubLevel03, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

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
	
	menus[3] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCPSTM_Menu_SubLevel03, grouptag+3);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCPSTM_Menu_SubLevel03, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
	LGobal_PushPlaySceneMenuData(itemtag, posdata);
	
end

function PS_CB_AddQuitRestart(toplayer, toptag, layertag, itemtag, posdata)
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCPSTM_Menu_QuitRestart;

	local xorig = posdata[1];
	local yorigcen = posdata[2];
	local xmove = posdata[3];
	local ymove = posdata[4];
	
	for i=0, 3 do
		
		local yorig = yorigcen - (i-1.5)*70;
		local x = xorig + xmove;
		local y = yorig + ymove;
		
		spMenus[i+1] = game.CreateSprite(SI_GUISub_Target+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_GUISub_Target_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, yorig, CCPSTM_Menu_QuitRestart, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.02;
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
	
	menus[5] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCPSTM_Menu_QuitRestart, grouptag+5);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCPSTM_Menu_QuitRestart, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
	LGobal_PushPlaySceneMenuData(itemtag, posdata);
	
end

function PS_CB_OnClickAction(toplayer, toptag)
	PS_ExitPlanning(toplayer, toptag);
	PS_StateFinish(STATE_Planning);
end

function PS_CB_OnClickWait(toplayer, toptag)
	local plangroup = LGlobal_PlayData.plangroup;
	local bFound = false;
	if not bFound then
		local nLines = table.getn(LGlobal_PlayData.planlines);
		for i=1, nLines do
			if LGlobal_PlayData.planlines[i].plangroup == plangroup then
				bFound = true;
				break;
			end
		end
	end
	if not bFound then
		local nCircles = table.getn(LGlobal_PlayData.plancircles);
		for i=1, nCircles do
			if LGlobal_PlayData.plancircles[i].plangroup == plangroup then
				bFound = true;
				break;
			end
		end
	end
	if not bFound then
		local nDots = table.getn(LGlobal_PlayData.plandots);
		for i=1, nDots do
			if LGlobal_PlayData.plandots[i].plangroup == plangroup then
				bFound = true;
				break;
			end
		end
	end
	if bFound then
		if plangroup < LConst_PlanGroupMax-1 then
			LGlobal_PlayData.plangroup = plangroup+1;
			PS_UpdatePlanGroup(toplayer, toptag);
		end
	end
end

function PSCB_MainMenu(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local layertag = toptag + sublayertag;
	local grouptag = layertag + selgrouptag;
	
	local item = game.GetNode({toplayer, grouptag+selitemtag});
	local xbase, ybase = game.GetPosition(item);

	-- command
	if selitemtag == 1 then
	-- action
	elseif selitemtag == 2 then
		PS_CB_OnClickAction(toplayer, toptag);
	-- wait
	elseif selitemtag == 3 then
		PS_CB_OnClickWait(toplayer, toptag);
	-- menu
	elseif selitemtag == 4 then
		PS_CB_AddQuitRestart(toplayer, toptag, layertag, itemtag, {xbase, ybase, 0, 180});
	end
	
end

function PSCB_TurnStartAndTarget(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag, delaytime)
	
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
	local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Message_TargetMenuDelay+selitemtag});

	game.RunAction(callnode, callfuncaction);
	
end

function PSCBDelay_TurnStartAndTarget(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	local layertag = toptag + sublayertag;
	local grouptag = layertag + CCPSTM_Message_TargetBoard;
	
	game.RemoveAllChildren({toplayer, grouptag});
	grouptag = layertag + CCPSTM_Message_TargetMenu;
	game.RemoveChild({toplayer, grouptag});
	
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, 0);
	
	local bInShowTurnStart = PS_StateFinish(STATE_ShowTurnStart);
	
	layertag = toptag + CCPSTL_Plan;
	local layernode = game.GetNode({toplayer, layertag});
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	local tintaction = game.ActionTint(CCAF_To, 0xffffff, LConst_ItemVanishTime);
	local spaction = game.ActionSpawn({fadeaction, tintaction});
	game.RunAction(layernode, spaction);
	
	if not bInShowTurnStart then
		PS_SetMenuEnable(toplayer, toptag, true);
	end
	
end

function PSCB_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	local layertag = toptag + sublayertag;
	
	local movedownaction = game.ActionMove(CCAF_To, 0, -480, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
		
	game.RunAction(layernode, movedownaction);
		
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_DelayActionTime);
	local callnode = game.AddNullChild({toplayer, layertag}, {0, 0, 0, layertag+CCPSTM_Message_OverMenuDelay+selitemtag});

	game.RunAction(callnode, callfuncaction);
	
end

function PSCBDelay_MissionOver(itemtag, toplayer, toptag, sublayertag, selgrouptag, selitemtag)
	
	if selitemtag == 1 then
		local missionindex, stageindex = game.GetNextAvailableMission();
		if missionindex ~= nil then
			game.TryMission(missionindex, stageindex);
			game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
		end
	elseif selitemtag == 2 then
		game.ReplaceScene(ktag_PlaySceneLayer, LConst_SceneTransTime);
	elseif selitemtag == 3 then
		game.ReplaceScene(ktag_MissionSelectSceneLayer, LConst_SceneTransTime);
	end
	
end