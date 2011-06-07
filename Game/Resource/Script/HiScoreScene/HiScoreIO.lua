function _TitleScene_AddHiScoreItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_03;
	
	local spHiScoreTitle = game.CreateSprite(SI_TUI_HiScore_Title, {340, 460});
	game.AddSpriteChild(spHiScoreTitle, {toplayer, layertag});
	
	local xorig = 1224;
	local xcen = 824;
	local ybegin = 260;
	local yoffset = 160;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTag_Menu_01;
	for i=0, 1 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Reset+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Reset_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_01, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
			
end

function _TitleScene_AddHiScoreDisplay(toplayer, toptag)

	local layertag = toptag + CCTag_Layer_03;
	local grouptag = layertag + CCTag_Menu_03;
	
	game.AddNullChild({toplayer, layertag}, {0, 0, CCTag_Menu_03, grouptag});
	
	local spriteBG = game.CreateSprite(SI_White, {340, 230, 0, 600, 380});
	game.AddSpriteChild(spriteBG, {toplayer, grouptag});
	game.SetColor(spriteBG, global.ARGB(0x1f, 0xffffff));
	
	local texts = {};
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
		
		texts[i+1] = game.AddTextChild({toplayer, grouptag}, {x, y, CCTag_Menu_03, grouptag+i+1}, text, LConst_FontSize*0.8);
		game.SetAnchor(texts[i+1], 0, 0);
	end
	
end

function _TitleScene_UpdateHiScore(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_03;
	local grouptag = layertag + CCTag_Menu_03;
	game.RemoveChild({toplayer, grouptag});
	_TitleScene_AddHiScoreDisplay(toplayer, toptag);
end

function _TitleScene_AddHiScoreOKCancelItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_03;
		
	local xorig = 824;
	local xcen = 664;
	local ybegin = 340;
	local yoffset = 160;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTag_Menu_04;
	for i=0, 1 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_OK+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_OK_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTag_Menu_04, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

		local fadetime = 0.3+i*0.05;
		local menumoveaction = game.ActionMove(CCAF_To, xcen, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	
	menus[3] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTag_Menu_04, grouptag+3);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_04, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _TitleScene_EnterOKCancelHiScoreLayer(toplayer, toptag)
	_TitleScene_AddHiScoreOKCancelItems(toplayer, toptag);
end

function _TitleScene_LeaveOKCancelHiScoreLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_03;
	local grouptag = layertag + CCTag_Menu_04;
	game.RemoveChild({toplayer, grouptag});
end

function _TitleScene_EnterHiScoreLayer(toplayer, toptag)
	_TitleScene_AddHiScoreItems(toplayer, toptag);
	_TitleScene_AddHiScoreDisplay(toplayer, toptag);
end

function _TitleScene_LeaveHiScoreLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_03;
	game.RemoveAllChildren({toplayer, layertag});
end