function PS_ShowTurnStartAndTarget(toplayer, toptag, bRequireClose)
	
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
		PSCB_TurnStartAndTarget(nil, toplayer, toptag, CCTag_Layer_04, nil, 1, LConst_BoardMoveTime+LConst_BoardShowTime);
	else
		grouptag = layertag + CCTag_Menu_04;
		local menuitem = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTag_Menu_04, grouptag+1);
		local menu = game.AddMenuChild({menuitem}, {toplayer, layertag}, {0, 0, CCTag_Menu_04, grouptag});
	end
	
	game.RunAction(layernode, moveupaction);
	
	layertag = toptag + CCTag_Layer_11;	
	local layernode = game.GetNode({toplayer, layertag});
	local fadeaction = game.ActionFade(CCAF_To, 0, LConst_ItemVanishTime);
	local tintaction = game.ActionTint(CCAF_To, 0, LConst_ItemVanishTime);
	local spaction = game.ActionSpawn({fadeaction, tintaction});
	game.RunAction(layernode, spaction);
	
	return false;
end


function PS_ShowTurnStart(toplayer, toptag)
	--Add Menu and Callback
	if PS_ShowTurnStartAndTarget(toplayer, toptag) then
		return true;
	end
--	PS_StepForward(STATE_ShowTurnStart);
	return false;
end