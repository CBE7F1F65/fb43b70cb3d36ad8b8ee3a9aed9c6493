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
				game.DoRemoveEnemy(ENEMY_OnSide);
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

function _PlayScene_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer)

	local layertag = toptag + CCTag_Layer_02;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;
	
	local siid, sidesiid, life, defelayer = game.GetEnemyTypeData(etype);
	if elayer == nil then
		elayer = defelayer;
	end
	
	x, y, xscale, yscale = _PlayScene_CalculatePos(x, y, elayer);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, CCZ_Max-(menugroup+elayer), grouptag});
	end
	
	local spEnemy = game.CreateSprite(siid, {x, y, 0, xscale, yscale}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag}, elayer);

	game.AddEnemy(grouptag+selitemtag, etype, life, elayer, ENEMY_InScene);
	
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
	
	local enemynode, layertag, grouptag, selitemtag = _PlayScene_CreateEnemySprite(toplayer, toptag, index, etype, x, y, 0, elayer);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));	
	local enemyaction = game.ActionFade(CCAF_To, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);

	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodegrouptag = layertag + CCTag_Menu_11;
	local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
	return false;
end

function _PlayScene_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local layertag = toptag + CCTag_Layer_08;
	local grouptag = layertag + CCTag_MenuSub_01*(nowturn+1);
	local enemyinscenecount, enemyonsidecount = game.GetActiveEnemyData();
	if index >= enemyonsidecount then
		return true;
	end
	local selitemtag = index + 1;
	local itemtag, etype, life, elayer = game.GetActiveEnemyData(index, ENEMY_OnSide);
	local enemyonsidenode = game.GetNode({toplayer, itemtag});

	local x, y = game.GetPosition(enemyonsidenode);
	local angle = game.GetAngle(enemyonsidenode);
	
	local r;
	if x <= LGlobal_EnemySideLEdge then
		r = x*(480-LGlobal_EnemySideEdge)/LGlobal_EnemySideEdge+(LGlobal_EnemySideLEdge-x);
	elseif x>=LGlobal_EnemySideREdge then
		r = (960-x)*(480-LGlobal_EnemySideEdge)/LGlobal_EnemySideEdge+(x-LGlobal_EnemySideREdge);
	elseif y>=LGlobal_EnemySideBEdge then
		r = (y-LGlobal_EnemySideBEdge)*(960-LGlobal_EnemySideTEdge-LGlobal_EnemySideEdge)/LGlobal_EnemySideEdge+(y-LGlobal_EnemySideBEdge);
	end
	
	if r ~= nil then
		x = x+r*global.SINT(angle);
		y = y+r*global.COST(angle);
		local enemyonsidenode = game.GetNode({toplayer, itemtag});
		local onsidemoveaction = game.ActionMove(CCAF_To, x, y, LConst_EnemySpriteFadeTime*2);
		local onsidealphaaction = game.ActionFade(CCAF_To, 0, LConst_EnemySpriteFadeTime*3);
		local onsidedeleteaction = game.ActionDelete();
		onsidedeleteaction = game.ActionSequence({onsidealphaaction, onsidedeleteaction});
		local onsideaction = game.ActionSpawn({onsidemoveaction, onsidedeleteaction});
		onsideaction = game.ActionEase(CCAF_In, onsideaction, 0.35);
		game.RunAction(enemyonsidenode, onsideaction);
		
		game.RemoveEnemy(index, ENEMY_OnSide);
				
		local enemynode, layertag, grouptag, selitemtag = _PlayScene_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer);
		game.SetColor(enemynode, global.ARGB(0, 0xffffff));
		local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
		game.RunAction(enemynode, enemyaction);
		
		local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
		local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);	
		local callnodegrouptag = layertag + CCTag_Menu_11;
		local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
		game.RunAction(callnode, callfuncaction);
		
	end
	
	return false;
	
end

function _PlayScene_EnemyEnter(toplayer, toptag, index)

	-- Check all enemy in
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if nowturn == 0 then
		if _PlayScene_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission) then
			return true;
		end
	else
		if _PlayScene_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn) then
			return true;
		end
	end
	
	return false;
end
--[[
function _PlayScene_CalculateSidePos(x, y)
		
	local lx, rx, ty, by = 32, 928, 64, 608;
	
	local r = 512;
	
	local vcount = 0;
	local vpoints = {};
	--checkbottom
	if r > by-y then
		local c = global.DIST(r, 0, (by-y), 0);
		local plx = x-c;
		local prx = x+c;
		if plx >= lx then
			vcount = vcount+1;
			vpoints[vcount] = {plx, by};
		end
		if prx <= rx then
			vcount = vcount+1;
			vpoints[vcount] = {prx, by};
		end
	end
	--checkleft
	if r > x-lx then
		local c = global.DIST(r, 0, (x-lx), 0);
		local pty = y-c;
		local pby = y+c;
		if pty >= ty then
			vcount = vcount+1;
			vpoints[vcount] = {lx, pty};
		end
		if pby <= by then
			vcount = vcount+1;
			vpoints[vcount] = {lx, pby};
		end
	end
	--checkright
	if r > rx-x then
		local c = global.DIST(r, 0, (rx-x), 0);
		local pty = y-c;
		local pby = y+c;
		if pty >= ty then
			vcount = vcount+1;
			vpoints[vcount] = {rx, pty};
		end
		if pby <= by then
			vcount = vcount+1;
			vpoints[vcount] = {rx, pby};
		end
	end
	
	local randval = RANDT(1, table.getn(vpoints));
	
	local px, py = vpoints[randval][1], vpoints[randval][2];
	local angle = global.AMA(px, py, x, y)+9000;
	
	return px, py, angle;
end
--]]

function _PlayScene_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn)
	local layertag = toptag + CCTag_Layer_08;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;

	local siid, sidesiid, life, elayer = game.GetEnemyTypeData(etype);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, CCZ_Max-(menugroup+elayer), grouptag});
	end
	
	local spEnemy = game.CreateSprite(sidesiid, {x, y, angle}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, layertag, grouptag});

	game.AddEnemy(grouptag+selitemtag, etype, life, elayer, ENEMY_OnSide);
	
	return enemynode, layertag, grouptag, selitemtag;
end

function _PlayScene_AddEnemyToSide(toplayer, toptag, index, nowstage, nowmission, nowturn)
	
	local eposmissionitem = LGlobal_EnemyPosTable[nowstage+1][nowmission];
	if nowturn+1 >= table.getn(eposmissionitem) then
		return true;
	end
	
	local eposturnitem = eposmissionitem[nowturn+2];
	if index >= table.getn(eposturnitem) then
		return true;
	end	
		
	local epositem = eposturnitem[index+1];
	local x, y, etype, angle = epositem[1], epositem[2], epositem[3], epositem[4];
	
	local enemynode, layertag, grouptag, selitemtag = _PlayScene_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
	
	local dataindex = LGlobal_SaveData(STATE_AddEnemy);	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);	
	local callnodegrouptag = layertag + CCTag_Menu_11;
	local callnode = game.AddNullChild({toplayer, layertag, grouptag, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
	return false;
end

function _PlayScene_AddEnemy(toplayer, toptag, index)
	
	-- Check all enemy added
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if _PlayScene_AddEnemyToSide(toplayer, toptag, index, nowstage, nowmission, nowturn) then
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
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if true then
		return true;
	end
	
	return false;
end

function _PlayScene_EnemyAttack(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer)
	local atk = game.GetEnemyATK(etype, elayer/CCZ_eLayer_01);
end

function _PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer)
	local elayeradvance = game.GetEnemyELayerAdvance(etype);
	elayer = elayer + elayeradvance;
	if elayer > CCZ_eLayer_03 then
		elayer = CCZ_eLayer_03;
	end
end

function _PlayScene_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local enemyinscenecount, enemyonsidecount = game.GetActiveEnemyData();
	if index >= enemyinscenecount+enemyonsidecount then
		return true;
	end
	local layertag;
	local itemtag, etype, life, elayer;
	if index < enemyinscenecount then
		layertag = toptag + CCTag_Layer_02;
		itemtag, etype, life, elayer = game.GetActiveEnemyData(index, ENEMY_InScene);
		_PlayScene_EnemyAttack(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer);
		_PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer);
	else
		local eindex = index-enemyinscenecount;
		layertag = toptag + CCTag_Layer_08;
		itemtag, etype, life, elayer = game.GetActiveEnemyData(eindex, ENEMY_InScene);
		_PlayScene_EnemyAttack(toplayer, toptag, eindex, nowstage, nowmission, nowturn, etype, 0);
	end

	local dataindex = LGlobal_SaveData(STATE_EnemyAction);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodegrouptag = layertag + CCTag_Menu_11;
	local callnode = game.AddNullChild({toplayer, itemtag}, {0, 0, 0, callnodegrouptag+index+1});
	game.RunAction(callnode, callfuncaction);
	return false;
end

function _PlayScene_EnemyAction(toplayer, toptag, index)
	-- Check all enemy action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if _PlayScene_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn) then
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