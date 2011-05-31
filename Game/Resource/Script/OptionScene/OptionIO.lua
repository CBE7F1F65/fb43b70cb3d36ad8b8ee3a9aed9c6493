

function _TitleScene_AddOptionTouchLayer(toplayer, toptag)
	
	local xcen = 780;
	local ycen = 550;
	
	local width, height = game.GetSIData(SI_TUI_BGMSE_Bar);
	local bgmvol, sevol = game.GetBGMSEVol();
	
	local x = xcen - width / 2;
	local y = ycen - height / 2;
	local layertag = toptag + CCTag_Layer_06;
	
	--BGM
	local spritebgBGM = game.CreateSprite(SI_TUI_BGMSE_Bar, {x, y}, layertag+CCTag_Menu_01);
	game.AddSpriteChild(spritebgBGM, {toplayer, layertag});
	game.SetAnchor(spritebgBGM, 0, 0);
	game.SetScale(spritebgBGM, bgmvol/100.0, 1);
	
	local spritebgBGMFrame = game.CreateSprite(SI_TUI_BGMSE_Frame, {xcen, ycen});
	game.AddSpriteChild(spritebgBGMFrame, {toplayer, layertag});
	
	local spriteBGM = game.CreateSprite(SI_TUI_BGM, {xcen-160, ycen});
	game.AddSpriteChild(spriteBGM, {toplayer, layertag});
	game.SetColor(spriteBGM, global.ARGB(0x7f, 0xffffff));
		
	local touchlayerBGM = game.AddTouchLayerChild(
			{toplayer, {x, y, width, height}},
			{toplayer, layertag},
			{0, 0, CCTag_Layer_06, layertag+CCTag_Menu_01}
		);
	
	--SE
	layertag = toptag + CCTag_Layer_07;
	ycen = ycen - 80;
	y = ycen - height / 2;
	local spritebgSE = game.CreateSprite(SI_TUI_BGMSE_Bar, {x, y}, layertag+CCTag_Menu_01);
	game.AddSpriteChild(spritebgSE, {toplayer, layertag});
	game.SetAnchor(spritebgSE, 0, 0);

	game.SetScale(spritebgSE, sevol/100.0, 1);
	
	local spritebgSEFrame = game.CreateSprite(SI_TUI_BGMSE_Frame, {xcen, ycen});
	game.AddSpriteChild(spritebgSEFrame, {toplayer, layertag});
	
	local spriteSE = game.CreateSprite(SI_TUI_SE, {xcen-160, ycen});
	game.AddSpriteChild(spriteSE, {toplayer, layertag});
	game.SetColor(spriteSE, global.ARGB(0x7f, 0xffffff));
		
	local touchlayerSE = game.AddTouchLayerChild(
			{toplayer, {x, y, width, height}},
			{toplayer, layertag},
			{0, 0, CCTag_Layer_07, layertag+CCTag_Menu_01}
		);
	
end

function _TitleScene_AddOptionItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_05;
	
	local spOptionTitle = game.CreateSprite(SI_TUI_Option_Title, {340, 460});
	game.AddSpriteChild(spOptionTitle, {toplayer, layertag});
	
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
		
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, blinktimepre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction = game.ActionSpawn({menumoveaction, menualphaaction});

		game.RunAction(menus[i+1], menuaction);
		
	end
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTag_Menu_01, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
		
end

function _TitleScene_AddOptionOKCancelItems(toplayer, toptag)
	
	local layertag = toptag + CCTag_Layer_05;
		
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
		
		local blinktimepre = 0.5;
		local blinktimepost = 0.9;
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, blinktimepre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, blinktimepost);
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

function _TitleScene_EnterOKCancelOptionLayer(toplayer, toptag)
	_TitleScene_AddOptionOKCancelItems(toplayer, toptag);
end

function _TitleScene_LeaveOKCancelOptionLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_05;
	local grouptag = layertag + CCTag_Menu_04;
	game.RemoveChild({toplayer, grouptag});
end



function _TitleScene_EnterOptionLayer(toplayer, toptag)
	_TitleScene_AddOptionItems(toplayer, toptag);
	_TitleScene_AddOptionTouchLayer(toplayer, toptag);
end

function _TitleScene_LeaveOptionLayer(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_05;
	game.RemoveAllChildren({toplayer, layertag});
	layertag = toptag + CCTag_Layer_06;
	game.RemoveAllChildren({toplayer, layertag});
	layertag = toptag + CCTag_Layer_07;
	game.RemoveAllChildren({toplayer, layertag});
	game.SaveIni()
end

