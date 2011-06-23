function PS_SelfAction(toplayer, toptag, index)
	-- Check all self action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local layertag = toptag+CCPSTL_Plan;
	local grouptag = layertag+CCPSTM_Plan_RenderTexture;
	
	if index == 0 then
		grouptag = layertag+CCPSTM_Plan_LinesFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCPSTM_Plan_CirclesFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		grouptag = layertag+CCPSTM_Plan_DotsFeather;
		local groupnode = game.GetNode({toplayer, grouptag});
		game.RemoveAllChildren(groupnode);
		
	end
	
	if PS_DoSelfAction(toplayer, toptag, index, nowstage, nowmission, nowturn) then
		LGlobal_PlayData.planlines = {};
		LGlobal_PlayData.plandots = {};
		LGlobal_PlayData.plancircles = {};
		return true;
	end
	
	return false;
end

function PS_DoSelfAction(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local plangroup = LGlobal_PlayData.plangroup;
	if index > plangroup or index >= LConst_PlanGroupMax then
		return true;
	end
	local layertag = toptag+CCPSTL_Plan;
	local grouptag = layertag+CCPSTM_Plan_RenderTexture;
	local rendertextureitem = game.GetNode({toplayer, grouptag+index+1});
	game.RenderTextureBegin(rendertextureitem, true);
	game.RenderTextureEnd(rendertextureitem);
	
	local enemyinscenecount = game.GetActiveEnemyData();
	
	for i=0, enemyinscenecount-1 do
		
		local itemtag, enx, eny, etype, life, elayer, angle, status = game.GetActiveEnemyData(i, ENEMY_InScene);
		
		if life > 0 then
		
			local def;
			local defrate = 1;
			if status == ENEMYSTATUS_Blowed then
				defrate = 0.5;
			end
			
			local costlife = 0;
			local blowx = 0;
			local blowy = 0;
			local bBlowed = false;
			
			local nLines = table.getn(LGlobal_PlayData.planlines);
			def = game.GetEnemyDEF(etype, WEAPON_Laser)*defrate;
			for j=1, nLines do
				if LGlobal_PlayData.planlines[j].plangroup == index then
					local item = LGlobal_PlayData.planlines[j];
					local costrate = game.AttackEnemy(i, WEAPON_Laser, item.xb, item.yb, item.xe, item.ye);
					local atk = item.atk*costrate-def;
					if atk > 0 then
						costlife = costlife + atk;
					end
				end
			end

			local nCircles = table.getn(LGlobal_PlayData.plancircles);
			def = game.GetEnemyDEF(etype, WEAPON_Bomb)*defrate;
			for j=1, nCircles do
				if LGlobal_PlayData.plancircles[j].plangroup == index then
					local item = LGlobal_PlayData.plancircles[j];
					local costrate, tblowx, tblowy = game.AttackEnemy(i, WEAPON_Bomb, item.x, item.y, item.r);
					local atk = item.atk*costrate-def;
					if atk > 0 then
						costlife = costlife + atk;
					end
					if costrate > 0 then
						blowx = blowx+tblowx;
						blowy = blowy+tblowy;
						bBlowed = true;
					end
				end
			end

			local nDots = table.getn(LGlobal_PlayData.plandots);
			def = game.GetEnemyDEF(etype, WEAPON_Sniper)*defrate;
			for j=1, nDots do
				if LGlobal_PlayData.plandots[j].plangroup == index then
					local item = LGlobal_PlayData.plandots[j];
					local costrate = game.AttackEnemy(i, WEAPON_Sniper, item.x, item.y, item.r);
					local atk = item.atk*costrate-def;
					if atk > 0 then
						costlife = costlife + atk;
					end
				end
			end
			
			local enemynode = game.GetNode({toplayer, itemtag});
			local tx, ty = game.GetEnemyXYScale(i);
			
			if costlife > 0 then
				life = life - costlife;
				if not bBlowed then
					LGlobal_PlayScene_RunShakeAction(enemynode, tx, ty);
				end				
			end
			
			if life <= 0 then
				life = 0;
				PS_EnemyDead(toplayer, toptag, i, enemynode, status);
			else
				local statustoset = ENEMYSTATUS_Normal;
				if bBlowed then
					statustoset = ENEMYSTATUS_Blowed;
				end
				game.SetActiveEnemyData(i, ENEMY_InScene, life, elayer, blowx, blowy, statustoset);
				tx, ty = game.GetEnemyXYScale(i);
			end
			
			if bBlowed then
				local moveaction = game.ActionMove(CCAF_To, tx, ty, LConst_EnemyBlowTime);
				moveaction = game.ActionEase(CCAF_In, moveaction, 0.4);
				game.RunAction(enemynode, moveaction);
			end
			
			if costlife > 0 then
				PS_AddLifeCostScore(toplayer, toptag, i, costlife);
			end
			
		end
		
	end
	
	local dataindex = LGlobal_SaveData(STATE_SelfAction);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_SelfActionDelayTime, dataindex);
	local callnodegrouptag = layertag + CCPSTM_Plan_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+index+1}, {0, 0, 0, callnodegrouptag+index+1});
	game.RunAction(callnode, callfuncaction);
	return false;
end

function PS_EnemyDead(toplayer, toptag, index, enemynode, status)
	
	if status == ENEMYSTATUS_Blowed then
		local scorerate = game.GetMissionRateScore();
		scorerate = scorerate + LConst_ScoreRateComboPlus;
		game.SetMissionRateScore(scorerate);
		PS_ProduceEgg(toplayer, toptag, index);
	end
	
	local fadeoutaction = game.ActionFade(CCAF_To, 0, LConst_EnemySpriteFadeTime);
	local deleteaction = game.ActionDelete(LConst_SelfActionDelayTime);
	local enemyaction = game.ActionSequence({fadeoutaction, deleteaction});
	game.RunAction(enemynode, enemyaction);
	
	game.RemoveEnemy(index, ENEMY_InScene);
end

function PS_ProduceEgg(toplayer, toptag, index)
	local tx, ty = game.GetEnemyXYScale(index);
	
	local layertag = toptag + CCPSTL_TopMessage;
	local grouptag = layertag + CCPSTM_TopMessage_EnemyEggMenu;
	
	local eggindex = game.GetEnemyEggIndex(index);
	local eggSIID;
	
	local item;
	
	local rectx, recty, rectw, recth = game.GetEnemyPositionRect();
	local bBroken = not global.PointInRect(tx, ty, rectx, recty, rectw, recth, LConst_EggBrokenEdge, LConst_EggBrokenEdge);
	if bBroken then
		eggSIID = SI_GUI_BrokenGoldenEgg;
		if eggindex == 0 then
			eggSIID = SI_GUI_BrokenEgg;
		end
		local spEgg = game.CreateSprite(eggSIID, {tx, ty});
		item = game.AddSpriteChild(spEgg, {toplayer, layertag});
	else
		eggSIID = SI_GUI_GoldenEgg;
		if eggindex == 0 then
			eggindex = index + MISSION_GoldenEggMax+1;
			eggSIID = SI_GUI_Egg;
		end
		local spEgg = game.CreateSprite(eggSIID);
		local spSelectedEgg = game.CreateSprite(eggSIID);
	
		item = game.CreateMenuItem({toplayer, grouptag}, {tx, ty, CCPSTM_TopMessage_EnemyEggMenu, grouptag+eggindex}, spEgg, spSelectedEgg);
		game.SetColor(item, global.ARGB(0, 0xffffff));
	end
	
	local fadeinaction = game.ActionFade(CCAF_To, 0xff, LConst_ItemVanishTime);
	local bezieraction = game.ActionBezier(CCAF_To, LConst_EggJumpActionTime, tx, ty+30, tx, ty-30, tx, ty);
	bezieraction = game.ActionEase(CCAF_In, bezieraction, 0.7);
	fadeinaction = game.ActionSpawn({fadeinaction, bezieraction});
	local fadeoutaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
	local deleteaction = game.ActionDelete();
	local jumpaction = game.ActionSequence({fadeinaction, fadeoutaction, deleteaction});
	game.RunAction(item, jumpaction);
	
	if not bBroken then
		local menunode = game.GetNode({toplayer, grouptag});
		if DtoI(menunode) == NULL then
			game.AddMenuChild({item}, {toplayer, layertag}, {0, 0, CCPSTM_TopMessage_EnemyEggMenu, grouptag});
		else
			game.AddMenuItemChild(item, {toplayer, grouptag});
		end
	end
	
end

function PS_AddLifeCostScore(toplayer, toptag, index, costlife)
	
	local scorerate, score = game.GetMissionRateScore();
	score = score + costlife*scorerate*LConst_EnemyLifeCostScore;
	PS_SetScore(toplayer, toptag, score);
	
end