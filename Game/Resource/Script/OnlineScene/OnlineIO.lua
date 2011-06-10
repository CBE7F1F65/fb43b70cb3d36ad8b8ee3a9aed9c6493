
function _TitleScene_AddOnlineItems(toplayer, toptag)
	
	local layertag = toptag + CCTSTL_Online;
	
	local spOnlineTitle = game.CreateSprite(SI_TUI_Online_Title, {340, 460});
	game.AddSpriteChild(spOnlineTitle, {toplayer, layertag});
	
	local xorig = 1224;
	local xcen = 824;
	local ybegin = 420;
	local yoffset = 160;
	
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	local grouptag = layertag + CCTSTM_Online_Menu;
	for i=0, 2 do
		local y = ybegin - i*yoffset;
		local normalsiid = SI_TUI_LeaderBoard + i*2;
		local selectedsiid = SI_TUI_LeaderBoard_Down + i*2;
		if i == 2 then
			normalsiid = SI_TUI_Exit;
			selectedsiid = SI_TUI_Exit_Down;
		end
		
		spMenus[i+1] = game.CreateSprite(normalsiid);
		spSelectedMenus[i+1] = game.CreateSprite(selectedsiid);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {xorig, y, CCTSTM_Online_Menu, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCTSTM_Online_Menu, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
		
end

function _TitleScene_EnterOnlineLayer(toplayer, toptag)
	_TitleScene_AddOnlineItems(toplayer, toptag);
end

function _TitleScene_LeaveOnlineLayer(toplayer, toptag)
	local layertag = toptag + CCTSTL_Online;
	game.RemoveAllChildren({toplayer, layertag});
end
