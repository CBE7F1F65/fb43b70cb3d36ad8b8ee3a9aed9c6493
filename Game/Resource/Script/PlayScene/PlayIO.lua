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

function _PlayScene_AddBGItems(toplayer, toptag)
	
	local layertag = toptag+CCTag_Layer_00;
	
	local bgsiid = game.GetMissionBGData();
	local spBG = game.CreateSprite(bgsiid, {480, 320});
	game.AddSpriteChild(spBG, {toplayer, layertag});
		
end

function _PlayScene_RunHelp(toplayer, toptag)
		
	local helptype1, helpindex1, helptype2, helpindex2, helptype3, helpindex3 = game.GetMissionHelpData();

	if helptype1 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype1, helpindex1);
		
		if not enabled then
			game.SetHelpIndex(helptype1, helpindex1);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return
		end
	end
	
	if helptype2 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype2, helpindex2);
		if not enabled then
			game.SetHelpIndex(helptype2, helpindex2);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return
		end
	end
	
	if helptype3 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype3, helpindex3);
		if not enabled then
			game.SetHelpIndex(helptype3, helpindex3);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return
		end
	end
	
	LGlobal_PlayData.PlayScene_EnterHelpFlag = -1;
		
end

function PlayScene_OnInit(toplayer, toptag)
	
	local layertag = toptag;
	
	-- BG Frame
	local layertag = toptag + CCTag_Layer_00;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_00, layertag});
	
	_PlayScene_AddBGItems(toplayer, toptag);
	
	-- ObjBG
	local layertag = toptag + CCTag_Layer_01;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_01, layertag});
	
	-- Sprites
	local layertag = toptag + CCTag_Layer_02;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_02, layertag});
	
	-- ObjFG
	local layertag = toptag + CCTag_Layer_03;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_03, layertag});
	
	-- Message
	local layertag = toptag + CCTag_Layer_05;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_05, layertag});
	
	-- Touch
	local layertag = toptag + CCTag_Layer_06;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_06, layertag});
	
	-- Menu
	local layertag = toptag + CCTag_Layer_08;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_08, layertag});
	
	-- Clear GameOver
	local layertag = toptag + CCTag_Layer_10;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_10, layertag});
	
	_PlayScene_InitGlobal(toplayer, toptag);
			
end

function _PlayScene_InitGlobal(toplayer, toptag)
	LGlobal_PlayData.PlayScene_EnterHelpFlag = 0;
end

function PlayScene_OnEnter(toplayer, toptag)
end
function PlayScene_OnEnterA(toplayer, toptag)
end

function PlayScene_OnEnterTDF(toplayer, toptag)
end

function PlayScene_OnEnterTDFA(toplayer, toptag)
	if LGlobal_PlayData.PlayScene_EnterHelpFlag < 3 then
		LGlobal_PlayData.PlayScene_EnterHelpFlag = LGlobal_PlayData.PlayScene_EnterHelpFlag+4;
	else
		LGlobal_PlayData.PlayScene_EnterHelpFlag = -1;
	end
end
function PlayScene_OnUpdate(toplayer, toptag)
	if LGlobal_PlayData.PlayScene_EnterHelpFlag > 3 then
		LGlobal_PlayData.PlayScene_EnterHelpFlag = LGlobal_PlayData.PlayScene_EnterHelpFlag-3;
		_PlayScene_RunHelp(toplayer, toptag);
	else
	end
end

function PlayScene_OnExit(toplayer, toptag)
end
function PlayScene_OnTouchBegin(toplayer, toptag)
end
function PlayScene_OnTouchEnd(toplayer, toptag)
end