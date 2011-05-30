function HelpScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return HelpScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return HelpScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return HelpScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return HelpScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return HelpScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return HelpScene_OnTouchEnd(toplayer, toptag);
	end
end

function HelpScene_OnInit(toplayer, toptag)

	local layertag = toptag;
	
	-- bg layer
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local spHelp = game.CreateSprite(SI_HelpScene, {480, 320});
	game.AddSpriteChild(spHelp, {toplayer, layertag});
		
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
	-- sub layer
	layertag = toptag + CCTag_Layer_04;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_04, layertag});
end

function HelpScene_OnEnter(toplayer, toptag)
end

function _HelpScene_AddHelpItems(toplayer, toptag)
	
	local helptype, helpindex = game.GetHelpAccessInfo();
	
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 3 do
		local y = ybegin - i*yoffset;
		if i == 3 then
			y = y-yoffset;
		end
		
		spMenus[i+1] = game.CreateSprite(SI_HUI_Back+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_HUI_Back_Down+i*2);
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);
		
		local fadetime = 0.3+i*0.01;
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
		
		if helptype == 0 and i < 3 then
			game.SetTouchEnabled(menus[i+1], false);
			game.SetIsVisible(menus[i+1], false);
		end
		
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _HelpScene_AddHelpCatagoryItems(toplayer, toptag)
				
	local xorig = 740;
	local xcen = 340;
	local ybegin = 540;
	local yoffset = 108;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_02;
	for i=0, 4 do
		
		local enabled = true;
		if not game.GetHelpAccessInfo(i+1, -1) then
			enabled = false;
		end
		
		local y = ybegin - i*yoffset;
		
		if enabled then
			spMenus[i+1] = game.CreateSprite(SI_HUI_HowToPlay+i*2);
			spSelectedMenus[i+1] = game.CreateSprite(SI_HUI_HowToPlay_Down+i*2);
		else
			spMenus[i+1] = game.CreateSprite(SI_HUI_Locked);
			spSelectedMenus[i+1] = game.CreateSprite(SI_HUI_Locked_Down);
		end
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_02, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);
		
		if not enabled then
			game.SetMenuItemEnabled(menus[i+1], false);
		end
		
		local fadetime = 0.3+i*0.01;
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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_02, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
end

function _HelpScene_EnterCatagoryMenu(toplayer, toptag)
	_HelpScene_AddHelpCatagoryItems(toplayer, toptag);
end

function _HelpScene_LeaveCatagoryMenu(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_02;
	game.RemoveChild({toplayer, grouptag});
end

function _HelpScene_EnterSubLayer(toplayer, toptag, helptype, helpindex)
	layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 2 do
		local menuitem = game.GetNode({toplayer, grouptag+i+1});
		game.SetTouchEnabled(menuitem, true);
		game.SetIsVisible(menuitem, true);
	end
	_HelpScene_ChangeSubLayerItems(toplayer, toptag, helptype, helpindex);
end

function _HelpScene_LeaveSubLayer(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_04;
	game.RemoveAllChildren({toplayer, layertag});
	
	layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 2 do
		local menuitem = game.GetNode({toplayer, grouptag+i+1});
		game.SetTouchEnabled(menuitem, false);
		game.SetIsVisible(menuitem, false);
	end
	
end



function HelpScene_OnEnterTDF(toplayer, toptag)
	
	_HelpScene_AddHelpItems(toplayer, toptag);
	
	local helptype, helpindex = game.GetHelpAccessInfo();
	if helptype ~= 0 then
		_HelpScene_EnterSubLayer(toplayer, toptag);
	else
		_HelpScene_AddHelpCatagoryItems(toplayer, toptag);
	end
	
end

function HelpScene_OnExit(toplayer, toptag)
end
function HelpScene_OnTouchBegin(toplayer, toptag)
end
function HelpScene_OnTouchEnd(toplayer, toptag)
end




function _HelpScene_ChangeSubLayerItems(toplayer, toptag, helptype, helpindex)
	
	if helptype == nil or helpindex == nil then
		helptype, helpindex = game.GetHelpAccessInfo();
	end
	
	local layertag = toptag + CCTag_Layer_04;
	game.RemoveAllChildren({toplayer, layertag});
	
end