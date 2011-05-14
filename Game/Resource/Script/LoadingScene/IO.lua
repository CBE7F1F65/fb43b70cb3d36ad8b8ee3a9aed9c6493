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
end
function LoadingScene_OnEnterTDF()
end
function LoadingScene_OnExit()
end
function LoadingScene_OnTouchBegin()
end
function LoadingScene_OnTouchEnd()
end