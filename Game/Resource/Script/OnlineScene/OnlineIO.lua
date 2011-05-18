function OnlineScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return OnlineScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return OnlineScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return OnlineScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return OnlineScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return OnlineScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return OnlineScene_OnTouchEnd(toplayer, toptag);
	end
end

function OnlineScene_OnInit(toplayer, toptag)
end

function OnlineScene_OnEnter(toplayer, toptag)
end
function OnlineScene_OnEnterTDF(toplayer, toptag)
end
function OnlineScene_OnExit(toplayer, toptag)
end
function OnlineScene_OnTouchBegin(toplayer, toptag)
end
function OnlineScene_OnTouchEnd(toplayer, toptag)
end