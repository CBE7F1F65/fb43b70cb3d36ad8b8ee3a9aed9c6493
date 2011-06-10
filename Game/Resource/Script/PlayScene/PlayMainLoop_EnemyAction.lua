function PS_EnemyAttack(toplayer, toptag, index, etype, elayer)
	local atk, apatk, hpregainatk = game.GetEnemyATK(etype, elayer/CCZ_eLayer_01);
	local hp, ap, sp = game.GetHPAPSP();
	hp = hp - atk;
	ap = ap - apatk;
	game.SetHPAPSP(hp, ap, sp);
	if hpregainatk > 0 then
		-- Add Enemy HP
	end
	
	-- Animation
	if atk > 0 then
		LGlobal_PlayScene_RunShakeAction(toplayer, 0, 0);
	end
	
end

function PS_EnemyAdvanceELayer(toplayer, toptag, index, etype, elayer)
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

function PS_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn, bZeroLayerOnly)
	local enemyinscenecount = game.GetActiveEnemyData();
	if index >= enemyinscenecount then
		return true;
	end
	
	local doaction = true;
	local doadvance = true;
	
	local layertag = toptag + CCPSTL_Enemy;
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
		PS_EnemyAttack(toplayer, toptag, index, etype, elayer);
	end
	if doadvance then
		PS_EnemyAdvanceELayer(toplayer, toptag, index, etype, elayer);
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
	local callnodegrouptag = layertag + CCPSTM_Enemy_CallNode;
	local callnode = game.AddNullChild({toplayer, itemtag}, {0, 0, 0, callnodegrouptag+index+1});
	game.RunAction(callnode, callfuncaction);
	return false;
end

function PS_EnemyAction(toplayer, toptag, index)
	-- Check all enemy action done
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if PS_DoEnemyAction(toplayer, toptag, index, nowstage, nowmission, nowturn) then
		return true;
	end
	
	return false;
end