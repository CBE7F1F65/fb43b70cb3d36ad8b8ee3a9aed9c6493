#include "Export_Lua_Game.h"
#include "../Header/GameMain.h"
#include "../Header/DataStruct.h"
#include "../Header/BResource.h"
#include "../Header/BIOInterface.h"
#include "../Header/BGlobal.h"

bool Export_Lua_Game::_LuaRegistFunction_Mission(LuaObject * obj)
{
	obj->Register("GetUsername", LuaFn_Game_GetUsername);
	obj->Register("SetUsername", LuaFn_Game_SetUsername);

	obj->Register("GetBGMSEVol", LuaFn_Game_GetBGMSEVol);
	obj->Register("SetBGMSEVol", LuaFn_Game_SetBGMSEVol);
	obj->Register("SaveIni", LuaFn_Game_SaveIni);
	obj->Register("ResetIni", LuaFn_Game_ResetIni);

	// Data
	obj->Register("GetHiScoreData", LuaFn_Game_GetHiScoreData);
	obj->Register("ResetHiScoreData", LuaFn_Game_ResetHiScoreData);

	obj->Register("GetTotalScore", LuaFn_Game_GetTotalScore);

	obj->Register("StageIsEnabled", LuaFn_Game_StageIsEnabled);
	obj->Register("MissionIsEnabled", LuaFn_Game_MissionIsEnabled);
	obj->Register("EnableMission", LuaFn_Game_EnableMission);
	obj->Register("TryStage", LuaFn_Game_TryStage);
	obj->Register("TryMission", LuaFn_Game_TryMission);
	obj->Register("GetNowStageMissionTurn", LuaFn_Game_GetNowStageMissionTurn);

	obj->Register("SetEnemyPositionRect", LuaFn_Game_SetEnemyPositionRect);
	obj->Register("GetEnemyPositionRect", LuaFn_Game_GetEnemyPositionRect);

	obj->Register("IsFunctionAccessEnabled", LuaFn_Game_IsFunctionAccessEnabled);
	obj->Register("EnableFunctionAccess", LuaFn_Game_EnableFunctionAccess);

	obj->Register("GetItemData", LuaFn_Game_GetItemData);
	obj->Register("UseItem", LuaFn_Game_UseItem);
	obj->Register("BuyItem", LuaFn_Game_BuyItem);


	obj->Register("Update", LuaFn_Game_Update);

	obj->Register("AddTurn", LuaFn_Game_AddTurn);

	obj->Register("GetMissionInfo", LuaFn_Game_GetMissionInfo);
	obj->Register("GetMissionBGData", LuaFn_Game_GetMissionBGData);
	obj->Register("GetMissionHelpData", LuaFn_Game_GetMissionHelpData);
	obj->Register("GetMissionAimData", LuaFn_Game_GetMissionAimData);

	obj->Register("GetNextAvailableMission", LuaFn_Game_GetNextAvailableMission);

	obj->Register("EnterMission", LuaFn_Game_EnterMission);
	obj->Register("ClearMission", LuaFn_Game_ClearMission);

	obj->Register("GetMissionRateScore", LuaFn_Game_GetMissionRateScore);
	obj->Register("SetMissionRateScore", LuaFn_Game_SetMissionRateScore);

	obj->Register("GetHelpAccessInfo", LuaFn_Game_GetHelpAccessInfo);
	obj->Register("SetHelpIndex", LuaFn_Game_SetHelpIndex);

	obj->Register("SetHPAPSP", LuaFn_Game_SetHPAPSP);
	obj->Register("GetHPAPSP", LuaFn_Game_GetHPAPSP);

	obj->Register("GetWeaponData", LuaFn_Game_GetWeaponData);

	obj->Register("GetEnemyTypeData", LuaFn_Game_GetEnemyTypeData);
	obj->Register("GetEnemyATK", LuaFn_Game_GetEnemyATK);
	obj->Register("GetEnemyDEF", LuaFn_Game_GetEnemyDEF);
	obj->Register("GetEnemyELayerAdvance", LuaFn_Game_GetEnemyELayerAdvance);
	obj->Register("GetEnemyXYScale", LuaFn_Game_GetEnemyXYScale);
	obj->Register("GetEnemyEggIndex", LuaFn_Game_GetEnemyEggIndex);

	obj->Register("EggGet", LuaFn_Game_EggGet);

	obj->Register("AttackEnemy", LuaFn_Game_AttackEnemy);

	obj->Register("GetMissionEnemy", LuaFn_Game_GetMissionEnemy);
	obj->Register("AddEnemy", LuaFn_Game_AddEnemy);
	obj->Register("RemoveEnemy", LuaFn_Game_RemoveEnemy);
	obj->Register("DoRemoveEnemy", LuaFn_Game_DoRemoveEnemy);
	obj->Register("SetActiveEnemyData", LuaFn_Game_SetActiveEnemyData);
	obj->Register("GetActiveEnemyData", LuaFn_Game_GetActiveEnemyData);

	obj->Register("CheckMissionOver", LuaFn_Game_CheckMissionOver);
	obj->Register("DoMissionOver", LuaFn_Game_DoMissionOver);

	obj->Register("GetState", LuaFn_Game_GetState);
	obj->Register("SetState", LuaFn_Game_SetState);

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

int Export_Lua_Game::LuaFn_Game_ResetHiScoreData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain::getInstance()->ResetSurvivalHiScore();
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

int Export_Lua_Game::LuaFn_Game_GetTotalScore(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int totalhiscore = GameMain::getInstance()->gamedata.totalhiscore.hiscore;
	node.PInt(totalhiscore);

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

	// missionindex, stageindex -> benabled, trycount, clearcount

	int _missionindex = node.iNextGet();
	int _stageindex = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_stageindex = node.iGet();
	}
	bool benabled = GameMain::getInstance()->MissionIsEnabled(_missionindex, _stageindex);
	int trycount = GameMain::getInstance()->GetMissionTryCount(_missionindex, _stageindex);
	int clearcount = GameMain::getInstance()->GetMissionClearCount(_missionindex, _stageindex);

	node.PBoolean(benabled);
	node.PInt(trycount);
	node.PInt(clearcount);

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

int Export_Lua_Game::LuaFn_Game_GetNextAvailableMission(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int missionindex, stageindex;
	if (GameMain::getInstance()->GetNextAvailableMission(&missionindex, &stageindex))
	{
		node.PInt(missionindex);
		node.PInt(stageindex);
	}

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

int Export_Lua_Game::LuaFn_Game_SetEnemyPositionRect(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	float _x = node.fNextGet();
	float _y = node.fNextGet();
	float _width = node.fNextGet();
	float _height = node.fNextGet();

	CCRect rect = CCRectMake(_x, _y, _width, _height);
	GameMain::getInstance()->SetEnemyPositionRect(rect);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyPositionRect(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	CCRect rect = GameMain::getInstance()->enemypositionrect;

	node.PFloat(rect.origin.x);
	node.PFloat(rect.origin.y);
	node.PFloat(rect.size.width);
	node.PFloat(rect.size.height);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_IsFunctionAccessEnabled(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index -> benabled

	BYTE _index = node.iNextGet();
	node.PBoolean(GameMain::getInstance()->IsFunctionAccessEnabled(_index));

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_EnableFunctionAccess(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index

	BYTE _index = node.iNextGet();
	GameMain::getInstance()->EnableFunctionAccess(_index);

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

int Export_Lua_Game::LuaFn_Game_GetMissionInfo(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// missionindex -> hiscore, rank, missiontype, place, egg1, egg2, egg3

	int _missionindex = -1;
	node.jNextGet();
	if (node.bhavenext)
	{
		_missionindex = node.iGet();
	}
	GameMain * pgm = GameMain::getInstance();
	int hiscore = pgm->GetMissionHiScore(_missionindex);
	BYTE rank = pgm->GetMissionRank(_missionindex);
	missionData * mitem = pgm->GetMissionData(_missionindex);
	BYTE missiontype = (mitem->missiontype)&M_MISSIONTYPE_TYPEMASK;
	BYTE place = mitem->placement;
	bool egg1, egg2, egg3;
	pgm->GetMissionGoldenEggData(&egg1, &egg2, &egg3, _missionindex);

	node.PInt(hiscore);
	node.PInt(rank);
	node.PInt(missiontype);
	node.PInt(place);
	node.PBoolean(egg1);
	node.PBoolean(egg2);
	node.PBoolean(egg3);

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

int Export_Lua_Game::LuaFn_Game_GetMissionAimData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> missiontype
	// missiontype -> target data

	missionData * item = GameMain::getInstance()->GetMissionData();
	missionAimHelpData * mthitem = GameMain::getInstance()->GetMissionAimHelpData();
	if (!node.argscount)
	{
		BYTE missiontype = item->missiontype;
		node.PInt(missiontype&M_MISSIONTYPE_AIMMASK);
	}
	else
	{
		BYTE _missiontype = node.iNextGet();
		switch (_missiontype&M_MISSIONTYPE_AIMMASK)
		{
		case M_MISSIONTYPE_TARGET:
			for (int i=0; i<M_MISSIONTARGETMAX; i++)
			{
				node.PInt(mthitem->targets[i].enemybasetype);
				node.PInt(mthitem->targets[i].num);
			}
			break;
		case M_MISSIONTYPE_DEFEND:
			node.PInt(mthitem->defend.defendturn);
			break;
		}
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetMissionRateScore(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	GameMain * pgm = GameMain::getInstance();
	float nowscorerate = pgm->nowscorerate;
	int missionscore = pgm->missionscore;
	int missionhiscore = pgm->GetMissionHiScore();
	BYTE rank = pgm->GetMissionRank();

	node.PFloat(nowscorerate);
	node.PInt(missionscore);
	node.PInt(missionhiscore);
	node.PInt(rank);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_SetMissionRateScore(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	float _nowscorerate = node.fNextGet();
	int _score = -1;
	node.jNextGet();
	if (node.bhavenext)
	{
		_score = node.iGet();
	}
	GameMain::getInstance()->SetMissionRateScore(_nowscorerate, _score);

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

int Export_Lua_Game::LuaFn_Game_SetHPAPSP(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	int _hp = -1;
	int _ap = -1;
	int _sp = -1;

	node.jNextGet();
	if (node.bhavenext)
	{
		_hp = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_ap = node.iGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_sp = node.iGet();
			}
		}
	}

	GameMain::getInstance()->SetHPAPSP(_hp, _ap, _sp);

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

int Export_Lua_Game::LuaFn_Game_GetWeaponData(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// weapon -> atk ap para
	int _index = node.iNextGet();
	weaponData * item = &(BResource::getInstance()->weapondata[_index]);

	node.PInt(item->atk);
	node.PInt(item->apcost);
	node.PInt(item->para);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyTypeData(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// type -> siid, sidesiid, sidearrowsiid, elayer

	int _etype = node.iNextGet();

	enemyData * enemyitem = &(BResource::getInstance()->enemydata[_etype]);
	enemyBaseData * item = &(BResource::getInstance()->enemybasedata[enemyitem->type]);
	
	node.PInt(item->siid);
	node.PInt(item->sidesiid);
	node.PInt(item->sidearrowsiid);
	node.PInt(item->elayer);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyATK(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// etype, atkindex -> atk, apatk, hpregainatk
	BYTE _etype = node.iNextGet();
	int _atkindex = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_atkindex = node.iGet();
	}
	enemyData * item = &(BResource::getInstance()->enemydata[_etype]);
	enemyBaseData * baseitem = &(BResource::getInstance()->enemybasedata[item->type]);
	switch (baseitem->attackflag)
	{
	case ENEMYATK_HP:
		node.PInt(item->atk[_atkindex]);
		node.PInt(0);
		node.PInt(0);
		break;
	case ENEMYATK_AP:
		node.PInt(0);
		node.PInt(item->atk[_atkindex]);
		node.PInt(0);
		break;
	case ENEMYATK_HPREGAIN:
		node.PInt(0);
		node.PInt(0);
		node.PInt(item->atk[_atkindex]);
		break;
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyDEF(LuaState * ls)
{
	_ENTERFUNC_LUA(2);

	// etype, atkindex -> Def
	BYTE _etype = node.iNextGet();
	int _defindex = node.iNextGet();
	enemyData * item = &(BResource::getInstance()->enemydata[_etype]);
	node.PInt(item->def[_defindex]);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyELayerAdvance(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// etype -> elayeradvance
	BYTE _etype = node.iNextGet();
	enemyData * enemyitem = &(BResource::getInstance()->enemydata[_etype]);
	enemyBaseData * item = &(BResource::getInstance()->enemybasedata[enemyitem->type]);
	node.PInt(item->elayeradvance);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyXYScale(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index -> x, y, scale
	int _index = node.iNextGet();
	GameMain * pgm = GameMain::getInstance();
	EnemyInGameData * item = pgm->GetEnemyByIndex(_index, ENEMY_INSCENE);
	if (!item)
	{
		break;
	}
	float x, y, scale;
	pgm->GetEnemyXYScale(item, &x, &y, &scale);

	node.PFloat(x);
	node.PFloat(y);
	node.PFloat(scale);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetEnemyEggIndex(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index -> eggindex
	int _index = node.iNextGet();
	GameMain * pgm = GameMain::getInstance();
	EnemyInGameData * item = pgm->GetEnemyByIndex(_index, ENEMY_INSCENE);
	if (!item)
	{
		break;
	}
	node.PInt(item->eggindex);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_EggGet(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// index -> bNew
	int _index = node.iNextGet();
	GameMain * pgm = GameMain::getInstance();
	pgm->EggGet();
	if (_index > 0 && _index <= M_MISSIONGOLDENEGGMAX)
	{
		bool bNew = pgm->GoldenEggGet(_index);
		node.PBoolean(bNew);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AttackEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	// enemyindex, weapontype, x, y, r/ xe, ye, xoffset, yoffset -> hitRate, blowoffsetx, blowoffsety, blowdistance, blowangle
	BYTE _index = node.iNextGet();
	EnemyInGameData * item = GameMain::getInstance()->GetEnemyByIndex(_index, ENEMY_INSCENE);
	if (!item)
	{
		break;
	}
	BResource * pbres = BResource::getInstance();
	BYTE basetype = pbres->GetEnemyBaseType(item->etype);
	enemyBaseData * baseitem = &(pbres->enemybasedata[basetype]);
	if (!baseitem)
	{
		break;
	}
	BYTE _weapontype = node.iNextGet();
	float _x = node.fNextGet();
	float _y = node.fNextGet();
	float _r = 0;
	float _xe = _x;
	float _ye = _y;
	switch (_weapontype)
	{
	case M_WEAPON_LASER:
		node.jNextGet();
		if (node.bhavenext)
		{
			_xe = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_ye = node.fGet();
			}
		}
		break;
	case M_WEAPON_BOMB:
	case M_WEAPON_SNIPER:
		node.jNextGet();
		if (node.bhavenext)
		{
			_r = node.fGet();
		}
		break;
	}

	float _xoffset = 0;
	float _yoffset = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_xoffset = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_yoffset = node.fGet();
		}
	}

	float hitRate = 0;
	float enemyx, enemyy, enemyscale;
	GameMain::getInstance()->GetEnemyXYScale(item, &enemyx, &enemyy, &enemyscale);
	enemyx += _xoffset;
	enemyy += _yoffset;

	switch (_weapontype)
	{
	case M_WEAPON_LASER:
		if (BGlobal::CollisionEllipseLine(
			enemyx+baseitem->headcollision.x*enemyscale, 
			enemyy+baseitem->headcollision.y*enemyscale, 
			baseitem->headcollision.rh*enemyscale, 
			baseitem->headcollision.rv*enemyscale, 
			_x, _y,
			_xe, _ye))
		{
			hitRate = baseitem->headshotscale;
		}
		else if (BGlobal::CollisionEllipseLine(
			enemyx+baseitem->bodycollision.x*enemyscale, 
			enemyy+baseitem->bodycollision.y*enemyscale, 
			baseitem->bodycollision.rh*enemyscale, 
			baseitem->bodycollision.rv*enemyscale, 
			_x, _y,
			_xe, _ye))
		{
			hitRate = 1.0f;
		}
		break;
	case M_WEAPON_BOMB:
	case M_WEAPON_SNIPER:
		if (BGlobal::CollisionEllipseCircle(
			enemyx+baseitem->headcollision.x*enemyscale, 
			enemyy+baseitem->headcollision.y*enemyscale, 
			baseitem->headcollision.rh*enemyscale, 
			baseitem->headcollision.rv*enemyscale, 
			_x, _y,
			_r))
		{
			hitRate = baseitem->headshotscale;
		}
		else if (BGlobal::CollisionEllipseCircle(
			enemyx+baseitem->bodycollision.x*enemyscale, 
			enemyy+baseitem->bodycollision.y*enemyscale, 
			baseitem->bodycollision.rh*enemyscale, 
			baseitem->bodycollision.rv*enemyscale, 
			_x, _y,
			_r))
		{
			hitRate = 1.0f;
		}
		break;
	}

	//
	if (hitRate > 0)
	{
		if (_weapontype != M_WEAPON_SNIPER)
		{
			hitRate = 1.0f;
		}
	}

	node.PFloat(hitRate);

	float blowdistancex = 0;
	float blowdistancey = 0;
	float blowdistance = 0;
	int blowangle = 0;
	if (hitRate && _weapontype == M_WEAPON_BOMB)
	{
		blowdistance = baseitem->blowdistance;
		if (blowdistance)
		{
			float dist = DIST(enemyx, enemyy, _x, _y);
			blowdistance *= (1-dist/(_r+baseitem->boxr*enemyscale))*0.8f+0.2f;
			blowangle = 9000-aMainAngle(_x, _y, enemyx, enemyy);
			blowdistancex = blowdistance*sint(blowangle);
			blowdistancey = blowdistance*cost(blowangle);
		}
	}
	node.PFloat(blowdistancex);
	node.PFloat(blowdistancey);
	node.PFloat(blowdistance);
	node.PInt(blowangle);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetMissionEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// nowmissionoffset -> missionenemyindex, x, y, etype, elayerindex/angle

	int nowturnoffset = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		nowturnoffset = node.iGet();
	}

	float x;
	float y;
	int etype;
	int elayerangle;
	BYTE flag;
	int missionenemyindex = GameMain::getInstance()->GetMissionEnemy(&x, &y, &etype, &elayerangle, &flag, nowturnoffset);

	BYTE eggindex = 0;
	switch (flag)
	{
	case M_GOLDENEGGFLAG_01:
		eggindex = 1;
		break;
	case M_GOLDENEGGFLAG_02:
		eggindex = 2;
		break;
	case M_GOLDENEGGFLAG_03:
		eggindex = 3;
		break;
	}
	if (missionenemyindex >= 0)
	{
		node.PInt(missionenemyindex);
		node.PFloat(x);
		node.PFloat(y);
		node.PInt(etype);
		node.PInt(elayerangle);
		node.PInt(eggindex);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(6);

	// itemtag, etype, elayer, eggindex, enemiesindex, angle -> count

	int _itemtag = node.iNextGet();
	float _x = node.fNextGet();
	float _y = node.fNextGet();
	BYTE _etype = node.iNextGet();
	int _elayer = node.iNextGet();
	BYTE _eggindex = node.iNextGet();
	BYTE _enemiesindex = ENEMY_ONSIDE;
	int _angle = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_enemiesindex = node.iGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_angle = node.iGet();
		}
	}

	int enemycount = GameMain::getInstance()->AddEnemy(_itemtag, _x, _y, _etype, _elayer, _eggindex, _enemiesindex, _angle);
	node.PInt(enemycount-1);

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

int Export_Lua_Game::LuaFn_Game_SetActiveEnemyData(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	int _index = node.iNextGet();
	BYTE _enemiesindex = node.iNextGet();
	int _life = node.fNextGet();
	int _elayer = node.iNextGet();
	EnemyInGameData * item = GameMain::getInstance()->GetEnemyByIndex(_index, _enemiesindex);

	float _xoffset = 0;
	float _yoffset = 0;
	BYTE _statusset = 0;
	node.jNextGet();
	if (node.bhavenext)
	{
		_xoffset = node.fGet();
		node.jNextGet();
		if (node.bhavenext)
		{
			_yoffset = node.fGet();
			node.jNextGet();
			if (node.bhavenext)
			{
				_statusset = node.iGet();
			}
		}
	}

	item->life = _life;
	item->elayer = _elayer;
	GameMain::getInstance()->SetEnemyPosition(item, item->x + _xoffset, item->y + _yoffset);
	if ((_statusset&ENEMYSTATUS_SETMASK) == ENEMYSTATUS_CLEAR)
	{
		BYTE statustoclear = _statusset&(~ENEMYSTATUS_SETMASK);
		item->status &= ~statustoclear;
	}
	else
	{
		item->status |= _statusset;
		_statusset = _statusset;
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetActiveEnemyData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> inscenecount, onsidecount
	// index, enemiesindex -> itemtag, x, y, etype, life, elayer, status

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
		float x = item->x;
		float y = item->y;
		BYTE etype = item->etype;
		int life = item->life;
		int elayer = item->elayer;
		int angle = item->angle;
		BYTE status = item->status;
		BYTE eggindex = item->eggindex;

		node.PInt(itemtag);
		node.PFloat(x);
		node.PFloat(y);
		node.PInt(etype);
		node.PInt(life);
		node.PInt(elayer);
		node.PInt(angle);
		node.PInt(status);
		node.PInt(eggindex);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_CheckMissionOver(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// bCheckAP -> missionstate

	bool _bCheckAP = false;
	node.jNextGet();
	if (node.bhavenext)
	{
		_bCheckAP = node.bGet();
	}

	GameMain * pgm = GameMain::getInstance();
	BYTE missionstate = pgm->CheckMissionOver(_bCheckAP);
	node.PInt(missionstate);

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_DoMissionOver(LuaState * ls)
{
	_ENTERFUNC_LUA(1);

	// missionstate -> hiscore, rank, btop

	BYTE missionstate = node.iNextGet();
	GameMain * pgm = GameMain::getInstance();

	bool btop = false;
	switch (missionstate)
	{
	case M_MISSIONSTATE_PROGRESSING:
		break;
	case M_MISSIONSTATE_CLEAR:
		btop = pgm->ClearMission();
		break;
	case M_MISSIONSTATE_FAILED:
		break;
	}

	int hiscore = pgm->GetMissionHiScore();
	BYTE scorerank = pgm->GetMissionRankByScore();
	BYTE rank = pgm->GetMissionRank();

	node.PInt(hiscore);
	node.PInt(scorerank);
	node.PInt(rank);
	node.PBoolean(btop);

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
