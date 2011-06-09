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
			else
				stateST = STATE_ST_Progressing;
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
	elseif stateAction == STATE_SpecialEnemyAction then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby or stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Progressing;
			if _PlayScene_SpecialEnemyAction(toplayer, toptag, stateStep) then
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
	elseif stateAction == STATE_HPRegain then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_HPRegain(toplayer, toptag) then
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
			_PlayScene_ShowTurnStart(toplayer, toptag)
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_StepForward then
			stateST = STATE_ST_Finished;
		end
	elseif stateAction == STATE_Planning then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			_PlayScene_PreparePlanning(toplayer, toptag);
			stateST = STATE_ST_Progressing;
		elseif stateST == STATE_ST_StepForward then
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
	elseif stateAction == STATE_APRegain then
		if stateST == STATE_ST_Null then
			stateST  = STATE_ST_Standby;
		elseif stateST == STATE_ST_Standby then
			if _PlayScene_APRegain(toplayer, toptag) then
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


function _PlayScene_UpdatePlanGroup(toplayer, toptag)
	
	local plangroup = LGlobal_PlayData.plangroup;
	local layergroup = toptag + CCTag_Layer_13;
	local grouptag = layergroup + CCTag_Menu_02;
	
	game.RemoveChild({toplayer, grouptag+1});
	local spNumber = game.CreateSprite(SI_GUIDigit_0 + plangroup+1, {624, 48}, grouptag+1);
	local numbernode = game.AddSpriteChild(spNumber, {toplayer, grouptag}, CCTag_Menu_02);
	game.SetColor(numbernode, global.ARGB(0, 0xffffff));
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	game.RunAction(numbernode, fadeaction);
	
end

function _PlayScene_PreparePlanning(toplayer, toptag)
	LGlobal_PlayData.planlines = {};
	LGlobal_PlayData.plancircles = {};
	LGlobal_PlayData.plandots = {};
	LGlobal_PlayData.plangroup = 0;
	_PlayScene_UpdatePlanGroup(toplayer, toptag);
	_PlayScene_ToggleMenuEnable(toplayer, toptag, true);
end

function _PlayScene_ExitPlanning(toplayer, toptag)
	_PlayScene_ToggleMenuEnable(toplayer, toptag, false);
end

function _PlayScene_Plan_DrawFeather(toplayer, toptag, grouptag, brushx, brushy, time, index)
	
	if brushx == nil or brushy == nil then
		return;
	end
	
	local feathernode;
	if time == 0 then
		local spfeather = game.CreateSprite(SI_Game_PlanBrush_Feather, {brushx, brushy}, grouptag+index);
		feathernode = game.AddSpriteChild(spfeather, {toplayer, grouptag});
		game.SetAnchor(feathernode, 0.25, 0);
	else
		feathernode = game.GetNode({toplayer, grouptag+index});
		game.SetPosition(feathernode, brushx, brushy);
	end
	
	if time == LConst_PlanBrushFrame-1 then
		local fadeoutaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
		local deleteaction = game.ActionDelete();
		local featheraction = game.ActionSequence({fadeoutaction, deleteaction});
		game.RunAction(feathernode, featheraction);
	end
end

function _PlayScene_AddPlanGroupNumber(toplayer, toptag, grouptag, index, x, y)
	local spNumber = game.CreateSprite(SI_GUIDigit_Small_0+LGlobal_PlayData.plangroup+1, {x, y});
	local numbernode = game.AddSpriteChild(spNumber, {toplayer, grouptag}, CCZ_Max);
	game.SetColor(numbernode, global.ARGB(0, 0xffffff));
	game.SetAnchor(numbernode, 0.5, 0);
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	game.RunAction(numbernode, fadeaction);
end

function _PlayScene_UpdatePlanning(toplayer, toptag, stateStep)
	
	local layertag = toptag + CCTag_Layer_11;
	local grouptag = layertag + CCTag_Menu_01;
	
	local linesgrouptag = layertag+CCTag_Menu_04;
	local circlesgrouptag = layertag+CCTag_Menu_05;
	local dotsgrouptag = layertag+CCTag_Menu_06;
	
	local rendertextureitem = game.GetNode({toplayer, grouptag});
	game.RenderTextureBegin(rendertextureitem);
	
	local nLines = table.getn(LGlobal_PlayData.planlines);
	
	if nLines > 0 then
		for i=1, nLines do
			if LGlobal_PlayData.planlines[i].time < LConst_PlanBrushFrame then				
				local item = LGlobal_PlayData.planlines[i];
				
				if item.time == 0 then
					_PlayScene_AddPlanGroupNumber(toplayer, toptag, linesgrouptag, i, item.xb, item.yb);
				end
				
				local stepstogonow = item.stepstogo[item.time+1].now;
				local stepstogoacc = item.stepstogo[item.time+1].acc;
				
				local brushx, brushy;
				if item.time == 0 then
					brushx, brushy = item.xb, item.yb;
				end
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
					brushx, brushy = global.INTER(item.xb, item.xe, interval), global.INTER(item.yb, item.ye, interval);
					game.NodeVisit(LGlobal_PlayData.planbrush.laser, brushx, brushy);
				end
				
				_PlayScene_Plan_DrawFeather(toplayer, toptag, linesgrouptag, brushx, brushy, item.time, i);
				
				LGlobal_PlayData.planlines[i].time = item.time+1;
			end
		end
	end
	
	local nCircles = table.getn(LGlobal_PlayData.plancircles);
	
	if nCircles > 0 then
		for i=1, nCircles do
			if LGlobal_PlayData.plancircles[i].time < LConst_PlanBrushFrame then
				local item = LGlobal_PlayData.plancircles[i];
				
				if item.time == 0 then
					_PlayScene_AddPlanGroupNumber(toplayer, toptag, circlesgrouptag, i, item.x, item.y);
				end
				
				local stepstogonow = item.stepstogo;
				local totalsteps = item.stepstogo * LConst_PlanBrushFrame;

				local brushx, brushy;
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
				
					brushx, brushy = x, y;
					game.NodeVisit(LGlobal_PlayData.planbrush.bomb, x, y);
				end
				
				_PlayScene_Plan_DrawFeather(toplayer, toptag, circlesgrouptag, brushx, brushy, item.time, i);
				
				LGlobal_PlayData.plancircles[i].time = item.time+1;
			end
		end
	end
	
	local nDots = table.getn(LGlobal_PlayData.plandots);
	
	if nDots > 0 then
		for i=1, nDots do
			if LGlobal_PlayData.plandots[i].time < 0 then
				LGlobal_PlayData.plandots[i].time = LGlobal_PlayData.plandots[i].time+1;
			elseif LGlobal_PlayData.plandots[i].time < LConst_PlanBrushFrame then
				local item = LGlobal_PlayData.plandots[i];
				
				if item.time == 0 then
					_PlayScene_AddPlanGroupNumber(toplayer, toptag, dotsgrouptag, i, item.x, item.y);
				end
				
				local stepstogonow = item.stepstogo;
				local totalsteps = item.stepstogo * LConst_PlanBrushFrame;
				
				local brushx, brushy;
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
				
					brushx, brushy = x, y;
					game.NodeVisit(LGlobal_PlayData.planbrush.sniper, x, y);
				end
				
				_PlayScene_Plan_DrawFeather(toplayer, toptag, dotsgrouptag, brushx, brushy, item.time, i);
				
				LGlobal_PlayData.plandots[i].time = item.time+1;
			end
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
	if _PlayScene_DoShowTurnStart(toplayer, toptag, true) then
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
	
	local siid, sidesiid, sidearrowsiid, defelayer = game.GetEnemyTypeData(etype);
	if elayer == nil then
		elayer = defelayer;
	end
	
	x, y, scale = game.Transform3DPoint(x, y, 3-elayer/CCZ_eLayer_01);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	game.AddEnemy(grouptag+selitemtag, x, y, etype, elayer, ENEMY_InScene);	
	
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

	local siid, sidesiid, sidearrowsiid, elayer = game.GetEnemyTypeData(etype);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	local spEnemy = game.CreateSprite(sidesiid, {x, y}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag});
	local spEnemySideArrow = game.CreateSprite(sidearrowsiid, {64, 64, angle, 2, 2}, grouptag+selitemtag);
	local enemysidearrownode = game.AddSpriteChild(spEnemySideArrow, {toplayer, grouptag+selitemtag});
	
	game.SetColor(enemysidearrownode, global.ARGB(0, 0xffffff));
	local arrowfadeactionpre = game.ActionFade(CCAF_To, 0xCF, LConst_BlinkTimePre);
	local arrowfadeactionpost = game.ActionFade(CCAF_To, 0x1F, LConst_BlinkTimePost);
	local arrowfadeaction = game.ActionSequence({arrowfadeactionpre, arrowfadeactionpost});
	arrowfadeaction = game.ActionRepeat(arrowfadeaction);
	game.RunAction(enemysidearrownode, arrowfadeaction);

	local tx, ty = _PlayScene_SidePosToScenePos(x, y, angle)

	game.AddEnemy(grouptag+selitemtag, tx, ty, etype, elayer, ENEMY_OnSide, angle);
	
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
	local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
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

function _PlayScene_HPRegain(toplayer, toptag)
	-- Add AP
	
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp + HPMax*LConst_HPRegainRate;
	game.SetHPAPSP(hp, ap, sp);
	return true;
end

function _PlayScene_APRegain(toplayer, toptag)
	-- Add AP
	
	local hp, ap, sp = game.GetHPAPSP();
	ap = ap + APMax*LConst_APRegainRate;
	game.SetHPAPSP(hp, ap, sp);
	return true;
end

function _PlayScene_DoShowTurnStart(toplayer, toptag, bRequireClose)
	
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local missiontype = game.GetMissionTargetData();
	
	if nowturn == 0 and missiontype == MISSIONTYPE_Normal then
		return true;
	end
	
	local layertag = toptag + CCTag_Layer_04;
	local grouptag = layertag + CCTag_Menu_01;
	
	local spboard = game.CreateSprite(SI_MOUI_Board, {480, 240});
	local boardnode = game.AddSpriteChild(spboard, {toplayer, grouptag}, CCTag_Menu_01);
	
	local sptarget = game.CreateSprite(SI_MOUI_Target, {480, 400});
	local targetnode = game.AddSpriteChild(sptarget, {toplayer, grouptag}, CCTag_Menu_01);
	
	if nowturn > 0 then
		local str = LGlobal_TranslateGameStr_NowTurn(nowturn);
		game.AddTextChild({toplayer, grouptag}, {480, 280, CCTag_Menu_01}, str, 80);
	end
	
	local moveupaction = game.ActionMove(CCAF_To, 0, 0, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, -480);
	
	if bRequireClose == nil or not bRequireClose then
		PlayScene_CB_Target(nil, toplayer, toptag, CCTag_Layer_04, nil, 1, LConst_BoardMoveTime+LConst_BoardShowTime);
	else
		grouptag = layertag + CCTag_Menu_04;
		local menuitem = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTag_Menu_04, grouptag+1);
		local menu = game.AddMenuChild({menuitem}, {toplayer, layertag}, {0, 0, CCTag_Menu_04, grouptag});
	end
	
	game.RunAction(layernode, moveupaction);
	
	layertag = toptag + CCTag_Layer_11;
	grouptag = layertag+CCTag_Menu_01;
	local planrendertexturesprite = game.GetNode({toplayer, grouptag}, NODETYPE_RenderTexture);
	local fadeaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
	local tintaction = game.ActionTint(CCAF_To, 0, LConst_ItemVanishTime);
	local spaction = game.ActionSpawn({fadeaction, tintaction});
	game.RunAction(planrendertexturesprite, spaction);
--	game.SetIsVisible(planlayernode, false);
	
	return false;
end

function _PlayScene_ShowTurnStart(toplayer, toptag)
	--Add Menu and Callback
	if _PlayScene_DoShowTurnStart(toplayer, toptag) then
		return true;
	end
--	_PlayScene_StepForward(STATE_ShowTurnStart);
	return false;
end

function _PlayScene_SelfAction(toplayer, toptag, index)
	-- Check all self action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local layertag = toptag+CCTag_Layer_11;
	local grouptag = layertag+CCTag_Menu_01;
	if index == 0 then
		grouptag = layertag+CCTag_Menu_04;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCTag_Menu_05;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCTag_Menu_06;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
	end
	if true then
		grouptag = layertag+CCTag_Menu_01;
		local rendertextureitem = game.GetNode({toplayer, grouptag});
		game.RenderTextureBegin(rendertextureitem, true);
		game.RenderTextureEnd(rendertextureitem);
		LGlobal_PlayData.planlines = {};
		LGlobal_PlayData.plandots = {};
		LGlobal_PlayData.plancircles = {};
		return true;
	end
	
	return false;
end

function _PlayScene_EnemyAttack(toplayer, toptag, index, etype, elayer)
	local atk, apatk, hpregainatk = game.GetEnemyATK(etype, elayer/CCZ_eLayer_01);
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp - atk;
	ap = ap - apatk;
	game.SetHPAPSP(hp, ap, sp);
	if hpregainatk > 0 then
		-- Add Enemy HP
	end
end

function _PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, etype, elayer)
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

function _PlayScene_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn, bZeroLayerOnly)
	local enemyinscenecount = game.GetActiveEnemyData();
	if index >= enemyinscenecount then
		return true;
	end
	
	local doaction = true;
	local doadvance = true;
	
	local layertag = toptag + CCTag_Layer_02;
	local itemtag, x, y, etype, life, elayer = game.GetActiveEnemyData(index, ENEMY_InScene);
		
	local atk, apatk, hpregainatk = game.GetEnemyATK(etype, 0);
	if bZeroLayerOnly ~= nil and bZeroLayerOnly then
		doadvance = false;
		if atk == 0 and apatk == 0 and hpregainatk == 0 then
			doaction = false;
		end
	else
		if atk ~= 0 or apatk ~= 0 or hpregainatk ~= 0 then
			doaction = false;
		end
	end
	
	if doaction then
		_PlayScene_EnemyAttack(toplayer, toptag, index, etype, elayer);
	end
	if doadvance then
		_PlayScene_EnemyAdvanceELayer(toplayer, toptag, index, etype, elayer);
	end

	local enemynode = game.GetNode({toplayer, itemtag});
	
	local delaytime = LConst_EnemyEnterDelayTime;
	local state = STATE_EnemyAction;
	if not doaction then
		delaytime = 0;
	end
	if bZeroLayerOnly then
		state = STATE_SpecialEnemyAction;
	end
	

	local dataindex = LGlobal_SaveData(state);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, delaytime, dataindex);
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

function _PlayScene_SpecialEnemyAction(toplayer, toptag, index)
	-- Check all enemy action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if _PlayScene_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn, true) then
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
			game.SetState(stateST, stateAction, stateStep);
		end
	end
end

function _PlayScene_StateFinish(_stateAction)
	local stateST, stateAction, stateStep = game.GetState();
	if stateAction == _stateAction then
		stateST = STATE_ST_Finished;
		game.SetState(stateST, stateAction, stateStep);
	end
end