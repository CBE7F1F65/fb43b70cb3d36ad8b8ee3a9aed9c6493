function PS_SetMenuEnable(toplayer, toptag, bEnable)
	
	local layertag = toptag + CCPSTL_Menu;
	local grouptag = layertag + CCPSTM_Menu_Main;
	
	local menunode = game.GetNode({toplayer, grouptag});
	game.SetMenuEnabled(menunode, bEnable);
	
end

function PS_SetHPAPSP(toplayer, toptag)
	
	local hp, ap, sp = game.GetHPAPSP();
	
	local layertag = toptag + CCPSTL_HPAPSP;
	local grouptag = layertag + CCPSTM_HPAPSP_HPAP;
	
	local hpbar = game.GetNode({toplayer, grouptag+1});
	local apbar = game.GetNode({toplayer, grouptag+2});
	
	if LGlobal_PlayData.nowhp ~= hp then
		LGlobal_PlayData.nowhp = hp;
		if hp < 0 then
			hp = 0;
		end
		local hpscaleaction = game.ActionScale(CCAF_To, hp/10000.0, 1, LConst_HPAPChangeTime, true);
		game.RunAction(hpbar, hpscaleaction);
	end
	
	if LGlobal_PlayData.nowap ~= ap then
		LGlobal_PlayData.nowap = ap;
		if ap < 0 then
			ap = 0;
		end
		local apscaleaction = game.ActionScale(CCAF_To, ap/10000.0, 1, LConst_HPAPChangeTime, true);
		game.RunAction(apbar, apscaleaction);
	end
	
	local grouptag = layertag + CCPSTM_HPAPSP_SP;
	
	if LGlobal_PlayData.nowsp ~= sp then
		local nowsp = LGlobal_PlayData.nowsp;
		LGlobal_PlayData.nowsp = sp;
		
		if nowsp > sp then
			for i=sp+1, nowsp do
				local spitem = game.GetNode({toplayer, grouptag+i});
				local spfadeaction = game.ActionFade(CCAF_To, 0, LConst_SPChangeTime);
				game.RunAction(spitem, spfadeaction);
			end
		else
			for i=nowsp+1, sp do
				local spitem = game.GetNode({toplayer, grouptag+i});
				local spfadeaction = game.ActionFade(CCAF_To, 0xFF, LConst_SPChangeTime);
				game.RunAction(spitem, spfadeaction);
			end
		end
	end
	
	
end

function PS_SetTouchLayerRect(toplayer, toptag)
	
	local layertag = toptag + CCPSTL_Touch;
	local grouptag = layertag + CCPSTM_Touch_Layer;
	
	local touchlayer = game.GetNode({toplayer, grouptag});
	
	local xcen, ycen, width, height;
	
	if LGlobal_PlayData.bZoomed then
		xcen = 480;
		ycen = 320;
		width = 960;
		height = 640;
	else
		xcen = 480;
		ycen = 336;
		width = 832;
		height = 480;
	end
	
	local x = xcen-width/2;
	local y = ycen-height/2;
	
	game.SetTouchLayerRect(touchlayer, {x, y, width, height});
	return x, y, width, height;
	
end

function PS_UpdateScoreDisplay(toplayer, toptag)
	local scorerate, score, hiscore = game.GetMissionRateScore();
	local layertag = toptag + CCPSTL_TopMessage;
	local grouptag = layertag + CCPSTM_TopMessage_Score;
	
	local scorestr = LGlobal_TranslateGameStr_Score()..": "..score.." ("..scorerate..")";
	if score > hiscore then
		hiscore = score;
	end
	local hiscorestr = LGlobal_TranslateGameStr_HiScore()..": "..hiscore;
		
	local hiscoreatlasnode = game.GetNode({toplayer, grouptag+1});
	game.SetAtlasTextString(hiscoreatlasnode, hiscorestr);
	local scoreatlasnode = game.GetNode({toplayer, grouptag+2});
	game.SetAtlasTextString(scoreatlasnode, scorestr);
end

function PS_SetScore(toplayer, toptag, nowscore)
	game.SetMissionRateScore(-1, nowscore);
	PS_UpdateScoreDisplay(toplayer, toptag);
end