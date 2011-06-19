#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "Const.h"
#include "MainDependency.h"
#include "GameAchievement.h"

// TODO Update GameData from order version

struct SurvivalHiScoreData 
{
	int hiscore;
	char username[M_USERNAMEMAX];
};

struct MissionScoreData
{
	int trycount;
	int clearcount;
	int hiscore;
	BYTE rank;
	BYTE eggflag;
	BYTE bestturn;
	BYTE enabled;
};

struct TotalHiScoreData
{
	int hiscore;
};

struct StageScoreData
{
	MissionScoreData missions[M_STAGEMISSIONMAX];
	BYTE opencount;
	BYTE clearcount;
};

struct FunctionAccessData{
	LONGLONG accessflag;
};

struct HelpAccessData{
	BYTE accessflag;
};

struct ItemOwnedData{
	int count;
};


struct GameData
{
	SurvivalHiScoreData hiscores[M_HISCOREMAX];
	TotalHiScoreData totalhiscore;
	StageScoreData stages[M_STAGEMAX];
	FunctionAccessData functionaccess;
	HelpAccessData helps[M_HELPTYPEMAX];
	ItemOwnedData items[M_ITEMTYPEMAX];
	AchievementData achieves;
};

#endif