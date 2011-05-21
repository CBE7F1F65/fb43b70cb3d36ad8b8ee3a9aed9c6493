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
	
	-- menus layer
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	local spTitle = game.CreateSprite(SI_TitleScene, {480, 320});
	game.AddSpriteChild(spTitle, {layertag});
	
	-- input layer
	layertag = toptag + CCTag_Layer_13;
	game.AddNullChild({toptag}, {0, 0, CCTag_Layer_13, layertag});
	
	
end

function TitleScene_OnEnter(toplayer, toptag)
end

function _TitleScene_AddMenus(toptag)
	
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
		
		spTitleMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2);--, {}, grouptag+CCTag_MenuSub_00+i+1);
		spTitleSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2);--, {}, grouptag+CCTag_MenuSub_01+i+1);
		menus[i+1] = game.CreateMenuItem({layertag}, {xorig, y, CCTag_Menu_00, grouptag+i+1}, spTitleMenus[i+1], spTitleSelectedMenus[i+1]);
		
		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(xcen, y, fadetime);
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
	
	game.AddMenuChild(menus, {layertag}, {0, 0, CCTag_Menu_00, grouptag});
	
end

function _TitleScene_AddInputLayer(toptag)
	
	local x = 200;
	local y = 480;
	local width = 320;
	local height = 20;
	local layertag = toptag + CCTag_Layer_13;
	
	local text, inputmax = game.GetUsername();
	local defaulttext = "Your Name";
	
	local inputlayer = game.AddInputLayerChild(
			{{x-width/2, y-height/2, width, height}, text, "",  LConst_FontSize, inputmax, defaulttext},
			{layertag},
			{0, 0, CCTag_Layer_13, layertag+CCTag_Menu_00}
		);
end

function TitleScene_OnEnterTDF(toplayer, toptag)
	
	_TitleScene_AddMenus(toptag);
	_TitleScene_AddInputLayer(toptag);
	
	
	
end
function TitleScene_OnExit(toplayer, toptag)
end
function TitleScene_OnTouchBegin(toplayer, toptag)
end
function TitleScene_OnTouchEnd(toplayer, toptag)
end