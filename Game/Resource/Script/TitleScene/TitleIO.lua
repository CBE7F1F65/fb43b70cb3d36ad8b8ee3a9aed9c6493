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
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local spTitle = game.CreateSprite(SI_TitleScene, {480, 320});
	game.AddSpriteChild(spTitle, {layertag});
	
end

function TitleScene_OnEnter(toplayer, toptag)
end

function TitleScene_OnEnterTDF(toplayer, toptag)
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spTitleMenus = {};
	local spTitleSelectedMenus = {};
	local menus = {};
	local layertag = toptag + CCTag_Layer_00;
	local grouptag = layertag + CCTag_Menu_00;
	for i=0, 4 do
		local y = ybegin - i*yoffset;
		
		spTitleMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2, {}, grouptag+CCTag_MenuSub_00+i+1);
		spTitleSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2, {}, grouptag+CCTag_MenuSub_01+i+1);
		menus[i+1] = game.CreateMenuItem({layertag}, {xorig, y, CCTag_Menu_00, grouptag+i+1}, spTitleMenus[i+1], spTitleSelectedMenus[i+1]);
		
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
	
	game.AddMenuChild(menus, {layertag}, {0, 0, CCTag_Menu_00, grouptag});
	
end
function TitleScene_OnExit(toplayer, toptag)
end
function TitleScene_OnTouchBegin(toplayer, toptag)
end
function TitleScene_OnTouchEnd(toplayer, toptag)
end