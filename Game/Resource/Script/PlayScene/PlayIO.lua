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
	
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toptag}, {0, 0, CCTag_Layer_00, layertag});
			
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