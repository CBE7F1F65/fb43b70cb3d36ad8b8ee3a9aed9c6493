function PS_ShowTurnStartAndTarget(toplayer, toptag, bRequireClose)
	
	local nowstage, nowmission, nowturn = game.GetNowStageMissionTurn();
	local missiontype = game.GetMissionAimData();
	
	if nowturn == 0 and missiontype == MISSIONTYPE_Normal then
		return true;
	end
	
	local layertag = toptag + CCPSTL_Message;
	local grouptag = layertag + CCPSTM_Message_TargetBoard;
	
	local spboard = game.CreateSprite(SI_MOUI_Board, {480, 240});
	local boardnode = game.AddSpriteChild(spboard, {toplayer, grouptag}, CCPSTM_Message_TargetBoard);
	
	local sptarget = game.CreateSprite(SI_MOUI_Target, {480, 400});
	local targetnode = game.AddSpriteChild(sptarget, {toplayer, grouptag}, CCPSTM_Message_TargetBoard);
	
	if nowturn > 0 then
		local str = LGlobal_TranslateGameStr_NowTurn(nowturn);
		local atlasnode = LGlobal_AddAtlasTextChild({toplayer, grouptag}, {480, 280, CCPSTM_Message_TargetBoard}, str, 1);
		game.SetAnchor(atlasnode, 0.5, 0.5);
	end
	
	local moveupaction = game.ActionMove(CCAF_To, 0, 0, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, -480);
	
	if bRequireClose == nil or not bRequireClose then
		PSCB_TurnStartAndTarget(nil, toplayer, toptag, CCPSTL_Message, nil, 1, LConst_BoardMoveTime+LConst_BoardShowTime);
	else
		grouptag = layertag + CCPSTM_Message_TargetMenu;
		local menuitem = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCPSTM_Message_TargetMenu, grouptag+1);
		local menu = game.AddMenuChild({menuitem}, {toplayer, layertag}, {0, 0, CCPSTM_Message_TargetMenu, grouptag});
	end
	
	game.RunAction(layernode, moveupaction);
	
	layertag = toptag + CCPSTL_Plan;	
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