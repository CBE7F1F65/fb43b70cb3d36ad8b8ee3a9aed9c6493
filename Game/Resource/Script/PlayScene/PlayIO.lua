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
	layertag = toptag + CCSTL_BG;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCSTL_BG, layertag});
	
	PS_AddBGItems(toplayer, toptag);
	
	-- ObjBG
	layertag = toptag + CCPSTL_ObjBG;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_ObjBG, layertag});
	
	-- Enemies
	layertag = toptag + CCPSTL_Enemy;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Enemy, layertag});
	
	-- ObjFG
	layertag = toptag + CCPSTL_ObjFG;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_ObjFG, layertag});
	
	-- Message
	layertag = toptag + CCPSTL_Message;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Message, layertag});
	-- Target/Turn
	grouptag = layertag + CCPSTM_Message_TargetBoard;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Message_TargetBoard, grouptag});
	-- Mission Over
	grouptag = layertag + CCPSTM_Message_OverBoard;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Message_OverBoard, grouptag});
	
	-- Frame
	layertag = toptag + CCPSTL_Frame;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Frame, layertag});
	
	PS_AddFrameItems(toplayer, toptag);
	
	-- Touch
	layertag = toptag + CCPSTL_Touch;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Touch, layertag});
	
	-- HPAPSP
	layertag = toptag + CCPSTL_HPAPSP;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_HPAPSP, layertag});
	
	-- Enemies On Side
	layertag = toptag + CCPSTL_EnemyOnSide;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_EnemyOnSide, layertag});
	
	-- Plan
	layertag = toptag + CCPSTL_Plan;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Plan, layertag});
	-- RenderTexture
	grouptag = layertag + CCPSTM_Plan_RenderTexture;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Plan_RenderTexture, grouptag});
	-- feathers
	grouptag = layertag + CCPSTM_Plan_LinesFeather;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Plan_LinesFeather, grouptag});
	grouptag = layertag + CCPSTM_Plan_CirclesFeather;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Plan_CirclesFeather, grouptag});
	grouptag = layertag + CCPSTM_Plan_DotsFeather;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_Plan_DotsFeather, grouptag});
	
	PS_AddPlanningRenderTexture(toplayer, toptag);
	
	-- Menu
	layertag = toptag + CCPSTL_Menu;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCPSTL_Menu, layertag});
	-- Menu Indicators
	grouptag = layertag + CCHSTM_Menu_Category;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCHSTM_Menu_Category, grouptag});
		
	-- Overlay
	local overlaylayer = game.AddOverlayLayerChild(toplayer, {0, 0, CCZ_Max});
	-- Sniper Scope
	layertag = ktag_OverlayLayer + CCSTL_BG;
	game.AddNullChild({overlaylayer, ktag_OverlayLayer}, {0, 0, CCSTL_BG, layertag});
			
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