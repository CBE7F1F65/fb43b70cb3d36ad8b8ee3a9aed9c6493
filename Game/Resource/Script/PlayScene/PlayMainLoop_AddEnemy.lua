function PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer)

	local layertag = toptag + CCPSTL_Enemy;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;
	
	local siid, sidesiid, sidearrowsiid, defelayer = game.GetEnemyTypeData(etype);
	if elayer == nil then
		elayer = defelayer;
	end
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	local eindex = game.AddEnemy(grouptag+selitemtag, x, y, etype, elayer, ENEMY_InScene);

	local tx, ty, scale = game.GetEnemyXYScale(eindex);
	
	local spEnemy = game.CreateSprite(siid, {tx, ty, 0, scale, scale}, grouptag+selitemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag}, elayer);
	
	return enemynode, layertag, grouptag, selitemtag, eindex;
end

function PS_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission)
	
	--skip event mission
	local eposturnitem = LGlobal_EnemyPosTable[nowstage+1][nowmission][1];
	if index >= table.getn(eposturnitem) then
		return true;
	end
		
	local epositem = eposturnitem[index+1];
	local x, y, etype, elayer = epositem[1], epositem[2], epositem[3], epositem[4];
	
	local enemynode, layertag, grouptag, selitemtag = PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, 0, elayer);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));	
	local enemyaction = game.ActionFade(CCAF_To, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);

	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodegrouptag = layertag + CCPSTM_Enemy_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
	return false;
end

function PS_AddEnemy(toplayer, toptag, index)
	
	-- Check all enemy added
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if PS_AddEnemyToSide(toplayer, toptag, index, nowstage, nowmission, nowturn) then
		return true;
	end
	
	return false;
end