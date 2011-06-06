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
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_Progressing then
			_PlayScene_UpdatePlanning(toplayer, toptag, stateStep);
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

function _PlayScene_UpdatePlanning(toplayer, toptag, stateStep)
	
	local layertag = toptag + CCTag_Layer_11;
	local grouptag = layertag + CCTag_Menu_01;
	
	local rendertextureitem = game.GetNode({toplayer, grouptag});
	game.RenderTextureBegin(rendertextureitem);
	
	local nLines = table.getn(LGlobal_PlayData.planlines);
	
	if nLines > 0 then
		local nFinishedLines = 0;
		for i=1, nLines do
			if LGlobal_PlayData.planlines[i].time < LConst_PlanBrushFrame then
				local item = LGlobal_PlayData.planlines[i];
				
				local stepstogonow = item.stepstogo[item.time+1].now;
				local stepstogoacc = item.stepstogo[item.time+1].acc;
				
				for j=0, stepstogonow-1 do
					local nowstepindex = stepstogoacc+j;
					local scale = RANDTF(0.5, 1);
					if nowstepindex >= item.steps-LConst_PlanBrushFadeInStep and nowstepindex >= math.ceil(item.steps/2) then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(item.steps-nowstepindex+1);
					elseif nowstepindex < LConst_PlanBrushFadeInStep then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(nowstepindex+1);
					end
					game.SetScale(LGlobal_PlayData.planbrush.laser, scale, scale);
					game.SetAngle(LGlobal_PlayData.planbrush.laser, RANDT());
					
					local interval = item.space * (nowstepindex) / item.dist;
					game.NodeVisit(LGlobal_PlayData.planbrush.laser, global.INTER(item.xb, item.xe, interval), global.INTER(item.yb, item.ye, interval));
				end
				
				LGlobal_PlayData.planlines[i].time = item.time+1;
			else
				nFinishedLines = nFinishedLines + 1;
			end
		end
		if nFinishedLines == nLines then
			LGlobal_PlayData.planlines = {};
		end
	end
	
	local nCircles = table.getn(LGlobal_PlayData.plancircles);
	
	if nCircles > 0 then
		local nFinishedCircles = 0;
		for i=1, nCircles do
			if LGlobal_PlayData.plancircles[i].time < LConst_PlanBrushFrame then
				local item = LGlobal_PlayData.plancircles[i];
				
				local stepstogonow = item.stepstogo;
				local totalsteps = item.stepstogo * LConst_PlanBrushFrame;

				for j=0, stepstogonow-1 do
					local nowstepindex = item.stepstogo*item.time+j;
					local nowangle = item.startangle+nowstepindex*item.anglestep;
					
					local r = item.r;
					r = r * (nowstepindex/totalsteps * 0.6 + 0.4);
					local x = item.x + global.SINT(nowangle)*r;
					local y = item.y + global.COST(nowangle)*r;
					
					local scale = RANDTF(0.5, 1);
					if nowstepindex >= totalsteps-LConst_PlanBrushFadeInStep then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(totalsteps-nowstepindex+1);
					elseif nowstepindex < LConst_PlanBrushFadeInStep then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(nowstepindex+1);
					end

					game.SetScale(LGlobal_PlayData.planbrush.bomb, scale, scale);
					game.SetAngle(LGlobal_PlayData.planbrush.bomb, RANDT());
				
					game.NodeVisit(LGlobal_PlayData.planbrush.bomb, x, y);
				end
				
				LGlobal_PlayData.plancircles[i].time = item.time+1;
			else
				nFinishedCircles = nFinishedCircles + 1;
			end
		end
		if nFinishedCircles == nCircles then
			LGlobal_PlayData.plancircles = {};
		end
	end
	
	local nDots = table.getn(LGlobal_PlayData.plandots);
	
	if nDots > 0 then
		local nFinishedDots = 0;
		for i=1, nDots do
			if LGlobal_PlayData.plandots[i].time < 0 then
				LGlobal_PlayData.plandots[i].time = LGlobal_PlayData.plandots[i].time+1;
			elseif LGlobal_PlayData.plandots[i].time < LConst_PlanBrushFrame then
				local item = LGlobal_PlayData.plandots[i];
				
				local stepstogonow = item.stepstogo;
				local totalsteps = item.stepstogo * LConst_PlanBrushFrame;
				
				for j=0, stepstogonow-1 do
					local nowstepindex = item.stepstogo*item.time+j;
					local index = 1;
					if item.time >= math.floor(LConst_PlanBrushFrame/2) then
						index = 2;
						nowstepindex = nowstepindex - item.stepstogo*math.floor(LConst_PlanBrushFrame/2);
					end
					local x = item.startx[index] + item.xplus[index]*nowstepindex;
					local y = item.starty[index] + item.yplus[index]*nowstepindex;
					
					local scale = RANDTF(0.5, 1);
					if nowstepindex >= totalsteps/2-LConst_PlanBrushFadeInStep then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(totalsteps/2-nowstepindex+1);
					elseif nowstepindex < LConst_PlanBrushFadeInStep then
						scale = 1/(LConst_PlanBrushFadeInStep+1)*(nowstepindex+1);
					end
					
					scale = scale * 0.75;
										
					game.SetScale(LGlobal_PlayData.planbrush.sniper, scale, scale);
					game.SetAngle(LGlobal_PlayData.planbrush.sniper, RANDT());
				
					game.NodeVisit(LGlobal_PlayData.planbrush.sniper, x, y);
				end
				
				LGlobal_PlayData.plandots[i].time = item.time+1;
			else
				nFinishedDots = nFinishedDots + 1;
			end
		end
		if nFinishedDots == nDots then
			LGlobal_PlayData.plandots = {};
		end
	end
	
	game.RenderTextureEnd(rendertextureitem);
	
	return false;
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

function _PlayScene_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer)

	local layertag = toptag + CCTag_Layer_02;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;
	
	local siid, sidesiid, sidearrowsiid, life, defelayer = game.GetEnemyTypeData(etype);
	if elayer == nil then
		elayer = defelayer;
	end
	
	x, y, scale = game.Transform3DPoint(x, y, 3-elayer/CCZ_eLayer_01);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	game.AddEnemy(grouptag+selitemtag, x, y, etype, life, elayer, ENEMY_InScene);	
	
	local spEnemy = game.CreateSprite(siid, {x, y, 0, scale, scale}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag}, elayer);
	
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

function _PlayScene_SidePosToScenePos(x, y, angle)
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
	end
	return x, y;
end

function _PlayScene_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local layertag = toptag + CCTag_Layer_08;
	local grouptag = layertag + CCTag_MenuSub_01*(nowturn+1);
	local enemyinscenecount, enemyonsidecount = game.GetActiveEnemyData();
	if index >= enemyonsidecount then
		return true;
	end
	local selitemtag = index + 1;
	local itemtag, x, y, etype, life, elayer, angle = game.GetActiveEnemyData(index, ENEMY_OnSide);
	local tx, ty, scale = game.Transform3DPoint(x, y, 1);
	
	local enemyonsidenode = game.GetNode({toplayer, itemtag});
	local onsidemoveaction = game.ActionMove(CCAF_To, tx, ty, LConst_EnemySpriteFadeTime*2);
	local onsidealphaaction = game.ActionFade(CCAF_To, 0, LConst_EnemySpriteFadeTime*2);
	local onsidedeleteaction = game.ActionDelete();
	onsidedeleteaction = game.ActionSequence({onsidealphaaction, onsidedeleteaction});
	local onsidedeletechildrenaction = game.ActionDeleteChildren(LConst_EnemySpriteFadeTime);
	local onsideaction = game.ActionSpawn({onsidemoveaction, onsidedeleteaction, onsidedeletechildrenaction});
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

function _PlayScene_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn)
	local layertag = toptag + CCTag_Layer_08;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;

	local siid, sidesiid, sidearrowsiid, life, elayer = game.GetEnemyTypeData(etype);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	local spEnemy = game.CreateSprite(sidesiid, {x, y}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag});
	local spEnemySideArrow = game.CreateSprite(sidearrowsiid, {64, 64, angle, 2, 2}, grouptag+selitemtag);
	local enemysidearrownode = game.AddSpriteChild(spEnemySideArrow, {toplayer, grouptag+selitemtag});
	
	game.SetColor(enemysidearrownode, global.ARGB(0, 0xffffff));
	local blinktimepre = 0.5;
	local blinktimepost = 0.9;
	local arrowfadeactionpre = game.ActionFade(CCAF_To, 0xCF, blinktimepre);
	local arrowfadeactionpost = game.ActionFade(CCAF_To, 0x1F, blinktimepost);
	local arrowfadeaction = game.ActionSequence({arrowfadeactionpre, arrowfadeactionpost});
	arrowfadeaction = game.ActionRepeat(arrowfadeaction);
	game.RunAction(enemysidearrownode, arrowfadeaction);

	local tx, ty = _PlayScene_SidePosToScenePos(x, y, angle)

	game.AddEnemy(grouptag+selitemtag, tx, ty, etype, life, elayer, ENEMY_OnSide, angle);
	
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
	
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp + HPMax*LConst_HPRegainRate;
	ap = ap + APMax*LConst_APRegainRate;
	game.SetHPAPSP(hp, ap, sp);
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
	local atk, apatk, hpregainatk = game.GetEnemyATK(etype, elayer/CCZ_eLayer_01);
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp - atk;
	ap = ap - apatk;
	game.SetHPAPSP(hp, ap, sp);
	if hpregainatk > 0 then
		-- Add Enemy HP
	end
end

function _PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer)
	local elayeradvance = game.GetEnemyELayerAdvance(etype);
	if elayer == CCZ_eLayer_03 or elayeradvance == 0 then
		return;
	end
	
	elayer = elayer + elayeradvance;
	if elayer > CCZ_eLayer_03 then
		elayer = CCZ_eLayer_03;
	end
	local itemtag, x, y, etype, life = game.GetActiveEnemyData(index, ENEMY_InScene);

	local tx, ty, scale = game.Transform3DPoint(x, y, 3-elayer/CCZ_eLayer_01);
	
	local aemoveaction = game.ActionMove(CCAF_To, tx, ty, LConst_EnemySpriteFadeTime);
	local aescaleaction = game.ActionScale(CCAF_To, scale, scale, LConst_EnemySpriteFadeTime, true);
	local aeaction = game.ActionSpawn({aemoveaction, aescaleaction});
	local enemynode = game.GetNode({toplayer, itemtag});

	game.RunAction(enemynode, aeaction);
	
	local ttoptag, tsublayertag, tmenugrouptag, tmenuitemtag = game.GetSubTags(itemtag);
	local menugroup = itemtag-tmenuitemtag;
	game.SetZ(enemynode, menugroup+elayer);
	game.SetActiveEnemyData(index, ENEMY_InScene, life, elayer);
	
end

function _PlayScene_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local enemyinscenecount, enemyonsidecount = game.GetActiveEnemyData();
	if index >= enemyinscenecount+enemyonsidecount then
		return true;
	end
	local layertag;
	local itemtag, x, y, etype, life, elayer;
	if index < enemyinscenecount then
		layertag = toptag + CCTag_Layer_02;
		itemtag, x, y, etype, life, elayer = game.GetActiveEnemyData(index, ENEMY_InScene);
		_PlayScene_EnemyAttack(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer);
		_PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, nowstage, nowmission, nowturn, etype, elayer);
	else
		local eindex = index-enemyinscenecount;
		layertag = toptag + CCTag_Layer_08;
		itemtag, x, y, etype, life, elayer = game.GetActiveEnemyData(eindex, ENEMY_OnSide);
		_PlayScene_EnemyAttack(toplayer, toptag, eindex, nowstage, nowmission, nowturn, etype, 0);
	end

	local enemynode = game.GetNode({toplayer, itemtag});

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