function PS_SetMenuEnable(toplayer, toptag, bEnable)
	
	local layertag = toptag + CCTag_Layer_13;
	local grouptag = layertag + CCTag_Menu_01;
	
	local menunode = game.GetNode({toplayer, grouptag});
	game.SetMenuEnabled(menunode, bEnable);
	
end

function PS_SetHPAPSP(toplayer, toptag)
	
	local hp, ap, sp = game.GetHPAPSP();
	
	local layertag = toptag + CCTag_Layer_07;
	local grouptag = layertag + CCTag_Menu_01;
	
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
	
	local grouptag = layertag + CCTag_Menu_02;
	
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
	
	local layertag = toptag + CCTag_Layer_06;
	local grouptag = layertag + CCTag_Menu_01;
	
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
	
	game.SetTouchLayerRect(touchlayer, {x, y, width, height})
	
end
