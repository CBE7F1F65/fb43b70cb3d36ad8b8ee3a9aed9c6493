function PS_AddBGItems(toplayer, toptag)
	
	local layertag = toptag+CCSTL_BG;
	
	local bgsiid = game.GetMissionBGData();
	local spBG = game.CreateSprite(bgsiid, {480, 336});
	local bgitem = game.AddSpriteChild(spBG, {toplayer, layertag});
	game.SetColor(bgitem, global.ARGB(0xff, 0xAFAFAF));
		
end

function PS_AddFrameItems(toplayer, toptag)
	local layertag = toptag+CCPSTL_Frame;
	
	local spTopPanel = game.CreateSprite(SI_GUI_TopPanel, {480, 608});
	game.AddSpriteChild(spTopPanel, {toplayer, layertag});
	local spBottomPanel = game.CreateSprite(SI_GUI_BottomPanel, {480, 48});
	game.AddSpriteChild(spBottomPanel, {toplayer, layertag});
	local spLeftPanel = game.CreateSprite(SI_GUI_LeftPanel, {32, 368});
	game.AddSpriteChild(spLeftPanel, {toplayer, layertag});
	local spRightPanel = game.CreateSprite(SI_GUI_RightPanel, {928, 368});
	game.AddSpriteChild(spRightPanel, {toplayer, layertag});
end

function PS_AddPlanningRenderTexture(toplayer, toptag)
	local layertag = toptag+CCPSTL_Plan;
	local grouptag = layertag+CCPSTM_Plan_RenderTexture;
	
	for i=1, LConst_PlanGroupMax do
		game.AddRenderTextureChild(960, 640, {toplayer, grouptag}, {480, 320, CCPSTM_Plan_RenderTexture, grouptag+i});
	end
end

function PS_AddHPAPSPItems(toplayer, toptag)
	
	local layertag = toptag + CCPSTL_HPAPSP;
	local grouptag = layertag + CCPSTM_HPAPSP_HPAP;
	
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_HPAPSP_HPAP, grouptag});
	
	local x = 232.5;
	local y = 112;
	
	for i=0, 1 do
		if i == 1 then
			x = 960 - x;
		end
		local texx, texy, width, height = game.GetSIData(SI_GUI_HP_Bar+i*2);
		
		local spBar = game.CreateSprite(SI_GUI_HP_Bar+i*2, {x-width/2, y-height/2}, grouptag+i+1);
		local nodebar = game.AddSpriteChild(spBar, {toplayer, grouptag});
		game.SetAnchor(nodebar, 0, 0);
		game.SetScale(nodebar, 0, 1);
		
		local spFrame = game.CreateSprite(SI_GUI_HP_Frame+i*2, {x, y});
		game.AddSpriteChild(spFrame, {toplayer, grouptag});
		
		local spTitle = game.CreateSprite(SI_GUI_HP+i, {x, y});
		game.AddSpriteChild(spTitle, {toplayer, grouptag});
	end
	
	grouptag = layertag + CCPSTM_HPAPSP_SP;
	game.AddNullChild({toplayer, layertag}, {0, 0, CCPSTM_HPAPSP_SP, grouptag});
	local xorig = 432;
	for i=0, 3 do
		x = xorig + i*32;
		
		local spSP = game.CreateSprite(SI_GUI_SP, {x, y}, grouptag+i+1);
		local nodesp = game.AddSpriteChild(spSP, {toplayer, grouptag});
		game.SetColor(nodesp, global.ARGB(0, 0xffffff));
		
	end
		
end

function PS_AddMainItems(toplayer, toptag)
	
	local xbegin = 168;
	local xoffset = 208;
	local yorig = -48;
	local y = 48;
		
	local spMenus = {};
	local spSelectedMenus = {};
	local spDisabledMenus = {};
	local menus = {};
	local layertag = toptag + CCPSTL_Menu;
	local grouptag = layertag + CCPSTM_Menu_Main;
	
	for i=0, 3 do
		local x = xbegin + i*xoffset;
		
		spMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command+i*3);
		spSelectedMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command_Down+i*3);
		spDisabledMenus[i+1] = game.CreateSprite(SI_GUIMenu_Command_Disabled+i*3);

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {x, yorig, CCPSTM_Menu_Main, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1], spDisabledMenus[i+1]);

		local fadetime = 0.3+i*0.03;
		local menumoveaction = game.ActionMove(CCAF_To, x, y, fadetime);
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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCPSTM_Menu_Main, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
	PS_SetMenuEnable(toplayer, toptag, false);
end

function PS_AddTouchLayer(toplayer, toptag)
		
	local layertag = toptag + CCPSTL_Touch;
	local grouptag = layertag + CCPSTM_Touch_Layer;
	
	local touchlayer = game.AddTouchLayerChild(
			{toplayer, {0, 0, 0, 0}},
			{toplayer, layertag},
			{0, 0, CCPSTL_Touch, grouptag}
		);
	local x, y, width, height = PS_SetTouchLayerRect(toplayer, toptag);
	game.SetEnemyPositionRect(x, y, width, height);
	
end