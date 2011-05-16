function LoadingScene_IO(eventtype)
	
	if eventtype == SceneIOFlag_OnInit then
		return LoadingScene_OnInit();
	elseif eventtype == SceneIOFlag_OnEnter then
		return LoadingScene_OnEnter();
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return LoadingScene_OnEnterTDF();
	elseif eventtype == SceneIOFlag_OnExit then
		return LoadingScene_OnExit();
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return LoadingScene_OnTouchBegin();
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return LoadingScene_OnTouchEnd();
	end
end

function LoadingScene_OnInit()
end
function LoadingScene_OnEnter()
	local sprite = game.CreateSprite(SI_TUI_Play);
	local sprite2 = game.CreateSprite(SI_TUI_Play_Down);
	local menu = game.CreateMenuItem({ktag_LoadingSceneLayer}, {240, 240, 0, ktag_LoadingSceneLayer+1}, sprite, sprite2);
	local sprite21 = game.CreateSprite(SI_TUI_Play);
	local sprite22 = game.CreateSprite(SI_TUI_Play_Down);
	local menu2 = game.CreateMenuItem({ktag_LoadingSceneLayer}, {240, 600, 0, ktag_LoadingSceneLayer+2}, sprite21, sprite22);
	game.AddMenuChild({menu, menu2}, {ktag_LoadingSceneLayer}, {0, 0, 0, ktag_LoadingSceneLayer+10});
end
function LoadingScene_OnEnterTDF()
end
function LoadingScene_OnExit()
end
function LoadingScene_OnTouchBegin()
end
function LoadingScene_OnTouchEnd()
end