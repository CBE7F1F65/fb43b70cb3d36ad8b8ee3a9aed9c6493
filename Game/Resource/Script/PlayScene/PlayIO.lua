function PlayScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return PlayScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return PlayScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterA then
		return PlayScene_OnEnterA(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return PlayScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDFA then
		return PlayScene_OnEnterTDFA(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnUpdate then
		return PlayScene_OnUpdate(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return PlayScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return PlayScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return PlayScene_OnTouchEnd(toplayer, toptag);
	end
end

function PlayScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	local grouptag = layertag;
	
	-- BG
	layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	PS_AddBGItems(toplayer, toptag);
	
	-- ObjBG
	layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
	-- Enemies
	layertag = toptag + CCTag_Layer_02;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_02, layertag});
	
	-- ObjFG
	layertag = toptag + CCTag_Layer_03;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_03, layertag});
	
	-- Message
	layertag = toptag + CCTag_Layer_04;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_04, layertag});
	-- Target/Turn/Mission Over
	grouptag = layertag + CCTag_Menu_01;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	
	-- Frame
	layertag = toptag + CCTag_Layer_05;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_05, layertag});
	
	PS_AddFrameItems(toplayer, toptag);
	
	-- Touch
	layertag = toptag + CCTag_Layer_06;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_06, layertag});
	
	-- HPAPSP
	layertag = toptag + CCTag_Layer_07;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_07, layertag});
	
	-- Enemies On Side
	layertag = toptag + CCTag_Layer_08;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_08, layertag});
	
	-- Plan
	layertag = toptag + CCTag_Layer_11;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_11, layertag});
	-- RenderTexture
	grouptag = layertag + CCTag_Menu_01;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	-- feathers
	grouptag = layertag + CCTag_Menu_04;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_04, grouptag});
	grouptag = layertag + CCTag_Menu_05;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_05, grouptag});
	grouptag = layertag + CCTag_Menu_06;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_06, grouptag});
	
	PS_AddPlanningRenderTexture(toplayer, toptag);
	
	-- Clear GameOver ??
	layertag = toptag + CCTag_Layer_12;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_12, layertag});
	
	-- Menu
	layertag = toptag + CCTag_Layer_13;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_13, layertag});
	-- Menu Indicators
	grouptag = layertag + CCTag_Menu_02;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_02, grouptag});
		
	-- Overlay
	local overlaylayer = game.AddOverlayLayerChild(toplayer, {0, 0, CCZ_Max});
	-- Sniper Scope
	layertag = ktag_OverlayLayer + CCTag_Layer_01;
	game.AddNullChild({overlaylayer, ktag_OverlayLayer}, {0, 0, CCTag_Layer_01, layertag});
	grouptag = layertag + CCTag_Menu_01;
	game.AddNullChild({overlaylayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
			
end

function PlayScene_OnEnter(toplayer, toptag)
	LGlobalPS_InitGlobal(toplayer, toptag);
	game.EnterMission();
end

function PlayScene_OnEnterA(toplayer, toptag)
	LGlobal_PlayData.btrasitioning = true;
end

function PlayScene_OnEnterTDF(toplayer, toptag)
	PS_AddMainItems(toplayer, toptag);
	PS_AddHPAPSPItems(toplayer, toptag);
	PS_SetHPAPSP(toplayer, toptag);
	
	PS_AddTouchLayer(toplayer, toptag);
end

function PlayScene_OnEnterTDFA(toplayer, toptag)
	if LGlobal_PlayData.btrasitioning then
		LGlobal_PlayData.btrasitioning = false;
	end
	
	PS_StepForward(STATE_ShowHelp);

end


function PlayScene_OnUpdate(toplayer, toptag)
	
	if LGlobal_PlayData.btrasitioning then
		return
	end
	
	game.Update();
	
	PS_UpdateState(toplayer, toptag);
		
	PS_SetHPAPSP(toplayer, toptag);
	
end

function PlayScene_OnExit(toplayer, toptag)
end
function PlayScene_OnTouchBegin(toplayer, toptag)
end
function PlayScene_OnTouchEnd(toplayer, toptag)
end