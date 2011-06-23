function PS_UpdateState(toplayer, toptag)
	
	local stateST, stateAction, stateStep = game.GetState();
	
--	LOGSTATE("Pre:", stateST, stateAction, stateStep, toplayer, toptag);
	
	if stateAction == STATE_Waiting then
		
		stateAction = STATE_ShowHelp;
		stateST = STATE_ST_Standby;
		
	elseif stateAction == STATE_ShowHelp then
	
		if stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			if stateStep < 3 then
				stateST = STATE_ST_Progressing;
				if PS_ShowHelp(toplayer, toptag) then
					stateST = STATE_ST_Finished;
				end
			else
				stateST = STATE_ST_Finished;
			end
		end
	
	elseif stateAction == STATE_EnemyEnter then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if PS_EnemyEnter(toplayer, toptag, stateStep) then
				game.DoRemoveEnemy(ENEMY_OnSide);
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_SpecialEnemyAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if PS_SpecialEnemyAction(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_AddEnemy then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if PS_AddEnemy(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_ShowTurnStart then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
			game.AddTurn();
		elseif stateST == STATE_ST_Standby then
			PS_ShowTurnStart(toplayer, toptag)
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_HPRegain then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if PS_HPRegain(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_Planning then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			PS_PreparePlanning(toplayer, toptag);
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_Progressing then
			PS_UpdatePlanning(toplayer, toptag, stateStep);
		end
	elseif stateAction == STATE_SelfAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if PS_SelfAction(toplayer, toptag, stateStep) then
				game.DoRemoveEnemy(ENEMY_InScene);
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_APRegain then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if PS_APRegain(toplayer, toptag) then
				stateST = STATE_ST_Finished;
			end
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_EnemyAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if PS_EnemyAction(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	-- Over cannot be quit normally
	elseif stateAction == STATE_Over then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_Progressing then
			stateST = STATE_ST_Progressing;
			if PS_ShowOver(toplayer, toptag) then
				stateST = STATE_ST_StepForward;
			end
--		elseif stateST == STATE_ST_StepForward then
--			stateST = STATE_ST_Finished;
		end
	
	end
		
	game.SetState(stateST, stateAction, stateStep);
	
--	LOGSTATE("Post:", stateST, stateAction, stateStep, toplayer, toptag);
end

function PS_StepForward(_stateAction)
	local stateST, stateAction, stateStep = game.GetState();
	if stateAction == _stateAction then
		if stateST == STATE_ST_Progressing then
			stateST = STATE_ST_StepForward;
			game.SetState(stateST, stateAction, stateStep);
			return true;
		end
	end
	return false;
end

function PS_StateFinish(_stateAction)
	local stateST, stateAction, stateStep = game.GetState();
	if stateAction == _stateAction then
		stateST = STATE_ST_Finished;
		game.SetState(stateST, stateAction, stateStep);
		return true;
	end
	return false;
end