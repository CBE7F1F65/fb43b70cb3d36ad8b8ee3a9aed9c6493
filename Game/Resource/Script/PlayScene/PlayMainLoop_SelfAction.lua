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
		
		local itemtag, enx, eny, etype, life, elayer = game.GetActiveEnemyData(i, ENEMY_InScene);
		local tx, ty, scale = game.GetEnemyXYScale(i);
		local def;
		local costlife = 0;
			
		local nLines = table.getn(LGlobal_PlayData.planlines);
		def = game.GetEnemyDEF(etype, WEAPON_Laser);
		for j=1, nLines do
			if LGlobal_PlayData.planlines[j].plangroup == index then
				local item = LGlobal_PlayData.planlines[j];
				costlife = costlife + game.AttackEnemy(i, WEAPON_Laser, item.xb, item.yb, item.xe, item.ye)*item.atk;
			end
		end

		local nCircles = table.getn(LGlobal_PlayData.plancircles);
		def = game.GetEnemyDEF(etype, WEAPON_Bomb);
		for j=1, nCircles do
			if LGlobal_PlayData.plancircles[j].plangroup == index then
				local item = LGlobal_PlayData.plancircles[j];
				costlife = costlife + game.AttackEnemy(i, WEAPON_Bomb, item.x, item.y, item.r)*item.atk;
			end
		end

		local nDots = table.getn(LGlobal_PlayData.plandots);
		def = game.GetEnemyDEF(etype, WEAPON_Sniper);
		for j=1, nDots do
			if LGlobal_PlayData.plandots[j].plangroup == index then
				local item = LGlobal_PlayData.plandots[j];
				costlife = costlife + game.AttackEnemy(i, WEAPON_Sniper, item.x, item.y, item.r)*item.atk;
			end
		end
		
		if costlife > 0 then
			local enemynode = game.GetNode({toplayer, itemtag});
			LGlobal_PlayScene_RunShakeAction(enemynode, tx, ty);
		end
		
	end
	
	local dataindex = LGlobal_SaveData(STATE_SelfAction);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_SelfActionDelayTime, dataindex);
	local callnodegrouptag = layertag + CCPSTM_Plan_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+index+1}, {0, 0, 0, callnodegrouptag+index+1});
	game.RunAction(callnode, callfuncaction);
	return false;
end