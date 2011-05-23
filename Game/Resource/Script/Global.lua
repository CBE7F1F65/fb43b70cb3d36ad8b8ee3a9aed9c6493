LGlobal_MessageBoxCount	=	{};

LGlobal_LogLineCount = 0;
LGlobal_LogLineCountMax = 30;
LGlobal_LogLineHeight = 18;
LGlobal_LogLineInfo = {};

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


function Debug_LogMoveup()
	for i=1, LGlobal_LogLineCountMax do
		if LGlobal_LogLineInfo[i] ~= nil then
			local posindex = LGlobal_LogLineCount+1-i;
			if posindex > LGlobal_LogLineCountMax then
				posindex = posindex - LGlobal_LogLineCountMax;
			elseif posindex < 1 then
				posindex = posindex + LGlobal_LogLineCountMax;
			end
			game.SetPosition(LGlobal_LogLineInfo[i], 0, (posindex+1)*LGlobal_LogLineHeight);
		end
	end
			
	if LGlobal_LogLineCount < LGlobal_LogLineCountMax then
		LGlobal_LogLineCount = LGlobal_LogLineCount+1;
	else
		LGlobal_LogLineCount = 1;
	end
	
	if LGlobal_LogLineInfo[LGlobal_LogLineCount] ~= nil then
		game.RemoveChild(LGlobal_LogLineInfo[LGlobal_LogLineCount]);
		LGlobal_LogLineInfo[LGlobal_LogLineCount] = nil;
	end
end

function Debug_Log(str, toplayer, toptag)
	global.SystemLog(str);
	if toplayer ~= nil and toptag ~= nil then
		local layertag = toptag + CCTag_Layer_14;
		
		Debug_LogMoveup();
		LGlobal_LogLineInfo[LGlobal_LogLineCount] = game.AddTextChild({toplayer, layertag}, {0, LGlobal_LogLineHeight}, str, LConst_FontSize*0.5);
		game.SetAnchor(LGlobal_LogLineInfo[LGlobal_LogLineCount], 0, 0)
	end
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	Debug_Log;

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