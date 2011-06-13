#include "../Header/GameMain.h"
#include "../Header/BIOInterface.h"
#include "../Header/BResource.h"

#include "../Header/GameAchievement.h"

static GameMain * g_GameMainSingleton = NULL;

#define INISECTION_CUSTOM	"Custom"
#define ININAME_BGMVOL		"BGMVol"
#define INIDEFAULT_BGMVOL	100
#define ININAME_SEVOL		"SEVol"
#define INIDEFAULT_SEVOL	100
#define ININAME_USERNAME	"Username"
#define INIDEFAULT_USERNAME	""

#define M_CCZ_ELAYER_01		"CCZ_eLayer_01"

GameMain::GameMain()
{
	BIOInterface::getInstance()->System_Assert(g_GameMainSingleton == NULL, ASSERTSTR_SECONDSINGLETON);
	bgmvol = INIDEFAULT_BGMVOL;
	sevol = INIDEFAULT_SEVOL;
	strcpy(username, "");
	ZeroMemory(&gamedata, sizeof(GameData));

	nowstage = 0;
	nowmission = 0;

	helptype = 0;
	helpindex = 0;

	missionscore = 0;
	totalscore = 0;
	nowturn = 0;

	nowhp = 0;
	nowap = 0;
	nowsp = 0;

	itemtypecount = 0;
	stateflag = GAMESTATE_ST_NULL;

	ptfar.x = M_SCREEN_XCENTER;
	ptfar.y = M_SCREEN_YCENTER;
	ptfar.z = M_SCREEN_Z;

	for (int i=0; i<ENEMY_VECTORTYPEMAX; i++)
	{
		list<EnemyInGameData> _enemiesgroup;
		enemies.push_back(_enemiesgroup);
	}

	enemyelayerbase = 0;

	GameAchievement::Init(&(gamedata.achieves));
}

GameMain::~GameMain()
{
	if (g_GameMainSingleton)
	{
		delete g_GameMainSingleton;
		g_GameMainSingleton = NULL;
	}
}

GameMain * GameMain::getInstance()
{
	if (!g_GameMainSingleton)
	{
		g_GameMainSingleton = new GameMain();
	}
	return g_GameMainSingleton;
}

void GameMain::Init()
{
	ReadIni();
	if (!ReadData())
	{
		SaveData();
	}

	if (!StageIsEnabled(0))
	{
		EnableMission(0, 0);
	}

	/*
	if (!HelpIsEnabled(1, 0))
	{
		EnableHelp(1, 0);
	}
	*/
}

void GameMain::OnlineLinkedCallback()
{
	ReportHiScore();
	GameAchievement::SubmitAchievement();
}

void GameMain::ReadIni()
{
	BIOInterface * bio = BIOInterface::getInstance();

	bgmvol = bio->Ini_GetInt(INISECTION_CUSTOM, ININAME_BGMVOL, INIDEFAULT_BGMVOL);
	if (bgmvol < 0 || bgmvol > INIDEFAULT_BGMVOL)
	{
		bgmvol = INIDEFAULT_BGMVOL;
	}
	sevol = bio->Ini_GetInt(INISECTION_CUSTOM, ININAME_SEVOL, INIDEFAULT_SEVOL);
	if (sevol < 0 || sevol > INIDEFAULT_SEVOL)
	{
		sevol = INIDEFAULT_SEVOL;
	}
	strcpy(username, bio->Ini_GetString(INISECTION_CUSTOM, ININAME_USERNAME, INIDEFAULT_USERNAME));
}

bool GameMain::ResetIni(bool bresetname/* =false */)
{
	if (bresetname)
	{
		SetUsername(INIDEFAULT_USERNAME);
	}
	SetBGMVol(INIDEFAULT_BGMVOL);
	SetSEVol(INIDEFAULT_SEVOL);

	return true;
}

bool GameMain::SaveIni()
{
	BIOInterface * bio = BIOInterface::getInstance();

	bio->Ini_SetInt(INISECTION_CUSTOM, ININAME_BGMVOL, bgmvol);
	bio->Ini_SetInt(INISECTION_CUSTOM, ININAME_SEVOL, sevol);
	bio->Ini_SetString(INISECTION_CUSTOM, ININAME_USERNAME, username);

	return true;
}

bool GameMain::ReadData()
{
	BIOInterface * bio = BIOInterface::getInstance();
	DWORD _size = 0;
	BYTE * _content = NULL;
	bool bret = false;
	_content = bio->Data_Read(&_size);
	if (_size == sizeof(GameData))
	{
		memcpy(&gamedata, _content, sizeof(GameData));
		bret = true;
	}
	bio->Data_Free(_content);
	return bret;
}

bool GameMain::InsertScore(int score)
{
	bool btopscore = false;
	for (int i=0; i<M_HISCOREMAX; i++)
	{
		if (score > gamedata.hiscores[i].hiscore)
		{
			for (int j=M_HISCOREMAX-1; j>i; j--)
			{
				memcpy(&(gamedata.hiscores[j]), &(gamedata.hiscores[j-1]), sizeof(HiScoreData));
			}
			gamedata.hiscores[i].hiscore = score;
			strcpy(gamedata.hiscores[i].username, username);
			if (i == 0)
			{
				btopscore = true;
			}
			break;
		}
	}
	if (btopscore)
	{
		ReportHiScore();
		GameAchievement::HiScoreSet(score);
	}
	SaveData();
	return btopscore;
}

void GameMain::ReportHiScore()
{
	// TODO
}

bool GameMain::StageIsEnabled(int index)
{
	if (index < 0 || index >= M_STAGEMAX)
	{
		return false;
	}
	return gamedata.stages[index].opencount;
}

bool GameMain::MissionIsEnabled(int missionindex, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		return false;
	}
	return gamedata.stages[stageindex].missions[missionindex].enabled;
}

int GameMain::GetMissionTryCount(int missionindex, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		return false;
	}
	return gamedata.stages[stageindex].missions[missionindex].trycount;
}

bool GameMain::EnableMission(int missionindex, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		return false;
	}

	if (!MissionIsEnabled(missionindex, stageindex))
	{
		gamedata.stages[stageindex].missions[missionindex].enabled = 1;
		gamedata.stages[stageindex].opencount++;
		SaveData();
	}
	
	return true;
}

int GameMain::GetMissionHiScore(int missionindex/* =-1 */, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		missionindex = nowmission;
	}

	return gamedata.stages[stageindex].missions[missionindex].hiscore;
}

BYTE GameMain::GetMissionRank(int missionindex/* =-1 */, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		missionindex = nowmission;
	}

	return gamedata.stages[stageindex].missions[missionindex].rank;
}

bool GameMain::TryStage(int index)
{
	if (index < 0 || index >= M_STAGEMAX)
	{
		return false;
	}
	nowstage = index;
	return true;
}

bool GameMain::TryMission(int missionindex, int stageindex/* =-1 */)
{
	if (stageindex < 0 || stageindex >= M_STAGEMAX)
	{
		stageindex = nowstage;
	}
	if (missionindex < 0 || missionindex >= M_STAGEMISSIONMAX)
	{
		return false;
	}

	EnableMission(missionindex, stageindex);
	gamedata.stages[stageindex].missions[missionindex].trycount++;

	if (nowstage != stageindex)
	{
		TryStage(stageindex);
	}
	nowmission = missionindex;

	GameAchievement::SingleMissionTryCountSet(gamedata.stages[stageindex].missions[missionindex].trycount);

	SaveData();

	return true;
}

bool GameMain::HelpIsEnabled(BYTE _type, int index)
{
	BYTE type = _type-1;
	if (type >= M_HELPTYPEMAX)
	{
		return false;
	}
	if (index < 0)
	{
		return gamedata.helps[type].accessflag;
	}
	return gamedata.helps[type].accessflag & (1<<index);
}

bool GameMain::EnableHelp(BYTE _type, BYTE index)
{
	BYTE type = _type-1;
	if (type >= M_HELPTYPEMAX)
	{
		return false;
	}
	if (!HelpIsEnabled(_type, index))
	{
		gamedata.helps[type].accessflag |= (1<<index);
		SaveData();
	}
	return true;
}

void GameMain::SetHelpIndex(BYTE type, BYTE index)
{
	if (type > M_HELPTYPEMAX)
	{
		type = 0;
	}
	helptype = type;
	helpindex = index;
}

int GameMain::GetItemData(BYTE type, int * siid/* =NULL */)
{
	if (siid)
	{
		*siid = 0;
	}
	if (type > itemtypecount)
	{
		return 0;
	}

	if (siid)
	{
		*siid = BResource::getInstance()->itemdata[type].siid;
	}

	return gamedata.items[type].count;
}

int GameMain::BuyItem(BYTE type)
{
	if (type > itemtypecount)
	{
		return 0;
	}
	// TODO
	return 0;
}

bool GameMain::UseItem(BYTE type)
{
	// TODO
	return false;
}

int GameMain::GetMissionBGSIID()
{
	return GetMissionData()->bgsiid;
}

void GameMain::GetMissionHelpData(BYTE * helptypes, BYTE * helpindexs)
{
	missionData * item = GetMissionData();
	if (helpindexs)
	{
		for (int i=0; i<M_MISSIONHELPMAX; i++)
		{
			helptypes[i] = item->helps[i].helptype;
			helpindexs[i] = item->helps[i].helpindex;
		}
	}
}

missionData * GameMain::GetMissionData()
{
	BResource * pbres = BResource::getInstance();
	int index = pbres->GetMissionDataIndexByStageMission(nowstage, nowmission);
	return &(pbres->missiondata[index]);
}

void GameMain::EnterMission()
{
	nowhp = M_GAMEHPMAX;
	nowap = M_GAMEAPMAX;
	nowsp = GetMissionData()->sp;
	stateflag = GAMESTATE_ST_NULL;

	missionscore = 0;
	nowturn = 0;

	for (int i=0; i<ENEMY_VECTORTYPEMAX; i++)
	{
		enemies[i].clear();
	}

	ZeroMemory(&targetcount, sizeof(missionTargetData)*M_MISSIONTARGETMAX);

	missionData * item = GetMissionData();
	if (item->missiontype == M_MISSIONTYPE_TARGET)
	{
		for (int i=0; i<M_MISSIONTARGETMAX; i++)
		{
			targetcount[i].enemybasetype = item->targets[i].enemybasetype;
		}
	}
}

bool GameMain::ClearMission()
{
	MissionScoreData * item = &gamedata.stages[nowstage].missions[nowmission];

	missionData * mitem = GetMissionData();

	GameAchievement::BestTurnSet(nowturn);
	if (!item->clearcount)
	{
		// TODO: bStory
		bool bStory = false;
		GameAchievement::MissionClearAdd(nowstage, bStory);
	}

	item->clearcount++;

	if (nowturn < item->bestturn)
	{
		item->bestturn = nowturn;
	}

	if (missionscore > item->hiscore)
	{
		totalscore += missionscore - item->hiscore;
		item->hiscore = missionscore;

		int orank = item->rank;
		for (int i=item->rank; i<M_MISSIONRANKMAX; i++)
		{
			if (missionscore >= mitem->ranks[i].hiscore)
			{
				item->rank = i+1;
			}
		}
		if (item->rank == M_MISSIONRANKMAX && item->rank > orank)
		{
			GameAchievement::Rank3Add();
		}
	}
	return InsertScore(totalscore);
}

void GameMain::SetHPAPSP(int hp, int ap, int sp)
{
	if (hp >= 0)
	{
		nowhp = hp;
	}
	if (ap >= 0)
	{
		nowap = ap;
	}
	if (sp >= 0)
	{
		nowsp = sp;
	}
	if (nowhp > M_GAMEHPMAX)
	{
		nowhp = M_GAMEHPMAX;
	}
	if (nowap > M_GAMEAPMAX)
	{
		nowap = M_GAMEAPMAX;
	}
	if (nowsp > M_GAMESPMAX)
	{
		nowsp = M_GAMESPMAX;
	}
}

int GameMain::GetState(int *stateST/* =NULL */, int *stateAction/* =NULL */, int *stateStep/* =NULL */)
{
	if (stateST)
	{
		*stateST = stateflag&GAMESTATE_STMASK;
	}
	if (stateAction)
	{
		*stateAction = stateflag&GAMESTATE_ACTIONMASK;
	}
	if (stateStep)
	{
		*stateStep = stateflag&GAMESTATE_STEPMASK;
	}
	return stateflag;
}

int GameMain::SetState(int stateST, int stateAction/* =-1 */, int stateStep/* =-1 */)
{
	stateflag &= ~GAMESTATE_STMASK;
	stateflag |= (stateST&GAMESTATE_STMASK);

	if (stateAction >= 0)
	{
		stateflag &= ~GAMESTATE_ACTIONMASK;
		stateflag |= (stateAction&GAMESTATE_ACTIONMASK);
	}
	if (stateStep >= 0)
	{
		stateflag &= ~GAMESTATE_STEPMASK;
		stateflag |= (stateStep&GAMESTATE_STEPMASK);
	}
	return stateflag;
}

void GameMain::SaveData()
{
	BIOInterface * bio = BIOInterface::getInstance();
	bio->Data_Save((BYTE *)&gamedata, sizeof(GameData));
}

void GameMain::ResetHiScore()
{
	ZeroMemory(&(gamedata.hiscores), sizeof(HiScoreData)*M_HISCOREMAX);
}

void GameMain::SetBGMVol(int _bgmvol)
{
	if (_bgmvol < 0 || _bgmvol > INIDEFAULT_BGMVOL)
	{
		return;
	}
	bgmvol = _bgmvol;
}

void GameMain::SetSEVol(int _sevol)
{
	if (_sevol < 0 || _sevol > INIDEFAULT_SEVOL)
	{
		return;
	}
	sevol = _sevol;
}

void GameMain::SetUsername(const char * _username)
{
	strcpy(username, _username);
	SaveIni();
}

int GameMain::GetHiScore(int index)
{
	if (index < 0 || index >= M_HISCOREMAX)
	{
		return 0;
	}
	return gamedata.hiscores[index].hiscore;
}

const char * GameMain::GetHiScoreUsername(int index)
{
	if (index < 0 || index >= M_HISCOREMAX)
	{
		return NULL;
	}
	return gamedata.hiscores[index].username;
}


BYTE GameMain::CheckMissionOver()
{
	missionData * item = GetMissionData();
	switch (item->missiontype)
	{
	case M_MISSIONTYPE_NORMAL:
		if (true)
		{
			int totalenemycount = 0;
			for (int i=0; i<ENEMY_VECTORTYPEMAX; i++)
			{
				totalenemycount += enemies[i].size();
			}
			if (!totalenemycount)
			{
				return M_MISSIONSTATE_CLEAR;
			}
		}
		break;
	case M_MISSIONTYPE_DEFEND:
		if (nowturn > item->defend.defendturn)
		{
			return M_MISSIONSTATE_CLEAR;
		}
		break;
	case M_MISSIONTYPE_TARGET:
		if (true)
		{
			int targetclearedcount = 0;
			missionData * mitem = GetMissionData();
			for (int i=0; i<M_MISSIONTARGETMAX; i++)
			{
				if (targetcount[i].num >= mitem->targets[i].num || targetcount[i].enemybasetype >= M_ENEMYTYPEMAX)
				{
					targetclearedcount++;
				}
			}
			if (targetclearedcount == M_MISSIONTARGETMAX)
			{
				return M_MISSIONSTATE_CLEAR;
			}
		}
		break;
	case M_MISSIONTYPE_SUICIDE:
		if (nowhp <= 0)
		{
			return M_MISSIONSTATE_CLEAR;
		}
		break;
	}
	if (nowhp <= 0)
	{
		return M_MISSIONSTATE_FAILED;
	}
	return M_MISSIONSTATE_PROGRESSING;
}

int GameMain::AddEnemy(int itemtag, float x, float y, BYTE etype, int elayer, BYTE enemiesindex, int angle/*=0*/)
{
	EnemyInGameData _edata;

	BResource * pbres = BResource::getInstance();
	enemyData * item = &(pbres->enemydata[etype]);
	enemyBaseData * baseitem = &(pbres->enemybasedata[item->type]);

	_edata.itemtag = itemtag;
	_edata.x = x;
	_edata.y = y;
	_edata.etype = etype;
	_edata.life = item->life;
	_edata.elayer = elayer;
	_edata.angle = angle;

	int retval = 0;
	enemies[enemiesindex].push_back(_edata);
	return enemies[enemiesindex].size();
}

int GameMain::DoRemoveEnemy(BYTE enemiesindex)
{
	int beatcountinoneturn = 0;
	for (list<EnemyInGameData>::iterator it=enemies[enemiesindex].begin(); it!=enemies[enemiesindex].end();)
	{
		if (it->life < 0)
		{
			it = enemies[enemiesindex].erase(it);
			beatcountinoneturn++;
		}
		else
		{
			++it;
		}
	}
	if (beatcountinoneturn && enemiesindex == ENEMY_INSCENE)
	{
		GameAchievement::BeatInOneTurnSet(beatcountinoneturn);
	}
	return enemies[enemiesindex].size();
}

void GameMain::RemoveEnemy(int index, BYTE enemiesindex)
{
	EnemyInGameData * item = GetEnemyByIndex(index, enemiesindex);
	if (!item || item->life < 0)
	{
		return;
	}
	item->life = -1;
	if (enemiesindex == ENEMY_INSCENE)
	{
		BYTE basetype = BResource::getInstance()->GetEnemyBaseType(item->etype);
		GameAchievement::BeatCountAdd(basetype);
		missionData * mitem = GetMissionData();
		if (mitem->missiontype == M_MISSIONTYPE_TARGET)
		{
			for (int i=0; i<M_MISSIONTARGETMAX; i++)
			{
				if (targetcount[i].enemybasetype == basetype)
				{
					if (targetcount[i].num < mitem->targets[i].num)
					{
						targetcount[i].num++;
					}
					break;
				}
			}
		}
	}
}

EnemyInGameData * GameMain::GetEnemyByIndex(int index, BYTE enemiesindex)
{
	int i=0;
	for (list<EnemyInGameData>::iterator it=enemies[enemiesindex].begin(); it!=enemies[enemiesindex].end(); it++)
	{
		if (i == index)
		{
			return &(*it);
		}
		i++;
	}
	return NULL;
}

void GameMain::GetEnemyXYScale(EnemyInGameData * item, float * x, float * y, float * scale)
{
	if (!item)
	{
		return;
	}

	if (!enemyelayerbase)
	{
		if (!BResource::getInstance()->GetCustomConstDataByName(M_CCZ_ELAYER_01, &enemyelayerbase))
		{
			return;
		}
	}

	float _x = item->x;
	float _y = item->y;
	float _z = (M_SCREEN_Z/M_ENEMY_ELAYERMAX/2.0f)*(M_ENEMY_ELAYERMAX-1-item->elayer/enemyelayerbase);
	float _scale;
	
	_scale = BIOInterface::getInstance()->Math_Transform3DPoint(_x, _y, _z, &(GameMain::getInstance()->ptfar));
	if (x)
	{
		*x = _x;
	}
	if (y)
	{
		*y = _y;
	}
	if (scale)
	{
		*scale = _scale;
	}
}

void GameMain::Update()
{
	int stateST;
	int stateAction;
	int stateStep;
	GetState(&stateST, &stateAction, &stateStep);
/*
	if (stateST == GAMESTATE_ST_STANDBY)
	{
		stateST = GAMESTATE_ST_PROGRESSING;
	}
	else 
*/
	if (stateST == GAMESTATE_ST_STEPFORWARD)
	{
		stateStep++;
//		stateST = GAMESTATE_ST_PROGRESSING;
	}
	else if (stateST == GAMESTATE_ST_FINISHED)
	{
		switch (stateAction)
		{
		case GAMESTATE_WAITING:
			stateAction = GAMESTATE_SHOWHELP;
			break;
		case GAMESTATE_SHOWHELP:
			stateAction = GAMESTATE_ENEMYENTER;
			break;

		case GAMESTATE_ENEMYENTER:
			stateAction = GAMESTATE_SPECIALENEMYACTION;
			break;

		case GAMESTATE_SPECIALENEMYACTION:
			if (CheckMissionOver())
			{
				stateAction = GAMESTATE_OVER;
			}
			else
			{
				stateAction = GAMESTATE_ADDENEMY;
			}
			break;

		case GAMESTATE_ADDENEMY:
			stateAction = GAMESTATE_HPREGAIN;
			break;
		case GAMESTATE_HPREGAIN:
			stateAction = GAMESTATE_SHOWTURNSTART;
			break;
		case GAMESTATE_SHOWTURNSTART:
			if (CheckMissionOver())
			{
				stateAction = GAMESTATE_OVER;
			}
			else
			{
				stateAction = GAMESTATE_PLANNING;
			}
			break;
		case GAMESTATE_PLANNING:
			stateAction = GAMESTATE_SELFACTION;
			break;

		case GAMESTATE_SELFACTION:
			if (CheckMissionOver())
			{
				stateAction = GAMESTATE_OVER;
			}
			else
			{
				stateAction = GAMESTATE_APREGAIN;
			}
			break;
		case GAMESTATE_APREGAIN:
			stateAction = GAMESTATE_ENEMYACTION;
			break;
		case GAMESTATE_ENEMYACTION:
			if (CheckMissionOver())
			{
				stateAction = GAMESTATE_OVER;
			}
			else
			{
				stateAction = GAMESTATE_ENEMYENTER;
			}
			break;

		}
		stateStep = 0;
		stateST = GAMESTATE_ST_NULL;
	}

	stateflag = SetState(stateST, stateAction, stateStep);

}