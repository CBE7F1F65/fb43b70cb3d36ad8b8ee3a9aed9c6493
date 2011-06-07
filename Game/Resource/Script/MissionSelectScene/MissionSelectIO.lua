function MissionSelectScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return MissionSelectScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return MissionSelectScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return MissionSelectScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return MissionSelectScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return MissionSelectScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return MissionSelectScene_OnTouchEnd(toplayer, toptag);
	end
end

function MissionSelectScene_OnInit(toplayer, toptag)
	
	-- bg layer
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local nowstage = game.GetNowStageMissionTurn();
	local spMissionSelect = game.CreateSprite(SI_World01_Scene+nowstage, {480, 320});
	game.AddSpriteChild(spMissionSelect, {toplayer, layertag});
	
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
end

function _MissionSelectScene_AddMainItems(toplayer, toptag)
	
	local nowstage = game.GetNowStageMissionTurn();
	local postable = LGlobal_MissionSelect_NodePos[nowstage+1];
	local nodecount = table.getn(postable);
		
	local spMenus = {};
	local spSelectedMenus = {};
	local spDisabledMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	
	local xcen=0;
	local ycen=0;
	
	for i=0, nodecount do
		
		local enabled = true;
		local missionenabled = false;
		local missiontriedtime = 0;
		
		if i < nodecount then
			
			missionenabled, missiontriedtime = game.MissionIsEnabled(i);
			--event
			if i == 0 and nowstage < 7 then
				spMenus[i+1] = game.CreateSprite(SI_MSUI_Event);
				spSelectedMenus[i+1] = game.CreateSprite(SI_MSUI_Event_Down);
			--pace
			else
			
				if not missionenabled then
					enabled = false;
				end
			
				if missiontriedtime > 0 then
					spMenus[i+1] = game.CreateSprite(SI_MSUI_Mission_Tried);
				else
					spMenus[i+1] = game.CreateSprite(SI_MSUI_Mission);
				end
				spDisabledMenus[i+1] = game.CreateSprite(SI_MSUI_Mission_Disabled);
				spSelectedMenus[i+1] = game.CreateSprite(SI_MSUI_Mission_Down);
			end
		--back
		else
			spMenus[i+1] = game.CreateSprite(SI_TUI_Exit);
			spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Exit_Down);
		end
		
		if i < nodecount then
			xcen = postable[i+1][1];
			ycen = postable[i+1][2];
		else
			xcen = 800;
			ycen = 120;
		end
		
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xcen+40, ycen-40, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1], spDisabledMenus[i+1]);
		
		if not enabled then
			game.SetMenuItemEnabled(menus[i+1], false);
		end

		local fadetime = 0.3+i*0.01;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, ycen, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction;
		if missionenabled and missiontriedtime == 0 then
			local menuscaleinaction = game.ActionScale(CCAF_To, 1.0, 1.0, fadetime);
			local menurepeatscaleactionpre = game.ActionScale(CCAF_To, 1.2, 1.2, LConst_BlinkTimePre/3);
			local menurepeatscaleactionpost = game.ActionScale(CCAF_To, 1.0, 1.0, LConst_BlinkTimePost/3);
			local menurepeatscaleaction = game.ActionSequence({menurepeatscaleactionpre, menurepeatscaleactionpost});
			menurepeatscaleaction = game.ActionRepeat(menurepeatscaleaction);
			local menuscaleaction = game.ActionSequence({menuscaleinaction, menurepeatscaleaction});
			
			menuaction = game.ActionSpawn({menumoveaction, menualphaaction, menuscaleaction})
		else		
			menuaction = game.ActionSpawn({menumoveaction, menualphaaction});
		end

		game.RunAction(menus[i+1], menuaction);
		
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _MissionSelectScene_EnterMainLayer(toplayer, toptag)
	_MissionSelectScene_AddMainItems(toplayer, toptag);
end

function _MissionSelectScene_LeaveMainLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	game.RemoveAllChildren({toplayer, layertag});
end

function MissionSelectScene_OnEnter(toplayer, toptag)
end

function MissionSelectScene_OnEnterTDF(toplayer, toptag)
	_MissionSelectScene_EnterMainLayer(toplayer, toptag);
end
function MissionSelectScene_OnExit(toplayer, toptag)
end
function MissionSelectScene_OnTouchBegin(toplayer, toptag)
end
function MissionSelectScene_OnTouchEnd(toplayer, toptag)
end