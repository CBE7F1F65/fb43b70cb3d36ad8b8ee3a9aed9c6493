function OptionScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return OptionScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return OptionScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return OptionScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return OptionScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return OptionScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return OptionScene_OnTouchEnd(toplayer, toptag);
	end
end

function OptionScene_OnInit(toplayer, toptag)
end

function OptionScene_OnEnter(toplayer, toptag)
end
function OptionScene_OnEnterTDF(toplayer, toptag)
end
function OptionScene_OnExit(toplayer, toptag)
end
function OptionScene_OnTouchBegin(toplayer, toptag)
end
function OptionScene_OnTouchEnd(toplayer, toptag)
end