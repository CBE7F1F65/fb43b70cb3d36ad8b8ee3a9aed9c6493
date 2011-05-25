#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

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
	MissionScoreData missions[M_MISSIONMAX];
	BYTE opencount;
	BYTE clearcount;
};

struct GameData
{
	HiScoreData hiscores[M_HISCOREMAX];
	StageScoreData stages[M_STAGEMAX];
};

class GameMain
{
public:
	GameMain();
	~GameMain();

	void Init();

	bool ReadData();
	void ReadIni();

	void SaveData();
	void ResetHiScore();
	void ReportHiScore();

	bool StageIsEnabled(int index);
	bool MissionIsEnabled(int missionindex, int stageindex=-1);
	bool EnableMission(int missionindex, int stageindex=-1);

	bool TryStage(int index);
	bool TryMission(int missionindex, int stageindex=-1);
	bool ClearMission(int missionindex, int stageindex=-1);

	int GetHiScore(int index);
	const char * GetHiScoreUsername(int index);

	bool ResetIni(bool bresetname=false);
	bool SaveIni();

	void SetBGMVol(int bgmvol);
	void SetSEVol(int sevol);
	void SetUsername(const char * username);

	bool InsertScore(int score);

	GameData gamedata;
	int bgmvol;
	int sevol;
	char username[M_USERNAMEMAX];

	int nowstage;
	int nowmission;

	int missionscore;
	int totalscore;
	int nowturn;

public:
	static GameMain * getInstance();
};

#endif