function PS_SidePosToScenePos(x, y, angle)
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

function PS_MoveSideEnemyToScene(toplayer, toptag, index, nowstage, nowmission, nowturn)
	local layertag = toptag + CCPSTL_EnemyOnSide;
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

	local enemynode, layertag, grouptag, selitemtag = PS_CreateEnemySprite(toplayer, toptag, index, etype, x, y, nowturn, elayer);
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
		
	local dataindex = LGlobal_SaveData(STATE_EnemyEnter);	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);	
	local callnodegrouptag = layertag + CCPSTM_Enemy_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
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

	local tx, ty = PS_SidePosToScenePos(x, y, angle)

	game.AddEnemy(grouptag+selitemtag, tx, ty, etype, elayer, ENEMY_OnSide, angle);
	
	return enemynode, layertag, grouptag, selitemtag;
end

function PS_AddEnemyToSide(toplayer, toptag, index, nowstage, nowmission, nowturn)
	
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
	
	local enemynode, layertag, grouptag, selitemtag = PS_CreateEnemySideSprite(toplayer, toptag, index, etype, x, y, angle, nowturn);
	
	game.SetColor(enemynode, global.ARGB(0, 0xffffff));
	
	local enemyaction = game.ActionFade(CCAF_In, 0xFF, LConst_EnemySpriteFadeTime);
	game.RunAction(enemynode, enemyaction);
	
	local dataindex = LGlobal_SaveData(STATE_AddEnemy);	
	local callfuncaction = game.ActionCallFunc({toplayer, toptag}, LConst_EnemyEnterDelayTime, dataindex);	
	local callnodegrouptag = layertag + CCPSTM_Enemy_CallNode;
	local callnode = game.AddNullChild({toplayer, grouptag+selitemtag}, {0, 0, 0, callnodegrouptag+selitemtag});
	game.RunAction(callnode, callfuncaction);
	
	return false;
end