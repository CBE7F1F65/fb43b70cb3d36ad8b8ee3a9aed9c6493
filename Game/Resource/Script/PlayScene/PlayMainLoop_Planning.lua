function PS_UpdatePlanGroup(toplayer, toptag)
	
	local plangroup = LGlobal_PlayData.plangroup;
	local layergroup = toptag + CCPSTL_Menu;
	local grouptag = layergroup + CCPSTM_Menu_PlanGroup;
	
	game.RemoveChild({toplayer, grouptag+1});
	local spNumber = game.CreateSprite(SI_GUIDigit_0 + plangroup+1, {624, 48}, grouptag+1);
	local numbernode = game.AddSpriteChild(spNumber, {toplayer, grouptag}, CCPSTM_Menu_PlanGroup);
	game.SetColor(numbernode, global.ARGB(0, 0xffffff));
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	game.RunAction(numbernode, fadeaction);
	
end

function PS_PreparePlanning(toplayer, toptag)
	LGlobal_PlayData.planlines = {};
	LGlobal_PlayData.plancircles = {};
	LGlobal_PlayData.plandots = {};
	LGlobal_PlayData.blowpos = {};
	LGlobal_PlayData.plangroup = 0;
	PS_UpdatePlanGroup(toplayer, toptag);
	PS_SetMenuEnable(toplayer, toptag, true);
	local scorerate = game.GetMissionRateScore();
	scorerate = scorerate * LConst_TurnScoreRateMul;
	if scorerate < 1.0 then
		scorerate = 1.0;
	end
	game.SetMissionRateScore(scorerate);
	PS_UpdateScoreDisplay(toplayer, toptag);
end

function PS_ExitPlanning(toplayer, toptag)
	PS_SetMenuEnable(toplayer, toptag, false);
	
	local layertag = toptag + CCPSTL_EnemyBlow;
	local grouptag = layertag + CCPSTM_EnemyBlow_Arrow;
	
	local fadeaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
	local deleteaction = game.ActionDeleteChildren();
	local fadebackaction = game.ActionFade(CCAF_To, 0xff);
	local layeraction = game.ActionSequence({fadeaction, deleteaction, fadebackaction});
	local layernode = game.GetNode({toplayer, grouptag});
	game.RunAction(layernode, layeraction);
	
	for i=1, LConst_PlanGroupMax do
		grouptag = layertag + CCPSTM_EnemyBlow_EyeStart * i;
		local fadeaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
		local deleteaction = game.ActionDeleteChildren();
		local fadebackaction = game.ActionFade(CCAF_To, 0xff);
		local layeraction = game.ActionSequence({fadeaction, deleteaction, fadebackaction});
		local layernode = game.GetNode({toplayer, grouptag});
		game.RunAction(layernode, layeraction);
	end
end

function PS_DrawPlanningFeather(toplayer, toptag, grouptag, brushx, brushy, time, index)
	
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

function PS_AddPlanGroupNumber(toplayer, toptag, grouptag, index, x, y)
	local spNumber = game.CreateSprite(SI_GUIDigit_Small_0+LGlobal_PlayData.plangroup+1, {x, y});
	local numbernode = game.AddSpriteChild(spNumber, {toplayer, grouptag}, CCZ_Max);
	game.SetColor(numbernode, global.ARGB(0, 0xffffff));
	game.SetAnchor(numbernode, 0.5, 0);
	local fadeaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	game.RunAction(numbernode, fadeaction);
end

function PS_UpdatePlanning(toplayer, toptag, stateStep)
	
	local layertag = toptag + CCPSTL_Plan;
	local grouptag = layertag + CCPSTM_Plan_RenderTexture;
	
	local linesgrouptag = layertag+CCPSTM_Plan_LinesFeather;
	local circlesgrouptag = layertag+CCPSTM_Plan_CirclesFeather;
	local dotsgrouptag = layertag+CCPSTM_Plan_DotsFeather;
	
	
	local nLines = table.getn(LGlobal_PlayData.planlines);
	
	if nLines > 0 then
		for i=1, nLines do
			if LGlobal_PlayData.planlines[i].time < LConst_PlanBrushFrame then				
				local item = LGlobal_PlayData.planlines[i];
				
				if item.time == 0 then
					PS_AddPlanGroupNumber(toplayer, toptag, linesgrouptag, i, item.xb, item.yb);
				end
				
				local rendertextureitem = game.GetNode({toplayer, grouptag+item.plangroup+1});
				game.RenderTextureBegin(rendertextureitem);
	
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
				
				game.RenderTextureEnd(rendertextureitem);
				
				PS_DrawPlanningFeather(toplayer, toptag, linesgrouptag, brushx, brushy, item.time, i);
				
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
					PS_AddPlanGroupNumber(toplayer, toptag, circlesgrouptag, i, item.x, item.y);
				end
				
				local rendertextureitem = game.GetNode({toplayer, grouptag+item.plangroup+1});
				game.RenderTextureBegin(rendertextureitem);
				
				local stepstogonow = item.stepstogo;
				local totalsteps = item.stepstogo * LConst_PlanBrushFrame;

				local brushx, brushy;
				for j=0, stepstogonow-1 do
					local nowstepindex = item.stepstogo*item.time+j;
					local nowangle = item.startangle+nowstepindex*item.anglestep;
					
					local r = item.r;
					r = r * (nowstepindex/totalsteps * 0.2 + 0.8);
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
				
				game.RenderTextureEnd(rendertextureitem);
				
				PS_DrawPlanningFeather(toplayer, toptag, circlesgrouptag, brushx, brushy, item.time, i);
				
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
					PS_AddPlanGroupNumber(toplayer, toptag, dotsgrouptag, i, item.x, item.y);
				end
				
				local rendertextureitem = game.GetNode({toplayer, grouptag+item.plangroup+1});
				game.RenderTextureBegin(rendertextureitem);
				
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
				
				game.RenderTextureEnd(rendertextureitem);
				
				PS_DrawPlanningFeather(toplayer, toptag, dotsgrouptag, brushx, brushy, item.time, i);
				
				LGlobal_PlayData.plandots[i].time = item.time+1;
			end
		end
	end
	
	return false;
end

function PS_AddBlowPosition(toplayer, toptag, plangroup, x, y, r)
	
	local enemyinscenecount = game.GetActiveEnemyData();
	for i=0, enemyinscenecount-1 do
		if LGlobal_PlayData.blowpos[i+1] == nil then
			LGlobal_PlayData.blowpos[i+1] = {};
		end
		
		local histblowedx = 0;
		local histblowedy = 0;
		local blowedx = 0;
		local blowedy = 0;
		
		for j=plangroup, 1, -1 do
			if LGlobal_PlayData.blowpos[i+1][j] ~= nil then
				histblowedx = LGlobal_PlayData.blowpos[i+1][j].blowx;
				histblowedy = LGlobal_PlayData.blowpos[i+1][j].blowy;
				break;
			end
		end
		
		if LGlobal_PlayData.blowpos[i+1][plangroup+1] == nil then
			LGlobal_PlayData.blowpos[i+1][plangroup+1] = {};
			LGlobal_PlayData.blowpos[i+1][plangroup+1].blowx = histblowedx;
			LGlobal_PlayData.blowpos[i+1][plangroup+1].blowy = histblowedy;
		else
			blowedx = LGlobal_PlayData.blowpos[i+1][plangroup+1].blowx;
			blowedy = LGlobal_PlayData.blowpos[i+1][plangroup+1].blowy;
		end
		
			
		local costrate, blowx, blowy = game.AttackEnemy(i, WEAPON_Bomb, x, y, r, histblowedx, histblowedy);
		if costrate > 0 then
			blowx = blowx + blowedx;
			blowy = blowy + blowedy;
			LGlobal_PlayData.blowpos[i+1][plangroup+1].blowx = blowx;
			LGlobal_PlayData.blowpos[i+1][plangroup+1].blowy = blowy;
			-- Node
			local itemtag, enx, eny, etype = game.GetActiveEnemyData(i, ENEMY_InScene);
			local siid, sidesiid, sidearrowsiid, elayer = game.GetEnemyTypeData(etype, ENEMY_InScene);
			local tx, ty, elayerscale = game.GetEnemyXYScale(i);
			
			local blowdistance = global.DIST(0, 0, blowx, blowy);
			local blowangle = 9000-global.AMA(0, 0, blowx, blowy);
			
			local distscale = LConst_BlowArrowDisplayR / blowdistance;
			tx = tx + blowx*distscale;
			ty = ty + blowy*distscale;

			local layertag = toptag + CCPSTL_EnemyBlow;
			local grouptag = layertag + CCPSTM_EnemyBlow_Arrow;
			local arrownode = game.GetNode({toplayer, grouptag+i+1});
			if DtoI(arrownode) == NULL then
				local spArrow = game.CreateSprite(sidearrowsiid, {tx, ty, blowangle, elayerscale, elayerscale}, grouptag+i+1);
				arrownode = game.AddSpriteChild(spArrow, {toplayer, grouptag}, CCPSTM_EnemyBlow_Arrow);
				game.SetColor(arrownode, global.ARGB(0, 0xffffff));
				local arrowfadeactionpre = game.ActionFade(CCAF_To, 0xCF, LConst_BlinkTimePre);
				local arrowfadeactionpost = game.ActionFade(CCAF_To, 0x1F, LConst_BlinkTimePost);
				local arrowfadeaction = game.ActionSequence({arrowfadeactionpre, arrowfadeactionpost});
				arrowfadeaction = game.ActionRepeat(arrowfadeaction);
				game.RunAction(arrownode, arrowfadeaction);
			else
				game.SetPosition(arrownode, tx, ty);
				game.SetAngle(arrownode, blowangle);
			end
		end
	end
	
end