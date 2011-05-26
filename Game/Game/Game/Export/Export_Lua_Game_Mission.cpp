#include "Export_Lua_Game.h"
#include "../Header/GameMain.h"
#include "../Header/DataStruct.h"

bool Export_Lua_Game::_LuaRegistFunction_Mission(LuaObject * obj)
{
	obj->Register("GetUsername", LuaFn_Game_GetUsername);
	obj->Register("SetUsername", LuaFn_Game_SetUsername);

	// Data
	obj->Register("GetHiScoreData", LuaFn_Game_GetHiScoreData);
	obj->Register("InsertHiScore", LuaFn_Game_InsertHiScore);
	obj->Register("ResetHiScoreData", LuaFn_Game_ResetHiScoreData);

	obj->Register("StageIsEnabled", LuaFn_Game_StageIsEnabled);
	obj->Register("MissionIsEnabled", LuaFn_Game_MissionIsEnabled);
	obj->Register("EnableMission", LuaFn_Game_EnableMission);
	obj->Register("TryStage", LuaFn_Game_TryStage);
	obj->Register("TryMission", LuaFn_Game_TryMission);
	obj->Register("ClearMission", LuaFn_Game_ClearMission);
	obj->Register("GetNowStageMission", LuaFn_Game_GetNowStageMission);

	obj->Register("GetMissionBGData", LuaFn_Game_GetMissionBGData);
	obj->Register("GetMissionHelpData", LuaFn_Game_GetMissionHelpData);

	obj->Register("GetHelpAccessInfo", LuaFn_Game_GetHelpAccessInfo);
	obj->Register("SetHelpIndex", LuaFn_Game_SetHelpIndex);

	obj->Register("GetBGMSEVol", LuaFn_Game_GetBGMSEVol);
	obj->Register("SetBGMSEVol", LuaFn_Game_SetBGMSEVol);
	obj->Register("SaveIni", LuaFn_Game_SaveIni);
	obj->Register("ResetIni", LuaFn_Game_ResetIni);

	return true;
}

int Export_Lua_Game::LuaFn_Game_GetUsername(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> username, inputmax
	node.PString(GameMain::getInstance()->username);
	node.PInt(M_USERNAMEMAX-1);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetUsername(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// username
	GameMain::getInstance()->SetUsername(node.sNextGet());

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetHiScoreData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> count
	if (!node.argscount)
	{
		node.PInt(M_HISCOREMAX);
	}
	// i -> username, hiscore
	else
	{
		int _index = node.iNextGet();
		node.PString(GameMain::getInstance()->GetHiScoreUsername(_index));
		node.PInt(GameMain::getInstance()->GetHiScore(_index));
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_InsertHiScore(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// hiscore
	int _hiscore = node.iNextGet();
	bool retval = GameMain::getInstance()->InsertScore(_hiscore);

	node.PBoolean(retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ResetHiScoreData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain::getInstance()->ResetHiScore();
	bool _bsave = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bsave = node.bGet();
	}
	if (_bsave)
	{
		GameMain::getInstance()->SaveData();
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_StageIsEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _index = node.iNextGet();
	bool bret = GameMain::getInstance()->StageIsEnabled(_index);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_MissionIsEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _missionindex = node.iNextGet();
	int _stageindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_stageindex = node.iGet();
	}
	bool benabled = GameMain::getInstance()->MissionIsEnabled(_missionindex, _stageindex);
	int trycount = GameMain::getInstance()->GetMissionTryCount(_missionindex, _stageindex);

	node.PBoolean(benabled);
	node.PInt(trycount);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_EnableMission(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _missionindex = node.iNextGet();
	int _stageindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_stageindex = node.iGet();
	}
	bool bret = GameMain::getInstance()->EnableMission(_missionindex, _stageindex);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_TryStage(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _index = node.iNextGet();
	bool bret = GameMain::getInstance()->TryStage(_index);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_TryMission(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _missionindex = node.iNextGet();
	int _stageindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_stageindex = node.iGet();
	}
	bool bret = GameMain::getInstance()->TryMission(_missionindex, _stageindex);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ClearMission(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int _missionindex = node.iNextGet();
	int _stageindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_stageindex = node.iGet();
	}
	bool bret = GameMain::getInstance()->ClearMission(_missionindex, _stageindex);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetNowStageMission(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int stageindex = GameMain::getInstance()->nowstage;
	int missionindex = GameMain::getInstance()->nowmission;

	node.PInt(stageindex);
	node.PInt(missionindex);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetMissionBGData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int retval = GameMain::getInstance()->GetMissionBGSIID();
	node.PInt(retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetMissionHelpData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	BYTE helptype[M_MISSIONHELPMAX];
	BYTE helpindex[M_MISSIONHELPMAX];

	GameMain::getInstance()->GetMissionHelpData(helptype, helpindex);

	for (int i=0; i<M_MISSIONHELPMAX; i++)
	{
		node.PInt(helptype[i]);
		node.PInt(helpindex[i]);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetHelpAccessInfo(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> helptype, helpindex
	// helptype, helpindex -> benabled

	BYTE _helptype = GameMain::getInstance()->helptype;
	int _helpindex = GameMain::getInstance()->helpindex;

	node.jNextGet();
	if (node.bhavenext)
	{
		_helptype = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_helpindex = node.iGet();
		}

		bool retval = GameMain::getInstance()->HelpIsEnabled(_helptype, _helpindex);
		node.PBoolean(retval);
	}
	else
	{
		node.PInt(_helptype);
		node.PInt(_helpindex);
	}


	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetHelpIndex(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	BYTE _helptype = node.iNextGet();
	BYTE _helpindex = 0;
	bool _benable = true;

	node.jNextGet();
	if (node.bhavenext)
	{
		_helpindex = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_benable = node.bGet();
		}
	}

	GameMain::getInstance()->SetHelpIndex(_helptype, _helpindex);
	if (_benable)
	{
		GameMain::getInstance()->EnableHelp(_helptype, _helpindex);
	}


	_LEAVEFUNC_LUA;
}


int Export_Lua_Game::LuaFn_Game_GetBGMSEVol(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	node.PInt(GameMain::getInstance()->bgmvol);
	node.PInt(GameMain::getInstance()->sevol);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetBGMSEVol(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _bgmvol = -1;
	int _sevol = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_bgmvol = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_sevol = node.iGet();
		}
	}

	GameMain::getInstance()->SetBGMVol(_bgmvol);
	GameMain::getInstance()->SetSEVol(_sevol);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SaveIni(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain::getInstance()->SaveIni();

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ResetIni(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	bool _bresetname = false;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bresetname = node.bGet();
	}
	GameMain::getInstance()->ResetIni(_bresetname);
	bool _bsave = true;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bsave = node.bGet();
	}
	if (_bsave)
	{
		GameMain::getInstance()->SaveIni();
	}

	_LEAVEFUNC_LUA;
}