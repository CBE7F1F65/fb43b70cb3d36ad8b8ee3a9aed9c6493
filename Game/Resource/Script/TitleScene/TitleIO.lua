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
	layertag = toptag + CCSTL_BG;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCSTL_BG, layertag});
	
	local spTitle = game.CreateSprite(SI_TitleScene, {480, 320});
	game.AddSpriteChild(spTitle, {toplayer, layertag});
	
	-- menu layer
	layertag = toptag + CCTSTL_Menu;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_Menu, layertag});
	
	-- hiscore layer
	layertag = toptag + CCTSTL_HiScore;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_HiScore, layertag});
	
	-- Option layer
	layertag = toptag + CCTSTL_Option;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_Option, layertag});
	-- BGMVol touch layer
	layertag = toptag + CCTSTL_BGMTouch;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_BGMTouch, layertag});
	-- SEVol touch layer
	layertag = toptag + CCTSTL_SETouch;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_SETouch, layertag});
	
	-- Online layer
	layertag = toptag + CCTSTL_Online;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_Online, layertag});
	
	-- input layer
	layertag = toptag + CCTSTL_Input;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTSTL_Input, layertag});
	
	
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
	local layertag = toptag + CCTSTL_Menu;
	local grouptag = layertag + CCTSTM_Menu_Main;
	for i=0, 4 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTSTM_Menu_Main, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTSTM_Menu_Main, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _TitleScene_RunInputHintAction(toplayer, layertag)
	local spritehint = game.GetNode({toplayer, layertag+CCTSTM_Input_Hint});
	local inputhintactionpre = game.ActionTint(CCAF_To, 0xff7f7f, 0.3);
	local inputhintactionpost = game.ActionTint(CCAF_To, 0xffffff, 0.5);
	local inputhintaction = game.ActionSequence({inputhintactionpre, inputhintactionpost});
	game.RunAction(spritehint, inputhintaction, true);
end

function _TitleScene_StopInputHintAction(toplayer, layertag)
	local spritehint = game.GetNode({toplayer, layertag+CCTSTM_Input_Hint});
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
	local layertag = toptag + CCTSTL_Input;
	
	local text, inputmax = game.GetUsername();
	local defaulttext = "Your Name";
	
	local spritebg = game.CreateSprite(SI_White, {xcen, ycen, 0, width, height});
	game.AddSpriteChild(spritebg, {toplayer, layertag});
	game.SetColor(spritebg, global.ARGB(0x1f, 0xffffff));
		
	local inputlayer = game.AddInputLayerChild(
			{toplayer, {x, y, width, height}, text, "",  LConst_FontSize, inputmax, defaulttext},
			{toplayer, layertag},
			{0, 0, CCTSTL_Input, layertag+CCTSTM_Input_Layer}
		);
		
	local spritehint = game.CreateSprite(SI_TUI_InputHint, {480, 450}, layertag+CCTSTM_Input_Hint);
	game.AddSpriteChild(spritehint, {toplayer, layertag});
	if text == "" then
		_TitleScene_RunInputHintAction(toplayer, layertag);
	end
	
end

function _TitleScene_PauseMenuLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Menu;
	local grouptag = layertag + CCTSTM_Menu_Main;
	local menulayer = game.GetNode({toplayer, grouptag});
	game.SetTouchEnabled(menulayer, false);
end

function _TitleScene_ResumeMenuLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Menu;
	local grouptag = layertag + CCTSTM_Menu_Main;
	local menulayer = game.GetNode({toplayer, grouptag});
	game.SetTouchEnabled(menulayer, true);
end



function _TitleScene_EnterMainLayer(toplayer, toptag)
	_TitleScene_AddMainItems(toplayer, toptag);
	_TitleScene_AddInputLayer(toplayer, toptag);
end

function _TitleScene_LeaveMainLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Menu;
	game.RemoveAllChildren({toplayer, layertag});
	local layertag = toptag + CCTSTL_Input;
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
