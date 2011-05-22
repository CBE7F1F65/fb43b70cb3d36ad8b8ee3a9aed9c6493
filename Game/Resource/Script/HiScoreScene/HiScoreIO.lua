function HiScoreScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return HiScoreScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return HiScoreScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return HiScoreScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return HiScoreScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return HiScoreScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return HiScoreScene_OnTouchEnd(toplayer, toptag);
	end
end

function HiScoreScene_OnInit(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
end

function HiScoreScene_OnEnter(toplayer, toptag)
end
function HiScoreScene_OnEnterTDF(toplayer, toptag)
end
function HiScoreScene_OnExit(toplayer, toptag)
end
function HiScoreScene_OnTouchBegin(toplayer, toptag)
end
function HiScoreScene_OnTouchEnd(toplayer, toptag)
end