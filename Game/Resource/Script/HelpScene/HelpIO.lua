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
end

function HelpScene_OnEnter(toplayer, toptag)
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spTitleMenus = {};
	local spTitleSelectedMenus = {};
	local menus = {};
	local grouptag = toptag+CCTag_Menu_00;
	for i=0, 1 do
		local y = ybegin - i*yoffset;
		
		spTitleMenus[i+1] = game.CreateSprite(SI_TUI_Back+i*2, {}, grouptag+CCTag_MenuSub_00+i+1);
		spTitleSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Back_Down+i*2, {}, grouptag+CCTag_MenuSub_01+i+1);
		menus[i+1] = game.CreateMenuItem({toptag}, {xorig, y, CCZOrder_Menu_00, grouptag+i+1}, spTitleMenus[i+1], spTitleSelectedMenus[i+1]);
		
		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(xcen, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local spritealphaaction = {};
		local spritefadeinaction = {};
		local spriterepeatactionpre = {};
		local spriterepeatactionpost = {};
		local spriterepeataction = {};
		local spritealphaaction = {};
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		for j=0, 1 do
			spritefadeinaction[j+1] = game.ActionFade(CCAF_In, 0xff, fadetime);
			spriterepeatactionpre[j+1] = game.ActionFade(CCAF_To, 0x9F, blinktimepre);
			spriterepeatactionpost[j+1] = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
			spriterepeataction[j+1] = game.ActionSequence({spriterepeatactionpre[j+1], spriterepeatactionpost[j+1]});
			spriterepeataction[j+1] = game.ActionRepeat(spriterepeataction[j+1]);
			spritealphaaction[j+1] = game.ActionSequence({spritefadeinaction[j+1], spriterepeataction[j+1]});
		end
		game.RunAction(spTitleMenus[i+1], spritealphaaction[1]);
		game.RunAction(spTitleSelectedMenus[i+1], spritealphaaction[2]);
		
		game.RunAction(menus[i+1], menumoveaction);
		
	end
	
	game.AddMenuChild(menus, {toptag}, {0, 0, CCZOrder_Menu_00, grouptag});
	
end
function HelpScene_OnEnterTDF(toplayer, toptag)
end
function HelpScene_OnExit(toplayer, toptag)
end
function HelpScene_OnTouchBegin(toplayer, toptag)
end
function HelpScene_OnTouchEnd(toplayer, toptag)
end