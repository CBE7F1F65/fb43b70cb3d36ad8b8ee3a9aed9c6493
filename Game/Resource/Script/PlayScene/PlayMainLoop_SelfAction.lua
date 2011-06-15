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
		
		local itemtag, enx, eny, etype, life, elayer, status = game.GetActiveEnemyData(i, ENEMY_InScene);
		
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
					blowx = blowx+tblowx;
					blowy = blowy+tblowy;
					bBlowed = true;
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
				if not bBlowed then
					LGlobal_PlayScene_RunShakeAction(enemynode, tx, ty);
				end
			end
			
			if bBlowed then
				local moveaction = game.ActionMove(CCAF_To, tx, ty, LConst_EnemyBlowTime);
				moveaction = game.ActionEase(CCAF_In, moveaction, 0.4);
				game.RunAction(enemynode, moveaction);
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
end