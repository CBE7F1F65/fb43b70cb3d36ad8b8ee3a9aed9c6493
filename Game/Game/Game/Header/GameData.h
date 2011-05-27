#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include "Const.h"
#include "MainDependency.h"

// TODO Update GameData from order version

struct HiScoreData 
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
	BYTE bestturn;
	BYTE enabled;
};

struct StageScoreData
{
	MissionScoreData missions[M_STAGEMISSIONMAX];
	BYTE opencount;
	BYTE clearcount;
};

struct HelpAccessData{
	BYTE accessflag;
};

struct ItemOwnedData{
	int count;
};

struct GameData
{
	HiScoreData hiscores[M_HISCOREMAX];
	StageScoreData stages[M_STAGEMAX];
	HelpAccessData helps[M_HELPTYPEMAX];
	ItemOwnedData items[M_ITEMTYPEMAX];
};

#endif