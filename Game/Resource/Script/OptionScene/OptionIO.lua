

function _TitleScene_AddOptionTouchLayer(toplayer, toptag)
	
	local xcen = 780;
	local ycen = 550;
	
	local texx, texy, width, height = game.GetSIData(SI_TUI_BGMSE_Bar);
	local bgmvol, sevol = game.GetBGMSEVol();
	
	local x = xcen - width / 2;
	local y = ycen - height / 2;
	local layertag = toptag + CCTSTL_BGMTouch;
	
	--BGM
	local spritebgBGM = game.CreateSprite(SI_TUI_BGMSE_Bar, {x, y}, layertag+CCTSTM_BGMTouch_Bar);
	game.AddSpriteChild(spritebgBGM, {toplayer, layertag});
	game.SetAnchor(spritebgBGM, 0, 0);
	
	local spritebgBGMFrame = game.CreateSprite(SI_TUI_BGMSE_Frame, {xcen, ycen});
	game.AddSpriteChild(spritebgBGMFrame, {toplayer, layertag});
	
	local spriteBGM = game.CreateSprite(SI_TUI_BGM, {xcen-160, ycen});
	game.AddSpriteChild(spriteBGM, {toplayer, layertag});
	game.SetColor(spriteBGM, global.ARGB(0x7f, 0xffffff));
		
	local touchlayerBGM = game.AddTouchLayerChild(
			{toplayer, {x, y, width, height}},
			{toplayer, layertag},
			{0, 0, CCTSTL_BGMTouch, layertag+CCTSTM_BGMTouch_Bar}
		);
	
	--SE
	layertag = toptag + CCTSTL_SETouch;
	ycen = ycen - 80;
	y = ycen - height / 2;
	local spritebgSE = game.CreateSprite(SI_TUI_BGMSE_Bar, {x, y}, layertag+CCTSTM_SETouch_Bar);
	game.AddSpriteChild(spritebgSE, {toplayer, layertag});
	game.SetAnchor(spritebgSE, 0, 0);
	
	local spritebgSEFrame = game.CreateSprite(SI_TUI_BGMSE_Frame, {xcen, ycen});
	game.AddSpriteChild(spritebgSEFrame, {toplayer, layertag});
	
	local spriteSE = game.CreateSprite(SI_TUI_SE, {xcen-160, ycen});
	game.AddSpriteChild(spriteSE, {toplayer, layertag});
	game.SetColor(spriteSE, global.ARGB(0x7f, 0xffffff));
		
	local touchlayerSE = game.AddTouchLayerChild(
			{toplayer, {x, y, width, height}},
			{toplayer, layertag},
			{0, 0, CCTSTL_SETouch, layertag+CCTSTM_SETouch_Bar}
		);
	_TitleScene_UpdateBGMSE(toplayer, toptag)
end

function _TitleScene_AddOptionItems(toplayer, toptag)
	
	local layertag = toptag + CCTSTL_Option;
	
	local spOptionTitle = game.CreateSprite(SI_TUI_Option_Title, {340, 460});
	game.AddSpriteChild(spOptionTitle, {toplayer, layertag});
	
	local xorig = 1224;
	local xcen = 824;
	local ybegin = 260;
	local yoffset = 160;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTSTM_Option_Menu;
	for i=0, 1 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_Reset+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Reset_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTSTM_Option_Menu, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTSTM_Option_Menu, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
		
end

function _TitleScene_AddOptionOKCancelItems(toplayer, toptag)
	
	local layertag = toptag + CCTSTL_Option;
		
	local xorig = 824;
	local xcen = 664;
	local ybegin = 340;
	local yoffset = 160;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTSTM_Option_OKCancel;
	
	for i=0, 1 do
		local y = ybegin - i*yoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_TUI_OK+i*2);
		spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_OK_Down+i*2);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTSTM_Option_OKCancel, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

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
	
	menus[3] = GlobalScene_CreateCancelMenu({toplayer, layertag}, CCTSTM_Option_OKCancel, grouptag+3);
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTSTM_Option_OKCancel, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
end

function _TitleScene_EnterOKCancelOptionLayer(toplayer, toptag)
	_TitleScene_AddOptionOKCancelItems(toplayer, toptag);
end

function _TitleScene_LeaveOKCancelOptionLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Option;
	local grouptag = layertag + CCTSTM_Option_OKCancel;
	game.RemoveChild({toplayer, grouptag});
end



function _TitleScene_EnterOptionLayer(toplayer, toptag)
	_TitleScene_AddOptionItems(toplayer, toptag);
	_TitleScene_AddOptionTouchLayer(toplayer, toptag);
end

function _TitleScene_LeaveOptionLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Option;
	game.RemoveAllChildren({toplayer, layertag});
	layertag = toptag + CCTSTL_BGMTouch;
	game.RemoveAllChildren({toplayer, layertag});
	layertag = toptag + CCTSTL_SETouch;
	game.RemoveAllChildren({toplayer, layertag});
	game.SaveIni()
end

