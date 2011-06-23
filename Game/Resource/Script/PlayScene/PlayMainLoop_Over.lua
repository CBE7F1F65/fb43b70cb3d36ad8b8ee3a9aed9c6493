function PS_DoShowOver(toplayer, toptag)
	
	local layertag = toptag + CCPSTL_TopMessage;
	local grouptag = layertag + CCPSTM_TopMessage_EnemyEggMenu;
	local eggmenuitem = game.GetNode({toplayer, grouptag});
	local eggmenucount = game.GetChild(eggmenuitem);
	if eggmenucount == nil then
		eggmenucount = 0;
	end

	if eggmenucount > 0 then
		return false;
	end
	grouptag = layertag + CCPSTM_TopMessage_EnemyEggMenuDelay;
	local eggmenudelayitem = game.GetNode({toplayer, grouptag});
	local eggmenudelaycount = game.GetChild(eggmenuitem);

	if eggmenudelaycount == nil then
		eggmenudelaycount = 0;
	end
	if eggmenudelaycount > 0 then
		return false;
	end
	
	local missionstate = game.CheckMissionOver();
	local scorerate, score = game.GetMissionRateScore();
	
	local flagsiid;
	local eggresultscore = 0;
	if missionstate == MISSIONSTATE_Clear then
		
		eggresultscore = LGlobal_PlayData.eggcount * LConst_EggResultScore * scorerate;
		score = score + eggresultscore;
		PS_SetScore(toplayer, toptag, score);
		
		flagsiid = SI_MOUI_Succeeded;
	else
		flagsiid = SI_MOUI_Failed;
	end
	
	local hiscore, scorerank, rank, btop = game.DoMissionOver(missionstate);
	
	layertag = toptag + CCPSTL_Message;
	grouptag = layertag + CCPSTM_Message_OverBoard;
	
	local spboard = game.CreateSprite(SI_MOUI_Board, {480, 240});
	local boardnode = game.AddSpriteChild(spboard, {toplayer, grouptag}, CCPSTM_Message_OverBoard);
	
	local spflag = game.CreateSprite(flagsiid, {440, 320});
	local flagnode = game.AddSpriteChild(spflag, {toplayer, grouptag}, CCPSTM_Message_OverBoard);
	
	local starxbegin = 400;
	local starxoffset = 60;
	local stary = 360;
	for i=0, 2 do
		local spStar = game.CreateSprite(SI_GUI_Star, {starxbegin+i*starxoffset, stary});
		local starnode = game.AddSpriteChild(spStar, {toplayer, grouptag}, CCPSTM_Message_OverBoard);
		if i > rank then
			game.SetColor(starnode, global.ARGB(0xff, 0x404040));
		elseif i > scorerank then
			game.SetColor(starnode, global.ARGB(0xff, 0x808080));
		end
	end
	
	local resultx = 280;
	local resultxcen = 320;
	local resultybegin = 360;
	local resultyoffset = 40;
	local resultfontscale = 0.3;
	local str;
	
	if missionstate == MISSIONSTATE_Clear then
		str = string.format("%c*%d*%d*%.1f", LConst_AtlasIndex_Egg, LGlobal_PlayData.eggcount, LConst_EggResultScore, scorerate);
		local atlasnodeeggcount = LGlobal_AddAtlasTextChild({toplayer, grouptag}, {resultxcen, resultybegin, CCPSTM_Message_OverBoard}, str, resultfontscale);
	
	
		str = string.format("  = %d", eggresultscore);
		local atlasnodeeggresult = LGlobal_AddAtlasTextChild({toplayer, grouptag}, {resultxcen, resultybegin-resultyoffset, CCPSTM_Message_OverBoard}, str, resultfontscale);
	
	end
	
	str = LGlobal_TranslateGameStr_Score()..": "..score;
	local atlasscorenode = LGlobal_AddAtlasTextChild({toplayer, grouptag}, {resultx, resultybegin-resultyoffset*2, CCPSTM_Message_OverBoard}, str, resultfontscale);
	game.SetAnchor(atlasscorenode, 0, 0.5);
	
	str = LGlobal_TranslateGameStr_HiScore()..": "..hiscore;
	local atlashiscorenode = LGlobal_AddAtlasTextChild({toplayer, grouptag}, {resultx, resultybegin-resultyoffset*3, CCPSTM_Message_OverBoard}, str, resultfontscale);
	game.SetAnchor(atlashiscorenode, 0, 0.5);
	
	grouptag = layertag + CCPSTM_Message_OverMenu;
	local xorig = 660;
	local ybegin = 420;
	local yoffset = 100;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	
	local missionindex, stageindex = game.GetNextAvailableMission();
	
	local j = 0;
	if missionindex == nil then
		j = 1;
	end
	for i=0, 2-j do
		
		local y = ybegin - j*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_MOUI_Next+j*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_MOUI_Next_Down+j*2);
		
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCPSTM_Message_OverMenu, grouptag+j+1}, spMenus[i+1], spSelectedMenus[i+1]);
		j = j + 1;

	end
		
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCPSTL_Message, grouptag});
	
	local moveupaction = game.ActionMove(CCAF_To, 0, 0, LConst_BoardMoveTime);
	local layernode = game.GetNode({toplayer, layertag});
	game.SetPosition(layernode, 0, -480);
	game.RunAction(layernode, moveupaction);
	
	return true;
end


function PS_ShowOver(toplayer, toptag)
	--Add Menu and Callback
	if PS_DoShowOver(toplayer, toptag) then
		return true;
	end
	return false;
end