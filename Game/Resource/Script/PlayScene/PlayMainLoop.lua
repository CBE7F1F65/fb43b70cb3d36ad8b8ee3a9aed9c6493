function _PlayScene_UpdateState(toplayer, toptag)
	
	local stateST, stateAction, stateStep = game.GetState();
	
--	LOGSTATE("Pre:", stateST, stateAction, stateStep, toplayer, toptag);
	
	if stateAction == STATE_Waiting then
		
		stateAction = STATE_ShowHelp;
		stateST = STATE_ST_Standby;
		
	elseif stateAction == STATE_ShowHelp then
	
		if stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			if stateStep < 3 then
				stateST = STATE_ST_Progressing;
				if _PlayScene_ShowHelp(toplayer, toptag) then
					stateST = STATE_ST_Finished;
				end
			else
				stateST = STATE_ST_Finished;
			end
		end
		
	elseif stateAction == STATE_ShowTarget then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_ShowTarget(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	
	elseif stateAction == STATE_EnemyEnter then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			if _PlayScene_EnemyEnter(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_HPAPRegain then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_HPAPRegain(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_ShowTurnStart then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_ShowTurnStart(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_Planning then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		end
	elseif stateAction == STATE_SelfAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			if _PlayScene_SelfAction(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_EnemyAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			if _PlayScene_EnemyAction(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_Over then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_ShowOver(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	
	end
		
	game.SetState(stateST, stateAction, stateStep);
	
--	LOGSTATE("Post:", stateST, stateAction, stateStep, toplayer, toptag);
end


function _PlayScene_ShowHelp(toplayer, toptag)
		
	local helptype1, helpindex1, helptype2, helpindex2, helptype3, helpindex3 = game.GetMissionHelpData();

	if helptype1 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype1, helpindex1);
		
		if not enabled then
			game.SetHelpIndex(helptype1, helpindex1);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return false;
		end
	end
	
	if helptype2 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype2, helpindex2);
		if not enabled then
			game.SetHelpIndex(helptype2, helpindex2);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return false;
		end
	end
	
	if helptype3 > 0 then
		local enabled = game.GetHelpAccessInfo(helptype3, helpindex3);
		if not enabled then
			game.SetHelpIndex(helptype3, helpindex3);
			game.PushScene(ktag_HelpSceneLayer, LConst_SceneTransTime);
			return false;
		end
	end
	
--	LGlobal_PlayData.PlayScene_EnterHelpFlag = -1;
	return true;
		
end

function _PlayScene_ShowTarget(toplayer, toptag)
	--Add Menu and Callback
	if true then
		return true;
	end
--	_PlayScene_StepForward(STATE_ShowTarget);
	return false;
end

function _PlayScene_EnemyEnter(toplayer, toptag, index)
	
	-- Check all enemy in
	if true then
		return true;
	end
	
	return false;
end

function _PlayScene_HPAPRegain(toplayer, toptag)
	-- Add HPAP
	return true;
end

function _PlayScene_ShowTurnStart(toplayer, toptag)
	--Add Menu and Callback
	if true then
		return true;
	end
--	_PlayScene_StepForward(STATE_ShowTurnStart);
	return false;
end

function _PlayScene_SelfAction(toplayer, toptag, index)
	-- Check all self action done
	if true then
		return true;
	end
	
	return false;
end

function _PlayScene_EnemyAction(toplayer, toptag, index)
	-- Check all enemy action done
	if true then
		return true;
	end
	
	return false;
end

function _PlayScene_ShowOver(toplayer, toptag)
	--Add Menu and Callback
	if true then
		return true;
	end
--	_PlayScene_StepForward(STATE_ShowOver);
	return false;
end

function _PlayScene_StepForward(_stateAction)
	local stateST, stateAction, stateStep = game.GetState();
	if stateAction == _stateAction then
		if stateST == STATE_ST_Progressing then
			stateST = STATE_ST_StepForward;
		end
	end
	game.SetState(stateST, stateAction, stateStep);
end

function _PlayScene_StateFinish(_stateAction)
	local stateST, stateAction, stateStep = game.GetState();
	if stateAction == _stateAction then
--		if stateST == STATE_ST_Progressing then
			stateST = STATE_ST_Finished;
--		end
	end
	game.SetState(stateST, stateAction, stateStep);
end