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
	obj->Register("GetMissionTargetData", LuaFn_Game_GetMissionTargetData);

	obj->Register("EnterMission", LuaFn_Game_EnterMission);
	obj->Register("ClearMission", LuaFn_Game_ClearMission);

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

	obj->Register("AttackEnemy", LuaFn_Game_AttackEnemy);

	obj->Register("AddEnemy", LuaFn_Game_AddEnemy);
	obj->Register("RemoveEnemy", LuaFn_Game_RemoveEnemy);
	obj->Register("DoRemoveEnemy", LuaFn_Game_DoRemoveEnemy);
	obj->Register("SetActiveEnemyData", LuaFn_Game_SetActiveEnemyData);
	obj->Register("GetActiveEnemyData", LuaFn_Game_GetActiveEnemyData);

	obj->Register("DoMissionOver", LuaFn_Game_DoMissionOver);

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

int Export_Lua_Game::LuaFn_Game_GetMissionTargetData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	missionData * item = GameMain::getInstance()->GetMissionData();
	if (!node.argscount)
	{
		BYTE missiontype = item->missiontype;
		node.PInt(missiontype);
	}
	else
	{
		BYTE _missiontype = node.iNextGet();
		switch (_missiontype)
		{
		case M_MISSIONTYPE_TARGET:
			for (int i=0; i<M_MISSIONTARGETMAX; i++)
			{
				node.PInt(item->targets[i].enemybasetype);
				node.PInt(item->targets[i].num);
			}
			break;
		case M_MISSIONTYPE_DEFEND:
			node.PInt(item->defend.defendturn);
			break;
		}
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

int Export_Lua_Game::LuaFn_Game_AttackEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(4);

	// enemyindex, weapontype, x, y, r/ xe, ye -> hitRate
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

	float hitRate = 0;
	float enemyx, enemyy, enemyscale;
	GameMain::getInstance()->GetEnemyXYScale(item, &enemyx, &enemyy, &enemyscale);

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

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_AddEnemy(LuaState * ls)
{
	_ENTERFUNC_LUA(5);

	// itemtag, etype, elayer, enemiesindex -> count

	int _itemtag = node.iNextGet();
	float _x = node.fNextGet();
	float _y = node.fNextGet();
	BYTE _etype = node.iNextGet();
	int _elayer = node.iNextGet();
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

	int enemycount = GameMain::getInstance()->AddEnemy(_itemtag, _x, _y, _etype, _elayer, _enemiesindex, _angle);
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
	item->life = _life;
	item->elayer = _elayer;

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_GetActiveEnemyData(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> inscenecount, onsidecount
	// index, enemiesindex -> itemtag, x, y, etype, life, elayer

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

		node.PInt(itemtag);
		node.PFloat(x);
		node.PFloat(y);
		node.PInt(etype);
		node.PInt(life);
		node.PInt(elayer);
		node.PInt(angle);
	}

	_LEAVEFUNC_LUA;
}

int Export_Lua_Game::LuaFn_Game_DoMissionOver(LuaState * ls)
{
	_ENTERFUNC_LUA(0);

	// -> missionstate, hiscore, rank, btop

	GameMain * pgm = GameMain::getInstance();

	bool btop = false;
	BYTE missionstate = pgm->CheckMissionOver();
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
	BYTE rank = pgm->GetMissionRank();

	node.PInt(missionstate);
	node.PInt(hiscore);
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