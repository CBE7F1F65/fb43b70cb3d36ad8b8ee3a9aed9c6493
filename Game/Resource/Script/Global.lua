LGlobal_MessageBoxCount	=	{}

_DEBUG_LGlobal_Jump	=	-1;
_DEBUG_MatchAndLog	=	0;

_DEBUG_ReplayCount = 0;

function LGlobal_CallMessageBoxOnce(content, title, indi)
	if indi == nil then
		indi = 1;
	end
	if LGlobal_MessageBoxCount[indi] == nil then
		LGlobal_MessageBoxCount[indi] = 0;
	end
	if LGlobal_MessageBoxCount[indi] > 0 then
		return 0;
	end
	LGlobal_MessageBoxCount[indi] = LGlobal_MessageBoxCount[indi] + 1;
	return LGlobal_CallMessageBox(content, title);
end

function LGlobal_TranslateStringType(str)
	if str == nil then
		str = "nil";
	elseif str == true then
		str = "true";
	elseif str == false then
		str = "false";
	end
	return str;
end

function LGlobal_CallMessageBox(content, title)
	content = LGlobal_TranslateStringType(content);
	title = LGlobal_TranslateStringType(title);
	return global.MessageBox(content, title);
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	global.SystemLog;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;

function Debug_AddReloadMenu(toplayer, toptag)
	local layertag = toptag + CCTag_Layer_14;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCTag_Layer_14, layertag});
	
	local menu = game.CreateMenuItem({toplayer, layertag}, {100, 380, CCTag_Debug_ReloadMenu, layertag+CCTag_Debug_ReloadMenu+1}, "Reload", LConst_FontSize);
	game.AddMenuChild({menu}, {toplayer, layertag}, {0, 0, CCTag_Debug_ReloadMenu, layertag+CCTag_Debug_ReloadMenu});
end

function Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag)
	if selitemtag == 1 then
		game.ReplaceScene(ktag_LoadingSceneLayer);
	end
end

g_SceneTransTime = 0.2