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
			stateST = STATE_ST_Progressing;
			if _PlayScene_EnemyEnter(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_AddEnemy then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if _PlayScene_AddEnemy(toplayer, toptag, stateStep) then
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
			game.AddTurn();
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
			stateST = STATE_ST_Progressing;
			if _PlayScene_SelfAction(toplayer, toptag, stateStep) then
				stateST = STATE_ST_Finished;
			end
		end
	elseif stateAction == STATE_EnemyAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
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

function _PlayScene_CalculatePos(x, y, elayer)
	-- TODO
	return x, y, 1, 1;
end

function _PlayScene_CreateEnemySprite(toplayer, toptag, siid, x, y, elayer)

	local layertag = toptag + CCTag_Layer_02;
	local grouptag = layertag + CCTag_Menu_04;
	
	local enemyinscenecount = game.GetActiveEnemyData();
	local selitemtag = enemyinscenecount+1;
	
	x, y, xscale, yscale = _PlayScene_CalculatePos(x, y, elayer);
	local spEnemy = game.CreateSprite(siid, {x, y, 0, xscale, yscale}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, layertag, grouptag}, elayer);
	
	game.AddEnemy(grouptag+selitemtag, true);
	
	return enemynode, layertag, grouptag, selitemtag;
end

function _PlayScene_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission)
	
	--skip event mission
	local eposturnitem = LGlobal_EnemyPosTable[nowstage+1][nowmission][1];
	if index >= table.getn(eposturnitem) then
		return true;
	end
		
	local epositem = eposturnitem[index+1];
	local x, y, etype, elayer = epositem[1], epositem[2], epositem[3], epositem[4];
	local siid, life = game.GetEnemyTypeData(etype);
	
	local enemynode, layertag, grouptag, selitemtag = _PlayScene_CreateEnemySprite(toplayer, toptag, siid, x, y, elayer);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
	
	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);	
	local callnodegrouptag = layertag + CCTag_Menu_11;
	local callnode = game.AddNullChild({toplayer, layertag, grouptag, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
end

function _PlayScene_EnemyEnter(toplayer, toptag, index)

	-- Check all enemy in
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if nowturn == 0 then
		if _PlayScene_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission) then
			return true;
		end
	end
	
	return false;
end

function _PlayScene_AddEnemy(toplayer, toptag, index)
	
	-- Check all enemy added
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