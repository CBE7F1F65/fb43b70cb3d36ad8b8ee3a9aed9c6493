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
		
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
end

function HelpScene_OnEnter(toplayer, toptag)
end

function _HelpScene_AddHelpItems(toplayer, toptag)
	
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 2 do
		local y = ybegin - i*yoffset;
		if i == 2 then
			y = y-yoffset
		end
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Back+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Back_Down+i*2);
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);
		
		local fadetime = 0.3+i*0.01;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, 0x9F, blinktimepre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		local menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	
end
function HelpScene_OnEnterTDF(toplayer, toptag)
	_HelpScene_AddHelpItems(toplayer, toptag);
end
function HelpScene_OnExit(toplayer, toptag)
end
function HelpScene_OnTouchBegin(toplayer, toptag)
end
function HelpScene_OnTouchEnd(toplayer, toptag)
end