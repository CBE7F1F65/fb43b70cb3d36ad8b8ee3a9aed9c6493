#include "Export_Lua_Game.h"
#include "../Header/GameMain.h"
#include "../Header/DataStruct.h"
#include "../Header/BResource.h"

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
	obj->Register("GetNowStageMissionTurn", LuaFn_Game_GetNowStageMissionTurn);

	obj->Register("GetItemData", LuaFn_Game_GetItemData);
	obj->Register("UseItem", LuaFn_Game_UseItem);
	obj->Register("BuyItem", LuaFn_Game_BuyItem);


	obj->Register("Update", LuaFn_Game_Update);

	obj->Register("AddTurn", LuaFn_Game_AddTurn);

	obj->Register("GetMissionBGData", LuaFn_Game_GetMissionBGData);
	obj->Register("GetMissionHelpData", LuaFn_Game_GetMissionHelpData);

	obj->Register("EnterMission", LuaFn_Game_EnterMission);
	obj->Register("ClearMission", LuaFn_Game_ClearMission);

	obj->Register("GetHelpAccessInfo", LuaFn_Game_GetHelpAccessInfo);
	obj->Register("SetHelpIndex", LuaFn_Game_SetHelpIndex);

	obj->Register("GetHPAPSP", LuaFn_Game_GetHPAPSP);

	obj->Register("GetEnemyTypeData", LuaFn_Game_GetEnemyTypeData);
	obj->Register("GetEnemyATK", LuaFn_Game_GetEnemyATK);
	obj->Register("GetEnemyELayerAdvance", LuaFn_Game_GetEnemyELayerAdvance);

	obj->Register("AddEnemy", LuaFn_Game_AddEnemy);
	obj->Register("RemoveEnemy", LuaFn_Game_RemoveEnemy);
	obj->Register("DoRemoveEnemy", LuaFn_Game_DoRemoveEnemy);
	obj->Register("GetActiveEnemyData", LuaFn_Game_GetActiveEnemyData);

	obj->Register("GetState", LuaFn_Game_GetState);
	obj->Register("SetState", LuaFn_Game_SetState);

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

int Export_Lua_Game::LuaFn_Game_EnterMission(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain::getInstance()->EnterMission();

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_ClearMission(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	bool bret = GameMain::getInstance()->ClearMission();

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetNowStageMissionTurn(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int stageindex = GameMain::getInstance()->nowstage;
	int missionindex = GameMain::getInstance()->nowmission;
	int nowturn = GameMain::getInstance()->nowturn;

	node.PInt(stageindex);
	node.PInt(missionindex);
	node.PInt(nowturn);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetItemData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> itemtypecount
	// index -> siid, itemcount

	node.jNextGet();
	if (node.bhavenext)
	{
		BYTE _index = node.iGet();
		int siid = 0;
		int itemcount = 0;
		itemcount = GameMain::getInstance()->GetItemData(_index, &siid);
		node.PInt(siid);
		node.PInt(itemcount);
	}
	else
	{
		BYTE itemtypecount = GameMain::getInstance()->itemtypecount;
		node.PInt(itemtypecount);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_UseItem(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	BYTE _index = node.iNextGet();
	bool bret = GameMain::getInstance()->UseItem(_index);

	node.PBoolean(bret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_BuyItem(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	BYTE _index = node.iNextGet();
	int iret = GameMain::getInstance()->BuyItem(_index);

	node.PInt(iret);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_Update(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain::getInstance()->Update();

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddTurn(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	(GameMain::getInstance()->nowturn)++;

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

int Export_Lua_Game::LuaFn_Game_GetHPAPSP(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int nowhp = GameMain::getInstance()->nowhp;
	int nowap = GameMain::getInstance()->nowap;
	int nowsp = GameMain::getInstance()->nowsp;

	node.PInt(nowhp);
	node.PInt(nowap);
	node.PInt(nowsp);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyTypeData(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// type -> siid, sidesiid, life, elayer

	int _etype = node.iNextGet();

	enemyData * item = &(BResource::getInstance()->enemydata[_etype]);
	
	node.PInt(item->siid);
	node.PInt(item->sidesiid);
	node.PInt(item->life);
	node.PInt(item->elayer);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyATK(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// etype, atkindex -> atk
	BYTE _etype = node.iNextGet();
	int _atkindex = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_atkindex = node.iGet();
	}
	enemyData * item = &(BResource::getInstance()->enemydata[_etype]);
	node.PInt(item->atk[_atkindex]);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyELayerAdvance(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// etype -> elayeradvance
	BYTE _etype = node.iNextGet();
	enemyData * item = &(BResource::getInstance()->enemydata[_etype]);
	node.PInt(item->elayeradvance);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	// itemtag, etype, life, elayer, enemiesindex -> count

	int _itemtag = node.iNextGet();
	BYTE _etype = node.iNextGet();
	int _life = node.iNextGet();
	int _elayer = node.iNextGet();
	BYTE _enemiesindex = ENEMY_ONSIDE;
	node.jNextGet();
	if (node.bhavenext)
	{
		_enemiesindex = node.iGet();
	}

	int enemycount = GameMain::getInstance()->AddEnemy(_itemtag, _etype, _life, _elayer, _enemiesindex);
	node.PInt(enemycount);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_RemoveEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index, enemiesindex
	int _index = node.iNextGet();
	BYTE _enemiesindex = ENEMY_ONSIDE;
	node.jNextGet();
	if (node.bhavenext)
	{
		_enemiesindex = node.iGet();
	}

	GameMain::getInstance()->RemoveEnemy(_index, _enemiesindex);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_DoRemoveEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// ememiesindex -> size

	BYTE _enemiesindex = ENEMY_ONSIDE;
	node.jNextGet();
	if (node.bhavenext)
	{
		_enemiesindex = node.iGet();
	}

	int retval = GameMain::getInstance()->DoRemoveEnemy(_enemiesindex);
	node.PInt(retval);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetActiveEnemyData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> inscenecount, onsidecount
	// index, enemiesindex -> itemtag, etype, life, elayer

	if (!node.argscount)
	{
		for (int i=0; i<ENEMY_VECTORTYPEMAX; i++)
		{
			node.PInt(GameMain::getInstance()->enemies[i].size());
		}
	}
	else
	{
		int _index = node.iNextGet();
		BYTE _enemiesindex = ENEMY_ONSIDE;
		node.jNextGet();
		if (node.bhavenext)
		{
			_enemiesindex = node.iGet();
		}

		EnemyInGameData * item = GameMain::getInstance()->GetEnemyByIndex(_index, _enemiesindex);
		int itemtag = item->itemtag;
		BYTE etype = item->etype;
		int life = item->life;
		int elayer = item->elayer;

		node.PInt(itemtag);
		node.PInt(etype);
		node.PInt(life);
		node.PInt(elayer);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetState(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int stateST;
	int stateAction;
	int stateStep;
	GameMain::getInstance()->GetState(&stateST, &stateAction, &stateStep);

	node.PInt(stateST);
	node.PInt(stateAction);
	node.PInt(stateStep);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetState(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	int stateST = node.iNextGet();
	int stateAction = -1;
	int stateStep = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		stateAction = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			stateStep = node.iGet();
		}
	}

	GameMain::getInstance()->SetState(stateST, stateAction, stateStep);

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