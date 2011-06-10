LGlobal_MessageBoxCount	=	{};

LGlobal_LogLineCount = 0;
LGlobal_LogLineCountMax = 30;
LGlobal_LogLineHeight = 18;

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

function LGlobal_CallMessageBox(content, title)
	content = tostring(content);
	title = tostring(title);
	return global.MessageBox(content, title);
end


function Debug_LogMoveup(toplayer, layertag)
	for i=1, LGlobal_LogLineCountMax do
		local item = game.GetNode({toplayer, layertag, i});
		if item ~= global.ARGB(0, 0) then
			local posindex = LGlobal_LogLineCount+1-i;
			if posindex > LGlobal_LogLineCountMax then
				posindex = posindex - LGlobal_LogLineCountMax;
			elseif posindex < 1 then
				posindex = posindex + LGlobal_LogLineCountMax;
			end
			game.SetPosition(item, 0, (posindex)*LGlobal_LogLineHeight);
		end
	end
			
	if LGlobal_LogLineCount < LGlobal_LogLineCountMax then
		LGlobal_LogLineCount = LGlobal_LogLineCount+1;
	else
		LGlobal_LogLineCount = 1;
	end
	
	local item = game.GetNode({toplayer, layertag, LGlobal_LogLineCount})
	if item ~= global.ARGB(0, 0) then
		game.RemoveChild(item);
	end
end

function Debug_Log(str, toplayer, toptag)
	global.SystemLog(str);
	if toplayer ~= nil and toptag ~= nil then
		local layertag = toptag + CCSTL_Debug;
		
		Debug_LogMoveup(toplayer, layertag);
		local item = game.AddTextChild({toplayer, layertag}, {0, LGlobal_LogLineHeight, 0, LGlobal_LogLineCount}, str, LConst_FontSize*0.5);
		if item ~= nil then
			game.SetAnchor(item, 0, 0)
		end
	end
end

function Debug_LogState(str, stateST, stateAction, stateStep, toplayer, toptag)
	str = str.."	State:";
	str = str.."	ST:	";
	if stateST == STATE_ST_Null then
		str = str.."Null";
	elseif stateST == STATE_ST_Standby then
		str = str.."Standby";
	elseif stateST == STATE_ST_Progressing then
		str = str.."Progressing";
	elseif stateST == STATE_ST_StepForward then
		str = str.."StepForward";
	elseif stateST == STATE_ST_Error then
		str = str.."Error";
	elseif stateST == STATE_ST_Finished then
		str = str.."Finished";
	else
		str = str.."??";
	end
	str = str.."	Action:	";
	if stateAction == STATE_Waiting then
		str = str.."Waiting";
	elseif stateAction == STATE_ShowHelp then
		str = str.."ShowHelp";
	elseif stateAction == STATE_ShowTarget then
		str = str.."ShowTarget";
	elseif stateAction == STATE_EnemyEnter then
		str = str.."EnemyEnter";
	elseif stateAction == STATE_AddEnemy then
		str = str.."AddEnemy";
	elseif stateAction == STATE_HPAPRegain then
		str = str.."HPAPRegain";
	elseif stateAction == STATE_ShowTurnStart then
		str = str.."ShowTurnStart";
	elseif stateAction == STATE_Planning then
		str = str.."Planning";
	elseif stateAction == STATE_SelfAction then
		str = str.."SelfAction";
	elseif stateAction == STATE_EnemyAction then
		str = str.."EnemyAction";
	elseif stateAction == STATE_Over then
		str = str.."Over";
	else
		str = str.."??";
	end
	str = str.."	Step:	"..stateStep;
	Debug_Log(str, toplayer, toptag);
end

MB	=	LGlobal_CallMessageBoxOnce;
MBA	=	LGlobal_CallMessageBox;
LOG	=	Debug_Log;
LOGSTATE = Debug_LogState;

DtoI = luastate.DWORDToInt;
ItoD = luastate.IntToDWORD;

RANDT	=	game.Random_Int;
RANDTF	=	game.Random_Float;

function Debug_AddReloadMenu(toplayer, toptag)
	local layertag = toptag + CCSTL_Debug;
	game.AddNullChild({toplayer, toptag}, {0, 0, CCSTL_Debug, layertag});
	
	local menu = game.CreateMenuItem({toplayer, layertag}, {100, 380, CCTag_Debug_ReloadMenu, layertag+CCTag_Debug_ReloadMenu+1}, "Reload", LConst_FontSize);
	game.AddMenuChild({menu}, {toplayer, layertag}, {0, 0, CCTag_Debug_ReloadMenu, layertag+CCTag_Debug_ReloadMenu});
end

function Debug_AddReloadMenu_Callback(selitemtag, toplayer, toptag)
	if selitemtag == 1 then
		game.ReplaceScene(ktag_LoadingSceneLayer);
	end
end

LGlobal_Data = {};
LGlobal_Data_EmptyIndex = {};

function LGlobal_SaveData(data)
	
	local dataindex = -1;
	local emptycount = table.getn(LGlobal_Data_EmptyIndex);
	if emptycount > 0 then
		dataindex = LGlobal_Data_EmptyIndex[emptycount];
		LGlobal_Data_EmptyIndex[emptycount] = nil;
	end
	
	if dataindex < 0 then
		local datacount = table.getn(LGlobal_Data);
		dataindex = datacount+1;
	end
	
	LGlobal_Data[dataindex] = data;
	return dataindex;
	
end

function LGlobal_GetData(dataindex, bremove)
	if bremove == nil then
		bremove = true;
	end	
	local item = LGlobal_Data[dataindex];
	if bremove then
		if dataindex ~= table.getn(LGlobal_Data) then
			local emptycount = table.getn(LGlobal_Data_EmptyIndex);
			LGlobal_Data_EmptyIndex[emptycount] = dataindex;
		end
		LGlobal_Data[dataindex] = nil;
	end
	return item;
end