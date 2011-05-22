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