function StageSelectScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return StageSelectScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return StageSelectScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return StageSelectScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return StageSelectScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return StageSelectScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return StageSelectScene_OnTouchEnd(toplayer, toptag);
	end
end

function StageSelectScene_OnInit(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
end

function StageSelectScene_OnEnter(toplayer, toptag)
end
function StageSelectScene_OnEnterTDF(toplayer, toptag)
end
function StageSelectScene_OnExit(toplayer, toptag)
end
function StageSelectScene_OnTouchBegin(toplayer, toptag)
end
function StageSelectScene_OnTouchEnd(toplayer, toptag)
end