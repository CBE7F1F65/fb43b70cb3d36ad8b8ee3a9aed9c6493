function MissionSelectScene_IO(eventtype, toplayer, toptag)
	
	if eventtype == SceneIOFlag_OnInit then
		return MissionSelectScene_OnInit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnter then
		return MissionSelectScene_OnEnter(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnEnterTDF then
		return MissionSelectScene_OnEnterTDF(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnExit then
		return MissionSelectScene_OnExit(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchBegin then
		return MissionSelectScene_OnTouchBegin(toplayer, toptag);
	elseif eventtype == SceneIOFlag_OnTouchEnd then
		return MissionSelectScene_OnTouchEnd(toplayer, toptag);
	end
end

function MissionSelectScene_OnInit(toplayer, toptag)
	
	-- bg layer
	layertag = toptag + CCSTL_BG;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCSTL_BG, layertag});
	
	local nowstage = game.GetNowStageMissionTurn();
	local spMissionSelect = game.CreateSprite(SI_World01_Scene+nowstage, {480, 320});
	game.AddSpriteChild(spMissionSelect, {toplayer, layertag});
	
	-- menu layer
	layertag = toptag + CCMSSTL_Menu;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCMSSTL_Menu, layertag});
	
end


function _MissionSelectScene_AddMainItems(toplayer, toptag)
	
	local nowstage = game.GetNowStageMissionTurn();
	
	local missioninfos = {};
	local placemax = {};
	for i=1, 3 do
		placemax[i] = 0;
	end
	local missioncount = LConst_MissionIndex_End;
	if nowstage == LConst_ExtraStageIndex then
		missioncount = LConst_MissionIndex_ExtraStage;
	end
		
	for i=0, missioncount-1 do
		missioninfos[i+1] = {};
		local hiscore, rank, missiontype, place = game.GetMissionInfo(i);
		
		if i > 0 and missioninfos[i].place == place then
			local ycountindex = 0;
			local j = i;
			while j > 0 and missioninfos[j].place == place do

				missioninfos[j].ycount = missioninfos[j].ycount+1;
				j = j-1;
				ycountindex = ycountindex + 1;
			end
			missioninfos[i+1].ycount = ycountindex+1;
			missioninfos[i+1].ycountindex = ycountindex;
		else
			missioninfos[i+1].ycount = 1;
			missioninfos[i+1].ycountindex = 0;
		end
		
		local missionenabled, missiontriedtime, missionclearedtime = game.MissionIsEnabled(i);
		missioninfos[i+1].hiscore, missioninfos[i+1].rank, missioninfos[i+1].missiontype, missioninfos[i+1].place = hiscore, rank, missiontype, place;
		missioninfos[i+1].enabled, missioninfos[i+1].triedtime = missionenabled, missiontriedtime;
		
		local placeindex;
		if i < LConst_MissionIndex_FreeStart then
			placeindex = 1;
		elseif i < LConst_MissionIndex_GoldenEggStart then
			placeindex = 2;
		else
			placeindex = 3;
		end
		if place > placemax[placeindex] then
			placemax[placeindex] = place;
		end
		
		if missiontype == MISSIONTYPE_Movie then
			missioninfos[i+1].spMenu = game.CreateSprite(SI_MSUI_Event);
			missioninfos[i+1].spSelectedMenu = game.CreateSprite(SI_MSUI_Event_Down);
		elseif missiontype == MISSIONTYPE_Boss then
			if missionclearedtime > 0 then
				missioninfos[i+1].spMenu = game.CreateSprite(SI_MSUI_BossMission_Cleared);
			else
				missioninfos[i+1].spMenu = game.CreateSprite(SI_MSUI_BossMission);
			end
			missioninfos[i+1].spSelectedMenu = game.CreateSprite(SI_MSUI_BossMission_Down);
			missioninfos[i+1].spDisabledMenu = game.CreateSprite(SI_MSUI_BossMission_Disabled);
		else
			if missionclearedtime > 0 then
				missioninfos[i+1].spMenu = game.CreateSprite(SI_MSUI_Mission_Cleared);
			else
				missioninfos[i+1].spMenu = game.CreateSprite(SI_MSUI_Mission);
			end
			missioninfos[i+1].spSelectedMenu = game.CreateSprite(SI_MSUI_Mission_Down);
			missioninfos[i+1].spDisabledMenu = game.CreateSprite(SI_MSUI_Mission_Disabled);
		end
		
	end
		
	local xlen = {};
	local xstart = {};
	local yspace = 120;
	local placespace = {};
	
	for i=1, 3 do
		if i == 1 then
			xlen[i] = 800;
		else
			xlen[i] = 600;
		end
		xstart[i] = (960-xlen[i])/2;
		if placemax[i] ~= nil then
			placespace[i] = xlen[i]/(placemax[i]-1);
		end
	end
	
	local layertag = toptag + CCSTL_BG;
	local spriteBG = game.CreateSprite(SI_White, {480, 400, 0, xlen[1]+120, yspace*3+80});
	game.AddSpriteChild(spriteBG, {toplayer, layertag});
	game.SetColor(spriteBG, global.ARGB(0x3f, 0x808080));
	
	local menus = {};
	layertag = toptag + CCMSSTL_Menu;
	local grouptag = layertag + CCMSSTM_Menu_Main;
	
	for i=0, missioncount-1 do
		
		local placeindex, xpageoffset;
		if i < LConst_MissionIndex_FreeStart then
			placeindex = 1;
			xpageoffset = 0;
		elseif i < LConst_MissionIndex_GoldenEggStart then
			placeindex = 2;
			xpageoffset = 960;
		else
			placeindex = 3;
			xpageoffset = 1920;
		end
		
		local x = placespace[placeindex]*(missioninfos[i+1].place-1) + xstart[placeindex] + xpageoffset;
		local y = -(missioninfos[i+1].ycountindex - (missioninfos[i+1].ycount-1)/2) * yspace + 400;
		
		if i==0 and nowstage ~= LConst_ExtraStageIndex then
			x = x+placespace[placeindex];
			y = y+yspace;
		end
		
		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {x-40, y+40, CCMSSTM_Menu_Main, grouptag+i+1}, missioninfos[i+1].spMenu, missioninfos[i+1].spSelectedMenu, missioninfos[i+1].spDisabledMenu);
		if not missioninfos[i+1].enabled then
			game.SetMenuItemEnabled(menus[i+1], false);
		end

		local fadetime = 0.3;
		local menumoveaction = game.ActionMove(CCAF_To, x, y, fadetime);
		menumoveaction = game.ActionEase(CCAF_In, menumoveaction, 0.25);
		
		local menufadeinaction = game.ActionFade(CCAF_In, 0xff, fadetime);
		local menurepeatactionpre = game.ActionFade(CCAF_To, LConst_ButtonFadeTo, LConst_BlinkTimePre);
		local menurepeatactionpost = game.ActionFade(CCAF_To, 0xFF, LConst_BlinkTimePost);
		local menurepeataction = game.ActionSequence({menurepeatactionpre, menurepeatactionpost});
		menurepeataction = game.ActionRepeat(menurepeataction);
		local menualphaaction = game.ActionSequence({menufadeinaction, menurepeataction});
		
		local menuaction;
		if missioninfos[i+1].enabled and missioninfos[i+1].triedtime == 0 then
			local menuscaleinaction = game.ActionScale(CCAF_To, 1.0, 1.0, fadetime);
			local menurepeatscaleactionpre = game.ActionScale(CCAF_To, 1.2, 1.2, LConst_BlinkTimePre/3);
			local menurepeatscaleactionpost = game.ActionScale(CCAF_To, 1.0, 1.0, LConst_BlinkTimePost/3);
			local menurepeatscaleaction = game.ActionSequence({menurepeatscaleactionpre, menurepeatscaleactionpost});
			menurepeatscaleaction = game.ActionRepeat(menurepeatscaleaction);
			local menuscaleaction = game.ActionSequence({menuscaleinaction, menurepeatscaleaction});
			
			menuaction = game.ActionSpawn({menumoveaction, menualphaaction, menuscaleaction})
		else		
			menuaction = game.ActionSpawn({menumoveaction, menualphaaction});
		end

		game.RunAction(menus[i+1], menuaction);
		
	end
	
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCMSSTM_Menu_Main, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
	
end

function _MissionSelectScene_AddPageItems(toplayer, toptag)
	local nowstage = game.GetNowStageMissionTurn();
	if nowstage == LConst_ExtraStageIndex then
		return;
	end
	
	local layertag = toptag + CCMSSTL_Menu;
	local grouptag = layertag + CCMSSTM_Menu_Page;
	
	local xbegin = 280;
	local xoffset = 300;
	local yorig = -48;
	local y = 96;
		
	local spMenus = {};
	local spSelectedMenus = {};
	local menus = {};
	
	for i=0, 2 do
		local x = xbegin + i*xoffset;
		if i == 2 then
			x = 800;
		end
		
		if i ~= 2 then
			spMenus[i+1] = game.CreateSprite(SI_MSUI_Back+i*2);
			spSelectedMenus[i+1] = game.CreateSprite(SI_MSUI_Back_Down+i*2);
		else
			spMenus[i+1] = game.CreateSprite(SI_TUI_Exit);
			spSelectedMenus[i+1] = game.CreateSprite(SI_TUI_Exit_Down);
		end

		menus[i+1] = game.CreateMenuItem({toplayer, layertag}, {x, yorig, CCMSSTM_Menu_Page, grouptag+i+1}, spMenus[i+1], spSelectedMenus[i+1]);

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
	local menu = game.AddMenuChild(menus, {toplayer, layertag}, {0, 0, CCMSSTM_Menu_Page, grouptag});
	game.SetColor(menu, global.ARGB(0, 0xffffff));
end

function _MissionSelectScene_EnterMainLayer(toplayer, toptag)
	LGlobal_MSS_NowPage = 0;
	_MissionSelectScene_AddMainItems(toplayer, toptag);
	_MissionSelectScene_AddPageItems(toplayer, toptag);
end

function _MissionSelectScene_LeaveMainLayer(toplayer, toptag)
	local layertag = toptag + CCMSSTL_Menu;
	game.RemoveAllChildren({toplayer, layertag});
end

function MissionSelectScene_OnEnter(toplayer, toptag)
end

function MissionSelectScene_OnEnterTDF(toplayer, toptag)
	_MissionSelectScene_EnterMainLayer(toplayer, toptag);
end
function MissionSelectScene_OnExit(toplayer, toptag)
end
function MissionSelectScene_OnTouchBegin(toplayer, toptag)
end
function MissionSelectScene_OnTouchEnd(toplayer, toptag)
end