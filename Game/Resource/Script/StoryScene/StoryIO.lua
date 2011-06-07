function StoryScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return StoryScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return StoryScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return StoryScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return StoryScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return StoryScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return StoryScene_OnTouchEnd(toplayer, toptag);
	end
end

function StoryScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	
	-- bg layer
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
		
	-- menu layer
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
			
end

function StoryScene_OnEnter(toplayer, toptag)
end

function _StoryScene_AddStoryItems(toplayer, toptag)
	local xorig = 1200;
	local xcen = 800;
	local y = 120
	
	local layertag = toptag + CCTag_Layer_01;
	local grouptag = layertag + CCTag_Menu_01;
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
--	for i=0, 2 do
	local i = 0;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Back);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Back_Down);
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);
		
		local fadetime = 0.3+i*0.01;
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
		
--	end
	game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
end

function StoryScene_OnEnterTDF(toplayer, toptag)
	_StoryScene_AddStoryItems(toplayer, toptag);
end

function StoryScene_OnExit(toplayer, toptag)
end
function StoryScene_OnTouchBegin(toplayer, toptag)
end
function StoryScene_OnTouchEnd(toplayer, toptag)
end