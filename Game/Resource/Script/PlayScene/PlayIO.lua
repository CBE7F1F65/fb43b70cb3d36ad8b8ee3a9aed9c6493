function PlayScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return PlayScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return PlayScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterA then
		return PlayScene_OnEnterA(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return PlayScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDFA then
		return PlayScene_OnEnterTDFA(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnUpdate then
		return PlayScene_OnUpdate(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return PlayScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return PlayScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return PlayScene_OnTouchEnd(toplayer, toptag);
	end
end

function _PlayScene_AddBGItems(toplayer, toptag)
	
	local layertag = toptag+CCTag_Layer_00;
	
	local bgsiid = game.GetMissionBGData();
	local spBG = game.CreateSprite(bgsiid, {480, 336});
	game.AddSpriteChild(spBG, {toplayer, layertag});
		
end

function _PlayScene_AddFrameItems(toplayer, toptag)
	local layertag = toptag+CCTag_Layer_05;
	
	local spTopPanel = game.CreateSprite(SI_GUI_TopPanel, {480, 608});
	game.AddSpriteChild(spTopPanel, {toplayer, layertag});
	local spBottomPanel = game.CreateSprite(SI_GUI_BottomPanel, {480, 48});
	game.AddSpriteChild(spBottomPanel, {toplayer, layertag});
	local spLeftPanel = game.CreateSprite(SI_GUI_LeftPanel, {32, 368});
	game.AddSpriteChild(spLeftPanel, {toplayer, layertag});
	local spRightPanel = game.CreateSprite(SI_GUI_RightPanel, {928, 368});
	game.AddSpriteChild(spRightPanel, {toplayer, layertag});
end

function PlayScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	local grouptag = layertag;
	
	-- BG
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	_PlayScene_AddBGItems(toplayer, toptag);
	
	-- ObjBG
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
	-- Enemies
	layertag = toptag + CCTag_Layer_02;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_02, layertag});
	
	-- ObjFG
	layertag = toptag + CCTag_Layer_03;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_03, layertag});
	
	-- Message
	layertag = toptag + CCTag_Layer_04;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_04, layertag});
	
	-- Frame
	layertag = toptag + CCTag_Layer_05;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_05, layertag});
	
	_PlayScene_AddFrameItems(toplayer, toptag);
	
	-- Touch
	layertag = toptag + CCTag_Layer_06;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_06, layertag});
	
	-- HPAPSP
	layertag = toptag + CCTag_Layer_07;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_07, layertag});
	
	-- Enemies On Side
	layertag = toptag + CCTag_Layer_08;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_08, layertag});
	
	-- Menu
	layertag = toptag + CCTag_Layer_10;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_10, layertag});
	
	
	-- Clear GameOver
	layertag = toptag + CCTag_Layer_12;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_12, layertag});
	
	LGlobal_PlayScene_InitGlobal(toplayer, toptag);
			
end

function PlayScene_OnEnter(toplayer, toptag)
	game.EnterMission();
end

function _PlayScene_AddHPAPSPItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_07;
	local grouptag = layertag + CCTag_Menu_01;
	
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	
	local x = 232.5;
	local y = 112;
	
	for i=0, 1 do
		if i == 1 then
			x = 960 - x;
		end
		local width, height = game.GetSIData(SI_GUI_HP_Bar+i*2);
		
		local spBar = game.CreateSprite(SI_GUI_HP_Bar+i*2, {x-width/2, y-height/2}, grouptag+i+1);
		local nodebar = game.AddSpriteChild(spBar, {toplayer, layertag, grouptag});
		game.SetAnchor(nodebar, 0, 0);
		game.SetScale(nodebar, 0, 1);
		
		local spFrame = game.CreateSprite(SI_GUI_HP_Frame+i*2, {x, y});
		game.AddSpriteChild(spFrame, {toplayer, layertag, grouptag});
		
		local spTitle = game.CreateSprite(SI_GUI_HP+i, {x, y});
		game.AddSpriteChild(spTitle, {toplayer, layertag, grouptag});
	end
	
	grouptag = layertag + CCTag_Menu_02;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	local xorig = 432;
	for i=0, 3 do
		x = xorig + i*32;
		
		local spSP = game.CreateSprite(SI_GUI_SP, {x, y}, grouptag+i+1);
		local nodesp = game.AddSpriteChild(spSP, {toplayer, layertag, grouptag});
		game.SetColor(nodesp, global.ARGB(0, 0xffffff));
		
	end
		
end

function _PlayScene_AddMainItems(toplayer, toptag)
	
	local xbegin = 168;
	local xoffset = 208;
	local yorig = -48;
	local y = 48;
		
	local spMenus = {};
	local spSelectedMenus = {};
	local spDisabledMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_10;
	local grouptag = layertag + CCTag_Menu_01;
	
	for i=0, 3 do
		local x = xbegin + i*xoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command+i*3);
		spSelectedMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command_Down+i*3);
		spDisabledMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command_Disabled+i*3);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {x, yorig, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1], spDisabledMenus[i+1]);

		local fadetime = 0.3+i*0.03;
		local menumoveaction = game.ActionMove(CCAF_To, x, y, fadetime);
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

function _PlayScene_SetHPAPSP(toplayer, toptag)
	
	local hp, ap, sp = game.GetHPAPSP();
	
	local layertag = toptag + CCTag_Layer_07;
	local grouptag = layertag + CCTag_Menu_01;
	
	local hpbar = game.GetNode({toplayer, layertag, grouptag, grouptag+1});
	local apbar = game.GetNode({toplayer, layertag, grouptag, grouptag+2});
	
	if LGlobal_PlayData.nowhp ~= hp then
		LGlobal_PlayData.nowhp = hp;
		if hp < 0 then
			hp = 0;
		end
		local hpscaleaction = game.ActionScale(CCAF_To, hp/10000.0, 1, LConst_HPAPChangeTime, true);
		game.RunAction(hpbar, hpscaleaction);
	end
	
	if LGlobal_PlayData.nowap ~= ap then
		LGlobal_PlayData.nowap = ap;
		if ap < 0 then
			ap = 0;
		end
		local apscaleaction = game.ActionScale(CCAF_To, ap/10000.0, 1, LConst_HPAPChangeTime, true);
		game.RunAction(apbar, apscaleaction);
	end
	
	local grouptag = layertag + CCTag_Menu_02;
	
	if LGlobal_PlayData.nowsp ~= sp then
		local nowsp = LGlobal_PlayData.nowsp;
		LGlobal_PlayData.nowsp = sp;
		
		if nowsp > sp then
			for i=sp, nowsp do
				local spitem = game.GetNode({toplayer, layertag, grouptag, grouptag+i});
				local spfadeaction = game.ActionFade(CCAF_To, 0, LConst_SPChangeTime);
				game.RunAction(spitem, spfadeaction);
			end
		else
			for i=nowsp, sp do
				local spitem = game.GetNode({toplayer, layertag, grouptag, grouptag+i});
				local spfadeaction = game.ActionFade(CCAF_To, 0xFF, LConst_SPChangeTime);
				game.RunAction(spitem, spfadeaction);
			end
		end
	end
	
	
end

function _PlayScene_AddTouchLayer(toplayer, toptag)
	
	local xcen = 480;
	local ycen = 272;
	local width = 960;
	local height = 544;
	
	local layertag = toptag + CCTag_Layer_06;
	
	local touchlayer = game.AddTouchLayerChild(
			{toplayer, {x, y, width, height}},
			{toplayer, layertag},
			{0, 0, CCTag_Layer_06, layertag+CCTag_Menu_01}
		);
	
end

function PlayScene_OnEnterA(toplayer, toptag)
	LGlobal_PlayData.btrasitioning = true;
end

function PlayScene_OnEnterTDF(toplayer, toptag)
	_PlayScene_AddMainItems(toplayer, toptag);
	_PlayScene_AddHPAPSPItems(toplayer, toptag);
	_PlayScene_SetHPAPSP(toplayer, toptag);
	
	_PlayScene_AddTouchLayer(toplayer, toptag);
end

function PlayScene_OnEnterTDFA(toplayer, toptag)
	if LGlobal_PlayData.btrasitioning then
		LGlobal_PlayData.btrasitioning = false;
	end
	
	_PlayScene_StepForward(STATE_ShowHelp);

end


function PlayScene_OnUpdate(toplayer, toptag)
	
	if LGlobal_PlayData.btrasitioning then
		return
	end
	
	game.Update();
	
	_PlayScene_UpdateState(toplayer, toptag);
		
	_PlayScene_SetHPAPSP(toplayer, toptag);
	
end

function PlayScene_OnExit(toplayer, toptag)
end
function PlayScene_OnTouchBegin(toplayer, toptag)
end
function PlayScene_OnTouchEnd(toplayer, toptag)
end