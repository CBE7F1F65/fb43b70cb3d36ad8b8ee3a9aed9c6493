function PS_SidePosToScenePos(x, y, angle)
	local r;
	if x <= LConst_EnemySideLEdge then
		r = x*(480-LConst_EnemySideEdge)/LConst_EnemySideEdge+(LConst_EnemySideLEdge-x);
	elseif x>=LConst_EnemySideREdge then
		r = (960-x)*(480-LConst_EnemySideEdge)/LConst_EnemySideEdge+(x-LConst_EnemySideREdge);
	elseif y>=LConst_EnemySideBEdge then
		r = (y-LConst_EnemySideBEdge)*(960-LConst_EnemySideTEdge-LConst_EnemySideEdge)/LConst_EnemySideEdge+(y-LConst_EnemySideBEdge);
	end
	
	if r ~= nil then
		x = x+r*global.SINT(angle);
		y = y+r*global.COST(angle);
	end
	return x, y;
end

function PS_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn)

	local layertag = toptag + CCPSTL_EnemyOnSide;
	local grouptag = layertag + CCTag_MenuSub_01*(nowturn+1);
	local enemyinscenecount, enemyonsidecount = game.GetActiveEnemyData();
	if index >= enemyonsidecount then
		return true;
	end
	local selitemtag = index + 1;
	local onsideitemtag, x, y, etype, life, elayer, angle = game.GetActiveEnemyData(index, ENEMY_OnSide);
	
	local enemynode, layertag, grouptag, itemtag, eindex = PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer);
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
	
	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodeitemtag = LGlobal_PlayScene_GetEnemyCallNodeItemtag(itemtag);
	local callnode = game.AddNullChild({toplayer, itemtag}, {0, 0, 0, callnodeitemtag});

	game.RunAction(callnode, callfuncaction);
	
	local tx, ty, scale = game.GetEnemyXYScale(eindex);
	
	local enemyonsidenode = game.GetNode({toplayer, onsideitemtag});
	local onsidemoveaction = game.ActionMove(CCAF_To, tx, ty, LConst_EnemySpriteFadeTime*2);
	local onsidealphaaction = game.ActionFade(CCAF_To, 0, LConst_EnemySpriteFadeTime*2);
	local onsidedeleteaction = game.ActionDelete();
	onsidedeleteaction = game.ActionSequence({onsidealphaaction, onsidedeleteaction});
	local onsidedeletechildrenaction = game.ActionDeleteChildren(LConst_EnemySpriteFadeTime);
	local onsideaction = game.ActionSpawn({onsidemoveaction, onsidedeleteaction, onsidedeletechildrenaction});
	onsideaction = game.ActionEase(CCAF_In, onsideaction, 0.35);
	game.RunAction(enemyonsidenode, onsideaction);
		
	game.RemoveEnemy(index, ENEMY_OnSide);
	
	return false;
	
end

function PS_EnemyEnter(toplayer, toptag, index)

	-- Check all enemy in
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	if nowturn == 0 then
		if PS_AddInitEnemyToScene(toplayer, toptag, index, nowstage, nowmission) then
			return true;
		end
	else
		if PS_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn) then
			return true;
		end
	end
	
	return false;
end

function PS_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn)
	local layertag = toptag + CCPSTL_EnemyOnSide;
	local menugroup = CCTag_MenuSub_01*(nowturn+1);
	local grouptag = layertag + menugroup;
	
	local selitemtag = index+1;

	local siid, sidesiid, sidearrowsiid, elayer = game.GetEnemyTypeData(etype);
	
	local groupnode = game.GetNode({toplayer, grouptag});
	if DtoI(groupnode) == NULL then
		game.AddNullChild({toplayer, layertag}, {0, 0, menugroup+elayer, grouptag});
	end

	local itemtag = grouptag+selitemtag;
	local spEnemy = game.CreateSprite(sidesiid, {x, y}, itemtag);
	local enemynode = game.AddSpriteChild(spEnemy, {toplayer, grouptag});
	local spEnemySideArrow = game.CreateSprite(sidearrowsiid, {64, 64, angle, 2, 2}, itemtag);
	local enemysidearrownode = game.AddSpriteChild(spEnemySideArrow, {toplayer, itemtag});
	
	game.SetColor(enemysidearrownode, global.ARGB(0, 0xffffff));
	local arrowfadeactionpre = game.ActionFade(CCAF_To, 0xCF, LConst_BlinkTimePre);
	local arrowfadeactionpost = game.ActionFade(CCAF_To, 0x1F, LConst_BlinkTimePost);
	local arrowfadeaction = game.ActionSequence({arrowfadeactionpre, arrowfadeactionpost});
	arrowfadeaction = game.ActionRepeat(arrowfadeaction);
	game.RunAction(enemysidearrownode, arrowfadeaction);

	local tx, ty = PS_SidePosToScenePos(x, y, angle);

	game.AddEnemy(itemtag, tx, ty, etype, elayer, ENEMY_OnSide, angle);
	
	return enemynode, layertag, grouptag, itemtag;
end

function PS_AddEnemyToSide(toplayer, toptag, index, nowstage, nowmission, nowturn)

	local missionenemyindex, x, y, etype, angle = game.GetMissionEnemy(1);
	
	if missionenemyindex == nil then
		return true;
	end
	
	local enemynode, layertag, grouptag, itemtag = PS_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
	
	local dataindex = LGlobal_SaveData(STATE_AddEnemy);
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);
	local callnodeitemtag = LGlobal_PlayScene_GetEnemyCallNodeItemtag(itemtag);
	local callnode = game.AddNullChild({toplayer, itemtag}, {0, 0, 0, callnodeitemtag});
	game.RunAction(callnode, callfuncaction);
	
	return false;
end