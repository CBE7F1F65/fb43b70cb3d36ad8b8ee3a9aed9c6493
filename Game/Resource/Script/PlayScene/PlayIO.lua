function PlayScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return PlayScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return PlayScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return PlayScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return PlayScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return PlayScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return PlayScene_OnTouchEnd(toplayer, toptag);
	end
end

function PlayScene_OnInit(toplayer, toptag)
	local spPlay = game.CreateSprite(SI_PlayScene, {480, 320});
	game.AddSpriteChild(spPlay, {toptag});
	
	local xcen = 780;
	local ybegin = 500;
	local yoffset = 108;
	
	local spPlayMenus = {};
	local spPlaySelectedMenus = {};
	local menus = {};
	for i=0, 4 do
		spPlayMenus[i+1] = game.CreateSprite(SI_TUI_Play+i*2);
		spPlaySelectedMenus[i+1] = game.CreateSprite(SI_TUI_Play_Down+i*2);
		menus[i+1] = game.CreateMenuItem({toptag}, {xcen, ybegin-yoffset*i, CCZOrder_Menu_00, toptag+CCTag_Menu_00+i+1}, spPlayMenus[i+1], spPlaySelectedMenus[i+1]);
	end
	
	game.AddMenuChild(menus, {toptag}, {0, 0, CCZOrder_Menu_00});
	
end

function PlayScene_OnEnter(toplayer, toptag)
end
function PlayScene_OnEnterTDF(toplayer, toptag)
end
function PlayScene_OnExit(toplayer, toptag)
end
function PlayScene_OnTouchBegin(toplayer, toptag)
end
function PlayScene_OnTouchEnd(toplayer, toptag)
end