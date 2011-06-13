function PS_DoShowOver(toplayer, toptag)
	
	local missionstate, hiscore, rank, btop = game.DoMissionOver();

	local flagsiid;
	if missionstate == MISSIONSTATE_Clear then
		flagsiid = SI_MOUI_Succeeded;
	else
		flagsiid = SI_MOUI_Failed;
	end
		
	local layertag = toptag + CCPSTL_Message;
	local grouptag = layertag + CCPSTM_Message_OverBoard;
	
	local spboard = game.CreateSprite(SI_MOUI_Board, {480, 240});
	local boardnode = game.AddSpriteChild(spboard, {toplayer, grouptag}, CCPSTM_Message_OverBoard);
	
	local spflag = game.CreateSprite(flagsiid, {440, 320});
	local flagnode = game.AddSpriteChild(spflag, {toplayer, grouptag}, CCPSTM_Message_OverBoard);
	
	local str = LGlobal_TranslateGameStr_HiScore()..": "..hiscore;
	local textnode = game.AddTextChild({toplayer, grouptag}, {280, 220, CCPSTM_Message_OverBoard}, str, LConst_FontSize);
	game.SetAnchor(textnode, 0, 0.5);
	
	grouptag = layertag + CCPSTM_Message_OverMenu;
	local xorig = 660;
	local ybegin = 420;
	local yoffset = 100;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	
	for i=0, 2 do
		
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_MOUI_Next+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_MOUI_Next_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCPSTM_Message_OverMenu, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCPSTL_Message, grouptag});
	
	local moveupaction = game.ActionMove(CCAF_To, 0, 0, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, -480);
	game.RunAction(layernode, moveupaction);
	
	return false;
end


function PS_ShowOver(toplayer, toptag)
	--Add Menu and Callback
	if PS_DoShowOver(toplayer, toptag) then
		return true;
	end
	return false;
end