function TitleScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return TitleScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return TitleScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return TitleScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return TitleScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return TitleScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return TitleScene_OnTouchEnd(toplayer, toptag);
	end
end

function TitleScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	
	-- bg layer
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local spTitle = game.CreateSprite(SI_TitleScene, {480, 320});
	game.AddSpriteChild(spTitle, {toplayer, layertag});
	
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
	-- hiscore layer
	layertag = toptag + CCTag_Layer_03;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_03, layertag});
	
	-- Option layer
	layertag = toptag + CCTag_Layer_05;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_05, layertag});
	-- BGMVol touch layer
	layertag = toptag + CCTag_Layer_06;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_06, layertag});
	-- SEVol touch layer
	layertag = toptag + CCTag_Layer_07;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_07, layertag});
	
	-- Online layer
	layertag = toptag + CCTag_Layer_09;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_07, layertag});
	
	-- input layer
	layertag = toptag + CCTag_Layer_13;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_13, layertag});
	
	
end

function TitleScene_OnEnter(toplayer, toptag)
end

function _TitleScene_AddMainItems(toplayer, toptag)
	
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 4 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
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

function _TitleScene_RunInputHintAction(toplayer, layertag)
	local spritehint = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_13});
	local inputhintactionpre = game.ActionTint(CCAF_To, 0xff7f7f, 0.3);
	local inputhintactionpost = game.ActionTint(CCAF_To, 0xffffff, 0.5);
	local inputhintaction = game.ActionSequence({inputhintactionpre, inputhintactionpost});
	game.RunAction(spritehint, inputhintaction, true);
end

function _TitleScene_StopInputHintAction(toplayer, layertag)
	local spritehint = game.GetNode({toplayer, layertag, layertag+CCTag_Menu_13});
	game.StopAction(spritehint);
	game.SetColor(spritehint, global.ARGB(0xff, 0xffffff));
end

function _TitleScene_AddInputLayer(toplayer, toptag)
	
	local xcen = 200;
	local ycen = 450;
	local width = 336;
	local height = 50;
	local x = xcen - width / 2;
	local y = ycen - height / 2;
	local layertag = toptag + CCTag_Layer_13;
	
	local text, inputmax = game.GetUsername();
	local defaulttext = "Your Name";
	
	local spritebg = game.CreateSprite(SI_White, {xcen, ycen, 0, width, height});
	game.AddSpriteChild(spritebg, {toplayer, layertag});
	game.SetColor(spritebg, global.ARGB(0x1f, 0xffffff));
		
	local inputlayer = game.AddInputLayerChild(
			{toplayer, {x, y, width, height}, text, "",  LConst_FontSize, inputmax, defaulttext},
			{toplayer, layertag},
			{0, 0, CCTag_Layer_13, layertag+CCTag_Menu_01}
		);
		
	local spritehint = game.CreateSprite(SI_TUI_InputHint, {480, 450}, layertag+CCTag_Menu_13);
	game.AddSpriteChild(spritehint, {toplayer, layertag});
	if text == "" then
		_TitleScene_RunInputHintAction(toplayer, layertag);
	end
	
end

function _TitleScene_PauseMenuLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	local menulayer = game.GetNode({toplayer, layertag, grouptag});
	game.SetTouchEnabled(menulayer, false);
end

function _TitleScene_ResumeMenuLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	local menulayer = game.GetNode({toplayer, layertag, grouptag});
	game.SetTouchEnabled(menulayer, true);
end



function _TitleScene_EnterMainLayer(toplayer, toptag)
	_TitleScene_AddMainItems(toplayer, toptag);
	_TitleScene_AddInputLayer(toplayer, toptag);
end

function _TitleScene_LeaveMainLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	game.RemoveAllChildren({toplayer, layertag});
	local layertag = toptag + CCTag_Layer_13;
	game.RemoveAllChildren({toplayer, layertag});
end


function TitleScene_OnEnterTDF(toplayer, toptag)
	_TitleScene_EnterMainLayer(toplayer, toptag);	
end
function TitleScene_OnExit(toplayer, toptag)
end
function TitleScene_OnTouchBegin(toplayer, toptag)
end
function TitleScene_OnTouchEnd(toplayer, toptag)
end
