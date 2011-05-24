function _TitleScene_AddHiScoreItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_03;
	
	local spHiScoreTitle = game.CreateSprite(SI_TUI_HiScore_Title, {340, 460});
	game.AddSpriteChild(spHiScoreTitle, {toplayer, layertag});
	
	local xorig = 1180;
	local xcen = 780;
	local ybegin = 284;
	local yoffset = 108;
	
	local spTitleMenus = {};
	local spTitleSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 1 do
		local y = ybegin - (1-i)*yoffset;
		
		spTitleMenus[i+1] = game.CreateSprite(SI_TUI_Close+i*2);
		spTitleSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Close_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spTitleMenus[i+1], spTitleSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, 0x9F, blinktimepre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		local menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
			
end

function _TitleScene_AddHiScoreDisplay(toplayer, toptag)

	local layertag = toptag + CCTag_Layer_03;
	local menus = {};
	local count = game.GetHiScoreData();
	local x = 45;
	local ybegin = 380;
	local yoffset = 24;
	local text, inputmax = game.GetUsername();
	local namelengthmax = inputmax + 1;
		
	for i=0, count-1 do
		local text = "";
		local username, hiscore = game.GetHiScoreData(i);
		local y = ybegin - i*yoffset;
		
		local namelength = string.len(username);
		if i+1 < 10 then
			text = '0';
		end
		text = text..(i+1)..'.'..username;

		for j=0, namelengthmax - namelength do
			text = text..'-'
		end
		
		local hiscoretext = hiscore;
		local hiscoretextlength = string.len(hiscoretext);
		for j=0, LConst_ScoreDigitMax-hiscoretextlength do
			hiscoretext = '0'..hiscoretext;
		end
		text = text..hiscoretext;
		
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {x, y, CCTag_Menu_03, layertag+CCTag_Menu_03+i+1}, text, LConst_FontSize*0.8);
		game.SetAnchor(menus[i+1], 0, 0);
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_03, layertag+CCTag_Menu_03});
	game.SetTouchEnabled(menu, false);
	
end

function _TitleScene_EnterHiScoreLayer(toplayer, toptag)
	_TitleScene_AddHiScoreItems(toplayer, toptag);
	_TitleScene_AddHiScoreDisplay(toplayer, toptag);
end

function _TitleScene_LeaveHiScoreLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_03;
	game.RemoveAllChildren({toplayer, layertag});
end