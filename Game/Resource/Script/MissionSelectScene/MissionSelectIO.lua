function MissionSelectScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return MissionSelectScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return MissionSelectScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return MissionSelectScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return MissionSelectScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return MissionSelectScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return MissionSelectScene_OnTouchEnd(toplayer, toptag);
	end
end

function MissionSelectScene_OnInit(toplayer, toptag)
end

function MissionSelectScene_OnEnter(toplayer, toptag)
end
function MissionSelectScene_OnEnterTDF(toplayer, toptag)
end
function MissionSelectScene_OnExit(toplayer, toptag)
end
function MissionSelectScene_OnTouchBegin(toplayer, toptag)
end
function MissionSelectScene_OnTouchEnd(toplayer, toptag)
end