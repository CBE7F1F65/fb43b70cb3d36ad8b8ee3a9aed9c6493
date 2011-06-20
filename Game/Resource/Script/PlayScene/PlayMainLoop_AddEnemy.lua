function PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, eggindex, nowturn, elayer)

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
		game.AddNullChild({toplayer, layertag}, {0, 0, CCZ_Max-(menugroup+elayer), grouptag}); --z=menugroup+elayer
	end

	local itemtag = grouptag+selitemtag;
	local eindex = game.AddEnemy(itemtag, x, y, etype, elayer, eggindex, ENEMY_InScene);

	local tx, ty, scale = game.GetEnemyXYScale(eindex);
	
	local spEnemy = game.CreateSprite(siid, {tx, ty, 0, scale, scale}, itemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag}, elayer);
	
	return enemynode, layertag, grouptag, itemtag, eindex;
end

function PS_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission)
	
	local missionenemyindex, x, y, etype, elayerindex, eggindex = game.GetMissionEnemy();
	
	if missionenemyindex == nil then
		return true;
	end
	local elayer = elayerindex*CCZ_eLayer_01;
	
	local enemynode, layertag, grouptag, itemtag = PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, eggindex, 0, elayer);

	game.SetColor(enemynode, global.ARGB(0, 0xffffff));	
	local enemyaction = game.ActionFade(CCAF_To, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);

	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodeitemtag = LGlobal_PlayScene_GetEnemyCallNodeItemtag(itemtag);
	local callnode = game.AddNullChild({toplayer, itemtag}, {0, 0, 0, callnodeitemtag});
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