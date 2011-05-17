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
	local menu = game.CreateMenuItem({toptag}, {100, 480, 0, toptag+CCTAG_Debug_ReloadItem}, "Reload", 20);
	game.AddMenuChild({menu}, {toptag}, {0, 0, CCZOrder_Debug_Reload, toptag+CCTAG_Debug_ReloadMenu});
end

function Debug_AddReloadMenu_Callback(selitemtag, eventtag, toptag)
	if selitemtag == CCTAG_Debug_ReloadItem-CCTAG_Debug_ReloadMenu then
		game.ReplaceScene(ktag_LoadingSceneLayer);
	end
end
