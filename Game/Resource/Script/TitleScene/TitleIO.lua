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
	local spTitle = game.CreateSprite(SI_TitleScene, {480, 320});
	game.AddSpriteChild(spTitle, {toptag});
	
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spTitleMenus = {};
	local spTitleSelectedMenus = {};
	local menus = {};
	for i=0, 4 do
		spTitleMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2);
		spTitleSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2);
		menus[i+1] = game.CreateMenuItem({toptag}, {xcen, ybegin-yoffset*i, CCZOrder_Menu_00, toptag+CCTag_Menu_00+i+1}, spTitleMenus[i+1], spTitleSelectedMenus[i+1]);
	end
	
	game.AddMenuChild(menus, {toptag}, {0, 0, CCZOrder_Menu_00});
	
end

function TitleScene_OnEnter(toplayer, toptag)
end
function TitleScene_OnEnterTDF(toplayer, toptag)
end
function TitleScene_OnExit(toplayer, toptag)
end
function TitleScene_OnTouchBegin(toplayer, toptag)
end
function TitleScene_OnTouchEnd(toplayer, toptag)
end