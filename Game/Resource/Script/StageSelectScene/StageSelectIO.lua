function StageSelectScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return StageSelectScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return StageSelectScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return StageSelectScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return StageSelectScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return StageSelectScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return StageSelectScene_OnTouchEnd(toplayer, toptag);
	end
end

function StageSelectScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	
	-- bg layer
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local spStageSelect = game.CreateSprite(SI_StageSelectScene, {480, 320});
	game.AddSpriteChild(spStageSelect, {toplayer, layertag});
	
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
end

function StageSelectScene_OnEnter(toplayer, toptag)

end


function _StageSelectScene_AddMainItems(toplayer, toptag)
	
	local width, height = game.GetSIData(SI_SSUI_Locked);
	local margin = 30;
	
	local xcen = {};
	local ycen = {};
	
	for i=0, 2 do
		for j=1, 3 do
			xcen[i*3+j] = 480 + (j-2) * (width+margin);
			ycen[i*3+j] = 320 + (1-i) * (height+margin);
		end
	end
	
	for j=1, 3 do
		xcen[6+j] = xcen[6+j] + 80;
	end
	
	
	local spMenus = {};
	local spSelectedMenus = {};
	local spDisabledMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	
	for i=0, 8 do
		
		local enabled = true;
		if i < 8 then
			
			if not game.StageIsEnabled(i) then
				enabled = false;
			end
			
			spMenus[i+1] = game.CreateSprite(SI_SSUI_World_1+i);
			spSelectedMenus[i+1] = game.CreateSprite(SI_SSUI_World_1_Down+i);
			spDisabledMenus[i+1] = game.CreateSprite(SI_SSUI_Locked);
		else
			spMenus[i+1] = game.CreateSprite(SI_TUI_Exit);
			spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Exit_Down);
			spDisabledMenus[i+1] = nil;
		end
		
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xcen[i+1]+40, ycen[i+1]+40, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1], spDisabledMenus[i+1]);
		
		if not enabled then
			game.SetMenuItemEnabled(menus[i+1], false);
		end

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen[i+1], ycen[i+1], fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, blinktimepre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _StageSelectScene_EnterMainLayer(toplayer, toptag)
	_StageSelectScene_AddMainItems(toplayer, toptag);
end

function _StageSelectScene_LeaveMainLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	game.RemoveAllChildren({toplayer, layertag});
end


function StageSelectScene_OnEnterTDF(toplayer, toptag)	
	_StageSelectScene_EnterMainLayer(toplayer, toptag);	
end
function StageSelectScene_OnExit(toplayer, toptag)
end
function StageSelectScene_OnTouchBegin(toplayer, toptag)
end
function StageSelectScene_OnTouchEnd(toplayer, toptag)
end