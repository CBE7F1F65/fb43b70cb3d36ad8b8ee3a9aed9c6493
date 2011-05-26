#include "../Header/GameMain.h"
#include "../Header/BIOInterface.h"
#include "../Header/BResource.h"

static GameMain * g_GameMainSingleton = NULL;

#define INISECTION_CUSTOM	"Custom"
#define ININAME_BGMVOL		"BGMVol"
#define INIDEFAULT_BGMVOL	100
#define ININAME_SEVOL		"SEVol"
#define INIDEFAULT_SEVOL	100
#define ININAME_USERNAME	"Username"
#define INIDEFAULT_USERNAME	""

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

	SaveData();
}

bool GameMain::ClearMission(int missionindex, int stageindex/* =-1 */)
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

	MissionScoreData * item = &gamedata.stages[stageindex].missions[missionindex];
	item->clearcount++;

	if (nowturn < item->bestturn)
	{
		item->bestturn = nowturn;
	}

	if (missionscore > item->hiscore)
	{
		item->hiscore = missionscore;
	}

	InsertScore(totalscore);
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

int GameMain::GetMissionBGSIID()
{
	int index = nowstage*M_STAGEMISSIONMAX+nowmission;
	return BResource::getInstance()->missiondata[index].bgsiid;
}

void GameMain::GetMissionHelpData(BYTE * helptypes, BYTE * helpindexs)
{
	int index = nowstage*M_STAGEMISSIONMAX+nowmission;
	missionData * item = &(BResource::getInstance()->missiondata[index]);
	if (helpindexs)
	{
		for (int i=0; i<M_MISSIONHELPMAX; i++)
		{
			helptypes[i] = item->helps[i].helptype;
			helpindexs[i] = item->helps[i].helpindex;
		}
	}
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