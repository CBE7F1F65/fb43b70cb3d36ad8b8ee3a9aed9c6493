function LoadingScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return LoadingScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return LoadingScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return LoadingScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return LoadingScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return LoadingScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return LoadingScene_OnTouchEnd(toplayer, toptag);
	end
end

function LoadingScene_OnInit(toplayer, toptag)
end

function LoadingScene_OnEnter(toplayer, toptag)
	
--	local sprite = game.CreateSprite(SI_TUI_Play);
--	local sprite2 = game.CreateSprite(SI_TUI_Play_Down);
--	local menu = game.CreateMenuItem({toptag}, {240, 240, 0, toptag+1}, sprite, sprite2);
--	local sprite21 = game.CreateSprite(SI_TUI_Play);
--	local sprite22 = game.CreateSprite(SI_TUI_Play_Down);
--	local menu2 = game.CreateMenuItem({toptag}, {240, 600, 0, toptag+2}, sprite21, sprite22);
--	local menu3 = game.CreateMenuItem({toptag}, {480, 600, 0, toptag+3}, "AAAAAAA", 20)
--	game.AddMenuChild({menu, menu2, menu3}, {toptag}, {0, 0, 0, toptag+10});

	game.ReplaceScene(ktag_TitleSceneLayer, g_SceneTransTime)
	
end
function LoadingScene_OnEnterTDF(toplayer, toptag)
end
function LoadingScene_OnExit(toplayer, toptag)
end
function LoadingScene_OnTouchBegin(toplayer, toptag)
end
function LoadingScene_OnTouchEnd(toplayer, toptag)
end