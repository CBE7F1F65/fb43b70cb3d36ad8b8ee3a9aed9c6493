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
	
	local hpslowbar = game.GetNode({toplayer, grouptag+1});
	local hpbar = game.GetNode({toplayer, grouptag+2});
	local apslowbar = game.GetNode({toplayer, grouptag+3});
	local apbar = game.GetNode({toplayer, grouptag+4});
	
	if LGlobal_PlayData.nowhp ~= hp then
		local oldhp = LGlobal_PlayData.nowhp;
		LGlobal_PlayData.nowhp = hp;
		if hp < 0 then
			hp = 0;
		end
		local hpscale = hp/10000.0;
		local hpscaleaction = game.ActionScale(CCAF_To, hpscale, 1, LConst_HPAPChangeTime, true);
		if oldhp > hp then
			game.RunAction(hpslowbar, hpscaleaction);
			game.StopAction(hpbar);
			game.SetScale(hpbar, hpscale, 1);
		else
			game.RunAction(hpbar, hpscaleaction);
			game.StopAction(hpslowbar);
			game.SetScale(hpslowbar, hpscale, 1);
		end
	end
	
	if LGlobal_PlayData.nowap ~= ap then
		local oldap = LGlobal_PlayData.nowap;
		LGlobal_PlayData.nowap = ap;
		if ap < 0 then
			ap = 0;
		end
		local apscale = ap/10000.0;
		local apscaleaction = game.ActionScale(CCAF_To, apscale, 1, LConst_HPAPChangeTime, true);
		if oldap > ap then
			game.RunAction(apslowbar, apscaleaction);
			game.StopAction(apbar);
			game.SetScale(apbar, apscale, 1);
		else
			game.RunAction(apbar, apscaleaction);
			game.StopAction(apslowbar);
			game.SetScale(apslowbar, apscale, 1);
		end
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
	
	local scorestr = LGlobal_TranslateGameStr_Score()..": "..score;
	local scorestr = string.format("%s (%.1f)", scorestr, scorerate);
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